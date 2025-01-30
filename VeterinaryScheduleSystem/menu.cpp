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

    ui->treeWidget->setStyleSheet(
        "QTreeWidget {"
        "   background-color: #f5f5f5;"
        "   border-radius: 10px;"
        "   font-size: 14px;"
        "   color: #333;"
        "}"
        "QTreeWidget::item {"
        "   padding: 10px;"
        "   border-bottom: 1px solid #ccc;"
        "}"
        "QTreeWidget::item:selected {"
        "   background-color: #C4B4E0;"
        "   color: white;"
        "}"
        );
    ui->treeWidget->header()->setStyleSheet(
        "QHeaderView::section {"
        "   background-color: #9B88BF;"
        "   color: white;"
        "   padding: 5px;"
        "   border-radius: 5px;"
        "}"
        );
    ui->treeWidget->setExpandsOnDoubleClick(true);
    ui->treeWidget->setColumnWidth(0, 250); // Ajuste conforme necessário






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

    // Lista de meses em ordem
    QStringList mesesOrdenados = {
        "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
        "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
    };

    // Mapa para organizar os dados: meses > dias > consultas
    QMap<QString, QMap<QString, QList<QJsonObject>>> consultasOrganizadas;

    for (const QJsonValue &value : consultas) {
        QJsonObject consulta = value.toObject();

        if (!consulta.contains("nome_pet") || !consulta.contains("cpf_tutor") ||
            !consulta.contains("hora") || !consulta.contains("veterinario") || !consulta.contains("data")) {
            qWarning("Consulta com campos ausentes no JSON.");
            continue;
        }

        QString dataConsulta = consulta["data"].toString();
        QDate date = QDate::fromString(dataConsulta, "dd-MM-yyyy");

        if (!date.isValid()) {
            qWarning() << "Data inválida:" << dataConsulta;
            continue;
        }

        QString mes = mesesOrdenados[date.month() - 1]; // Nome do mês em português
        QString dia = date.toString("dd");             // Dia do mês

        consultasOrganizadas[mes][dia].append(consulta);
    }

    // Preencher o TreeWidget com os dados organizados
    for (const QString &mes : mesesOrdenados) { // Usar ordem fixa dos meses
        if (!consultasOrganizadas.contains(mes)) {
            continue; // Ignorar meses que não têm consultas
        }

        // Criar item para o mês
        QTreeWidgetItem *mesItem = new QTreeWidgetItem(ui->treeWidget);
        mesItem->setText(0, mes);

        const QMap<QString, QList<QJsonObject>> &dias = consultasOrganizadas[mes];
        for (const QString &dia : dias.keys()) {
            // Criar item para o dia
            QTreeWidgetItem *diaItem = new QTreeWidgetItem(mesItem);
            diaItem->setText(0, "Dia " + dia);

            const QList<QJsonObject> &consultasDoDia = dias[dia];
            for (const QJsonObject &consulta : consultasDoDia) {
                // Criar item para a consulta
                QTreeWidgetItem *consultaItem = new QTreeWidgetItem(diaItem);
                QString cpfTutor = consulta["cpf_tutor"].toString();
                QString nomeTutor = "Desconhecido";

                // Buscar nome do tutor pelo CPF
                for (const QJsonObject &tutor : tutores) {
                    if (tutor["cpf"].toString() == cpfTutor) {
                        nomeTutor = tutor["nome"].toString();
                        break;
                    }
                }

                // Preencher colunas do item da consulta
                consultaItem->setText(0, consulta["nome_pet"].toString());       // Nome do animal
                consultaItem->setText(1, nomeTutor);                            // Nome do tutor
                consultaItem->setText(2, consulta["data"].toString());          // Data
                consultaItem->setText(3, consulta["hora"].toString());          // Hora
                consultaItem->setText(4, consulta["veterinario"].toString());   // Veterinário
            }
        }
    }

    ui->treeWidget->viewport()->update(); // Atualiza a interface
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
