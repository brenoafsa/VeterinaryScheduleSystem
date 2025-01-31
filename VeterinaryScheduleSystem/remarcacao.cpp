#include "remarcacao.h"
#include "ui_remarcacao.h"
#include "agendamento.h"
#include "menu.h"
#include "consultasdodia.h"
#include "cancelarconsulta.h"
#include "cadastrocliente.h"
#include <QDateEdit>
#include <QTimeEdit>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

// Construtor
remarcacao::remarcacao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::remarcacao)
{
    ui->setupUi(this);

    ui->dateEdit->setCalendarPopup(true); //pop-up de data

    ui->dateEdit->setDate(QDate::currentDate());

    QTime horaInicio(7, 30);
    QTime horaFim(19, 0);

    while (horaInicio <= horaFim) {
        ui->comboBox->addItem(horaInicio.toString("HH:mm"));
        horaInicio = horaInicio.addSecs(30 * 60);
    }


}

// Destrutor
remarcacao::~remarcacao()
{
    delete ui;
}

// Botão Nova consulta
void remarcacao::on_novaconsultaButton_clicked()
{
    agendamento *agendamentoScreen = new agendamento();
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();          // Fecha a janela atual
}

// Botão retorna ao menu (consultas gerais)
void remarcacao::on_menuButton_clicked()
{
    menu *menuScreen = new menu();
    menuScreen->show();         // Exibe a janela do menu
    this->close();              // Fecha a tela de remarcação
}

void remarcacao::on_alterarButton_clicked()
{
    // Lógica para buscar e atualizar consulta (remarcação)
    QString nomePet = ui->nomePet->text().trimmed().toLower();
    QString cpfTutor = ui->cpfTutor->text().remove(".").remove("-").trimmed();
    QString dataConsulta = ui->dateEdit->date().toString("dd-MM-yyyy");
    QString horaConsulta = ui->comboBox->currentText();
    QString veterinario = ui->veterinarioEdit->text().trimmed();

    // Verificação de campos vazios
    if (nomePet.isEmpty() || cpfTutor.isEmpty() || dataConsulta.isEmpty() || horaConsulta.isEmpty() || veterinario.isEmpty()) {
        showErrorDialog("Por favor, preencha todos os campos.");
        return;
    }

    // Carrega as consultas existentes
    QFile file("consultas.json");
    if (!file.open(QIODevice::ReadOnly)) {
        showErrorDialog("Erro ao carregar consultas.");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray consultasArray = doc.array();
    file.close();

    bool consultaEncontrada = false;
    for (QJsonValueRef consultaValue : consultasArray) {
        QJsonObject consulta = consultaValue.toObject();

        QString cpfConsulta = consulta["cpf_tutor"].toString();
        QString nomePetConsulta = consulta["nome_pet"].toString().toLower();

        // Se encontrar uma consulta com o mesmo CPF e nome do pet
        if (cpfConsulta == cpfTutor && nomePetConsulta == nomePet) {
            consulta["data"] = dataConsulta;
            consulta["hora"] = horaConsulta;
            consulta["veterinario"] = veterinario;

            consultaEncontrada = true;
            consultaValue = consulta;
            break;
        }
    }

    // Se encontrou a consulta, salvar as mudanças
    if (consultaEncontrada) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {  // Abrir para escrever e truncar o arquivo
            showErrorDialog("Erro ao salvar a remarcação.");
            return;
        }

        // Salvar os dados atualizados no arquivo JSON
        file.write(QJsonDocument(consultasArray).toJson());
        file.close();

        // Exibir a mensagem de sucesso
        QMessageBox successBox;
        successBox.setStyleSheet("QMessageBox { background-color: #D9048E; color: white; font-size: 14px; }"
                                 "QPushButton { background-color: #F26DCF; color: white; border-radius: 5px; padding: 5px; }"
                                 "QPushButton:hover { background-color: #A6036D; }");
        successBox.setText("Consulta remarcada com sucesso!");
        successBox.exec();
    } else {
        showErrorDialog("Consulta não encontrada para este pet e tutor.");
    }
}

// Botão Consultas do dia
void remarcacao::on_consultaButton_clicked()
{
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen->show();
    this->close();
}

// Mensagem de ero
void remarcacao::showErrorDialog(const QString &message)
{
    QMessageBox errorBox;
    errorBox.setStyleSheet("QMessageBox { background-color: #D9048E; color: white; font-size: 14px; }"
                           "QPushButton { background-color: #F26DCF; color: white; border-radius: 5px; padding: 5px; }"
                           "QPushButton:hover { background-color: #A6036D; }");
    errorBox.setText(message);
    errorBox.exec();
}

// Botão cancelar consulta
void remarcacao::on_cancelarconsultaButton_clicked()
{
    cancelarconsulta *cancelarconsultaScreen = new cancelarconsulta();
    cancelarconsultaScreen->show();
    this->close();
}

// Botão cancelar e limpar os dados preenchidos
void remarcacao::on_cancelarButton_clicked()
{
    ui->nomePet->clear();
    ui->cpfTutor->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox->setCurrentIndex(0);
    ui->veterinarioEdit->clear();
}

// Botão Cadastro Cliente
void remarcacao::on_pushButton_6_clicked()
{
    cadastrocliente *cadastroScreen = new cadastrocliente(); // Cria a tela de cadastro
    cadastroScreen->show(); // Exibe a tela de cadastro
    this->close();
}

