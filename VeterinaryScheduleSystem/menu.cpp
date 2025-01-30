#include "menu.h"
#include "mainwindow.h"
#include "ui_menu.h"
#include "consultasdodia.h"
#include "cadastrocliente.h"
#include "agendamento.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDate>
#include <QTreeWidgetItem>
#include <QMessageBox>

menu::menu(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::menu),
    mainWindow(parent)
{
    ui->setupUi(this);

    ui->treeWidget->setColumnCount(5);  // Agora são 5 colunas, pois vamos mostrar a data da consulta
    QStringList headers;
    headers << "Pet" << "Tutor" << "Data" << "Hora" << "Veterinário";  // Adicionando "Data" no header
    ui->treeWidget->setHeaderLabels(headers);

    carregarConsultas();
}

menu::~menu()
{
    delete ui;
}

QVector<QJsonObject> menu::carregarTutores()
{
    QFile arquivo("tutores.json");
    QVector<QJsonObject> tutores;

    if (!arquivo.open(QIODevice::ReadOnly)) {
        return tutores;
    }

    QJsonDocument doc = QJsonDocument::fromJson(arquivo.readAll());
    QJsonArray array = doc.array();
    for (const QJsonValue &valor : array) {
        tutores.append(valor.toObject());
    }

    arquivo.close();
    return tutores;
}

void menu::carregarConsultas() {
    QFile file("consultas.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Não foi possível abrir o arquivo de consultas.");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (document.isNull()) {
        qWarning("Erro ao carregar JSON.");
        return;
    }

    QJsonArray consultas = document.array();

    // Carregar tutores
    QVector<QJsonObject> tutores = carregarTutores();

    ui->treeWidget->clear(); // Limpar lista antes de atualizar

    for (const QJsonValue &value : consultas) {
        QJsonObject consulta = value.toObject();

        // Verificar se os campos existem
        if (!consulta.contains("nome_pet") || !consulta.contains("cpf_tutor") ||
            !consulta.contains("hora") || !consulta.contains("veterinario") || !consulta.contains("data")) {
            qWarning("Consulta com campos ausentes no JSON.");
            continue;
        }

        QString dataConsulta = consulta["data"].toString();

        // Normalizar data para o formato "dd-MM-yyyy"
        QDate date = QDate::fromString(dataConsulta, "dd-MM-yyyy"); // Formato com "-"

        if (!date.isValid()) {
            qWarning() << "Data inválida:" << dataConsulta;
            continue;
        }

        QString dataFormatada = date.toString("dd-MM-yyyy");

        // Buscar o nome do tutor pelo CPF
        QString cpfTutor = consulta["cpf_tutor"].toString();
        QString nomeTutor = "Desconhecido"; // Default caso não encontre o tutor

        for (const QJsonObject &tutor : tutores) {
            if (tutor["cpf"].toString() == cpfTutor) {
                nomeTutor = tutor["nome"].toString();
                break; // Encontrou o tutor, pode sair do loop
            }
        }

        // Criar um item no treeWidget
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, consulta["nome_pet"].toString());       // Pet
        item->setText(1, nomeTutor);                            // Tutor (nome do tutor)
        item->setText(2, dataFormatada);                        // Data da consulta
        item->setText(3, consulta["hora"].toString());          // Hora da consulta
        item->setText(4, consulta["veterinario"].toString());  // Veterinário
        ui->treeWidget->addTopLevelItem(item);  // Adiciona o item ao QTreeWidget
    }

    ui->treeWidget->viewport()->update(); // Forçar atualização da interface
}

void menu::on_pushButton_6_clicked()
{
    // Botão Cadastro Cliente
    cadastrocliente *cadastroScreen = new cadastrocliente(); // Cria a tela de cadastro
    cadastroScreen->show(); // Exibe a tela de cadastro
    this->close();          // Fecha a janela do menu
}

void menu::on_sairButton_clicked()
{
    // Botão Sair
    this->close(); // Fecha o menu
    if (mainWindow) {
        mainWindow->show(); // Exibe a MainWindow novamente
    }
}

void menu::on_agendamentoButton_clicked()
{
    // Botão Agendar Consulta
    agendamento *agendamentoScreen = new agendamento(); // Cria a tela de agendamento
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();             // Fecha a janela do menu
}

void menu::on_consultaButton_clicked()
{
    // Botão Consultas
    consultasdodia *consultasScreen = new consultasdodia();
    consultasScreen->show();
    this->close();
}
