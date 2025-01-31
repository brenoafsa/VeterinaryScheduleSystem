#include "cancelarconsulta.h"
#include "ui_cancelarconsulta.h"
#include "agendamento.h"
#include "menu.h"
#include "cadastrocliente.h"
#include "consultasdodia.h"
#include "remarcacao.h"
#include <QDateEdit>
#include <QTimeEdit>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

// Contrutor
cancelarconsulta::cancelarconsulta(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cancelarconsulta)
{
    ui->setupUi(this);

    ui->dateEdit_2->setCalendarPopup(true); //pop-up de data
    // Definir a data do dia atual ao abrir a tela
    ui->dateEdit_2->setDate(QDate::currentDate());


    // Populando o comboBox com horários padronizados (7:30 até 19:00, de 30 em 30 minutos)
    QTime horaInicio(7, 30); // 07:30
    QTime horaFim(19, 0);    // 19:00

    while (horaInicio <= horaFim) {
        ui->comboBox->addItem(horaInicio.toString("HH:mm"));
        horaInicio = horaInicio.addSecs(30 * 60); // Adiciona 30 minutos
    }

}

// Destrutor
cancelarconsulta::~cancelarconsulta()
{
    delete ui;
}

// Botão Nova consulta
void cancelarconsulta::on_novaconsultaButton_clicked()
{
    agendamento *agendamentoScreen = new agendamento();
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();          // Fecha a janela atual
}

// Botão consultas gerais (menu)
void cancelarconsulta::on_menuButton_clicked()
{
    // Botão para retornar ao menu
    menu *menuScreen = new menu();
    menuScreen->show();         // Exibe a janela do menu
    this->close();              // Fecha a tela de remarcação
}

// Botão para cancelar a consulta
void cancelarconsulta::on_apagarButton_clicked()
{
    // Obtem os dados preenchidos nos campos
    QString nomePet = ui->nomePet_2->text().trimmed().toLower();
    QString cpfTutor = ui->cpfTutor_2->text().remove(".").remove("-").trimmed();
    QString dataConsulta = ui->dateEdit_2->date().toString("dd/MM/yyyy").replace("/", "-");
    QString horaConsulta = ui->comboBox->currentText();
    QString veterinario = ui->veterinarioEdit_2->text().trimmed();

    // Verificar se algo está vazio
    if (nomePet.isEmpty() || cpfTutor.isEmpty() || dataConsulta.isEmpty() || horaConsulta.isEmpty() || veterinario.isEmpty()) {
        showErrorDialog("Por favor, preencha todos os campos.");
        return;
    }

    // Carregar as consultas existentes
    QFile file("consultas.json");
    if (!file.open(QIODevice::ReadOnly)) {
        showErrorDialog("Erro ao carregar consultas.");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray consultasArray = doc.array();
    file.close();

    bool consultaEncontrada = false;

    // Buscar a consulta
    for (int i = 0; i < consultasArray.size(); ++i) {
        QJsonObject consulta = consultasArray[i].toObject();

        if (consulta["cpf_tutor"].toString() == cpfTutor &&
            consulta["nome_pet"].toString().toLower() == nomePet &&
            consulta["data"].toString() == dataConsulta &&
            consulta["hora"].toString() == horaConsulta &&
            consulta["veterinario"].toString() == veterinario) {

            consultasArray.removeAt(i);
            consultaEncontrada = true;
            break;
        }
    }

    // Salva as alterações no arquivo
    if (consultaEncontrada) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            showErrorDialog("Erro ao salvar as alterações.");
            return;
        }

        file.write(QJsonDocument(consultasArray).toJson());
        file.close();

        QMessageBox successBox;
        successBox.setStyleSheet(
            "QMessageBox {"
            "    background-color: #C4B4E0; color: black; font-size: 14px;"
            "}"
            "QMessageBox QLabel {"
            "    color: #FFFFFF;"
            "}"
            "QPushButton {"
            "    background-color: #9B88BF; color: #FFFFFF; border-radius: 5px; padding: 5px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #C7C0D5;"
            "}"
            );
        successBox.setIcon(QMessageBox::Information);
        successBox.setText("Consulta apagada com sucesso!");
        successBox.setWindowTitle("Sucesso");
        successBox.exec();

    } else {
        showErrorDialog("Nenhuma consulta encontrada com os dados fornecidos.");
    }
}

// Botão para consultas do dia
void cancelarconsulta::on_consultaButton_clicked()
{
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen->show();
    this->close();
}

// Mensagem de erro
void cancelarconsulta::showErrorDialog(const QString &message)
{
    QMessageBox errorBox;
    errorBox.setStyleSheet("QMessageBox { background-color: #D9048E; color: white; font-size: 14px; }"
                           "QPushButton { background-color: #F26DCF; color: white; border-radius: 5px; padding: 5px; }"
                           "QPushButton:hover { background-color: #A6036D; }");
    errorBox.setText(message);
    errorBox.exec();
}

// Botão para cancelar (que limpa os dados)
void cancelarconsulta::on_cancelarButton_2_clicked()
{
    ui->nomePet_2->clear();
    ui->cpfTutor_2->clear();
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->comboBox->setCurrentIndex(0);
    ui->veterinarioEdit_2->clear();

}

// Botão remarcar consulta
void cancelarconsulta::on_remarcacaoButton_clicked()
{
    remarcacao *remarcacaoScreen = new remarcacao();
    remarcacaoScreen -> show();
    this -> close();
}

// Botão para consultas do dia
void cancelarconsulta::on_consultaButton_2_clicked()
{
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen -> show();
    this -> close();
}

// Botão agendamento
void cancelarconsulta::on_agendamentoButton_2_clicked()
{
    agendamento *agendamentoScreen = new agendamento();
    agendamentoScreen -> show();
    this -> close();
}

// Botão Cadastro Cliente
void cancelarconsulta::on_pushButton_6_clicked()
{
    cadastrocliente *cadastroScreen = new cadastrocliente(); // Cria a tela de cadastro
    cadastroScreen->show(); // Exibe a tela de cadastro
    this->close();          // Fecha a janela do menu
}

