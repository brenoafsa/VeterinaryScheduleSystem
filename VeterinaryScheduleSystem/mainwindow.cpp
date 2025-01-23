#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"  // Inclua o cabeçalho da nova tela
#include "database.h"  // Inclua o cabeçalho do banco de dados
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BotaoDeEntrada_clicked()
{
    QString nome = ui->txt_nome->text().trimmed();  // Remover espaços extras
    QString senha = ui->txt_senha->text().trimmed();  // Remover espaços extras

    if (verificarCredenciais(nome, senha)) {
        // Login bem-sucedido, cria e exibe a tela de menu
        menu *menuScreen = new menu(this); // Passa a instância da MainWindow
        menuScreen->setAttribute(Qt::WA_DeleteOnClose); // Garante que o menu seja deletado ao fechar
        menuScreen->show();

        // Fecha a janela atual (MainWindow)
        this->hide();

    } else {
        // Login falhou, exibe mensagem de erro
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("<font color='black'>Usuário ou senha incorretos!</font>");
        msgBox.setWindowTitle("Login");

        // Define explicitamente as cores de fundo e texto
        msgBox.setStyleSheet("QMessageBox { background-color: white; color: black; }");

        msgBox.exec();
    }
}

bool MainWindow::verificarCredenciais(const QString &nome, const QString &senha) {
    // Acessa o banco de dados para buscar a senha associada ao nome de usuário
    Database& db = Database::getInstance();

    // Obtém as senhas associadas ao nome (a chave)
    std::vector<QString> senhas = db.getData(nome);

    // Verifica se a senha existe no banco de dados para o nome de usuário
    for (const auto& storedSenha : senhas) {
        if (storedSenha == senha) {
            return true;  // Login bem-sucedido
        }
    }
    return false;  // Senha ou usuário incorreto
}
