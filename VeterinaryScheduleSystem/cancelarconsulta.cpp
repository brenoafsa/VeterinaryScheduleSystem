#include "cancelarconsulta.h"
#include "ui_cancelarconsulta.h"
#include "agendamento.h"
#include "menu.h"
#include "consultasdodia.h"
#include <QDateEdit>
#include <QTimeEdit>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>

cancelarconsulta::cancelarconsulta(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cancelarconsulta)
{
    ui->setupUi(this);
}

cancelarconsulta::~cancelarconsulta()
{
    delete ui;
}

void cancelarconsulta::on_novaconsultaButton_clicked()
{
    // Botão Nova consulta
    agendamento *agendamentoScreen = new agendamento();
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();          // Fecha a janela atual
}

void cancelarconsulta::on_menuButton_clicked()
{
    // Botão para retornar ao menu
    menu *menuScreen = new menu();
    menuScreen->show();         // Exibe a janela do menu
    this->close();              // Fecha a tela de remarcação
}

void cancelarconsulta::on_apagarButton_clicked()
{
    // Lógica para buscar e apagar consulta
    QString nomePet = ui->nomePet_2->text().trimmed().toLower();  // Nome do pet
    QString cpfTutor = ui->cpfTutor_2->text().remove(".").remove("-").trimmed();  // CPF do tutor

    // Verificação de campos vazios
    if (nomePet.isEmpty() || cpfTutor.isEmpty()) {
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
    for (int i = 0; i < consultasArray.size(); ++i) {
        QJsonObject consulta = consultasArray[i].toObject();

        QString cpfConsulta = consulta["cpf_tutor"].toString();
        QString nomePetConsulta = consulta["nome_pet"].toString().toLower();

        // Se encontrar uma consulta com o mesmo CPF e nome do pet
        if (cpfConsulta == cpfTutor && nomePetConsulta == nomePet) {
            consultasArray.removeAt(i);  // Remove a consulta encontrada
            consultaEncontrada = true;
            break;
        }
    }

    // Se encontrou a consulta, salvar as mudanças
    if (consultaEncontrada) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {  // Abrir para escrever e truncar o arquivo
            showErrorDialog("Erro ao salvar as mudanças.");
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
        successBox.setText("Consulta apagada com sucesso!");
        successBox.exec();
    } else {
        showErrorDialog("Consulta não encontrada para este pet e tutor.");
    }
}

void cancelarconsulta::on_consultaButton_clicked()
{
    // Botão Consultas
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen->show();
    this->close();
}

void cancelarconsulta::showErrorDialog(const QString &message)
{
    QMessageBox errorBox;
    errorBox.setStyleSheet("QMessageBox { background-color: #D9048E; color: white; font-size: 14px; }"
                           "QPushButton { background-color: #F26DCF; color: white; border-radius: 5px; padding: 5px; }"
                           "QPushButton:hover { background-color: #A6036D; }");
    errorBox.setText(message);
    errorBox.exec();
}

void cancelarconsulta::on_cancelarButton_2_clicked()
{


    ui->nomePet_2->clear();
    ui->cpfTutor_2->clear();
    ui->dateEdit_2->setDate(QDate::currentDate()); // Define a data para o dia atual
    ui->timeEdit_2->setTime(QTime::currentTime()); // Define o horário para o atual
    ui->veterinarioEdit_2->clear();

}


