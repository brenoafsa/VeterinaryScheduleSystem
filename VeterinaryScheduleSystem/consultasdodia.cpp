#include "consultasdodia.h"
#include "ui_consultasdodia.h"
#include "menu.h"
#include "cadastrocliente.h"
#include "agendamento.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDate>
#include <QTimer>
#include <QRegularExpression>



consultasdodia::consultasdodia(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::consultasdodia)
{
    ui->setupUi(this);


    // Configuração do treeWidget (4 colunas)
    ui->treeWidget->setColumnCount(4);
    QStringList headers;
    headers << "Pet" << "Tutor" << "Hora" << "Veterinário";
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

    // Definir largura fixa para cada coluna
    ui->treeWidget->setColumnWidth(0, 180);  // Pet
    ui->treeWidget->setColumnWidth(1, 250);  // Tutor
    ui->treeWidget->setColumnWidth(2, 100);  // Hora
    ui->treeWidget->setColumnWidth(3, 200);  // Veterinário



    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &consultasdodia::on_pesquisarrButton_3_clicked);




    // Carregar consultas do dia ao abrir a tela
    carregarConsultasDoDia();

    // Atualizar automaticamente a cada 60 segundos
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &consultasdodia::carregarConsultasDoDia);
    timer->start(60000); // 60 segundos
}

consultasdodia::~consultasdodia()
{
    delete ui;
}




void consultasdodia::carregarConsultasDoDia() {
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
    QString dataAtual = QDate::currentDate().toString("dd-MM-yyyy");

    ui->treeWidget->clear(); // Limpar lista antes de atualizar
    qDebug() << "Data Atual: " << dataAtual;

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
        QDate date;
        if (dataConsulta.contains('/')) {
            date = QDate::fromString(dataConsulta, "dd/MM/yyyy"); // Formato com "/"
        } else if (dataConsulta.contains('-')) {
            date = QDate::fromString(dataConsulta, "dd-MM-yyyy"); // Formato com "-"
        }

        if (!date.isValid()) {
            qWarning() << "Data inválida:" << dataConsulta;
            continue;
        }

        QString dataFormatada = date.toString("dd-MM-yyyy"); // Convertendo para o formato padronizado
        qDebug() << "Consulta em:" << dataFormatada;

        if (dataFormatada == dataAtual) {
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
            item->setText(0, consulta["nome_pet"].toString());
            item->setText(1, consulta["cpf_tutor"].toString()); // Ajustado para CPF Tutor
            item->setText(2, consulta["hora"].toString());
            item->setText(3, consulta["veterinario"].toString());
            ui->treeWidget->addTopLevelItem(item);
        }
    }

    ui->treeWidget->viewport()->update(); // Forçar atualização da interface
}




void consultasdodia::on_menuButton_2_clicked()
{
    // Botão voltar ao menu
    menu *menuScreen = new menu(); // Cria a tela menu
    menuScreen->show(); // Exibe a tela de menu
    this->close();             // Fecha a janela atual
}


void consultasdodia::on_agendamentoButton_2_clicked()
{
    // Botão Agendar Consulta
    agendamento *agendamentoScreen = new agendamento(); // Cria a tela de agendamento
    agendamentoScreen->show(); // Exibe a tela de agendamento
    this->close();             // Fecha a janela das consultas
}


void consultasdodia::on_pesquisarrButton_3_clicked()
{
    // botão de pesquisar


    QString busca = ui->lineEdit->text().trimmed().toLower();

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);

        // Verifica tanto o nome do pet (coluna 0) quanto o tutor (coluna 1)
        if (busca.isEmpty() || item->text(0).toLower().contains(busca) || item->text(1).toLower().contains(busca)) {
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }

}


void consultasdodia::on_pushButton_6_clicked()
{
    // Botão Cadastro Cliente
    cadastrocliente *cadastroScreen = new cadastrocliente(); // Cria a tela de cadastro
    cadastroScreen->show(); // Exibe a tela de cadastro
    this->close();          // Fecha a janela do menu
}

