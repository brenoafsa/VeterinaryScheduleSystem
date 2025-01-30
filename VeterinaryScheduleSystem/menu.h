#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QTreeWidget>  // Incluir o QTreeWidget para exibir as consultas
#include <QVector>      // Necessário para QVector
#include <QJsonObject>  // Necessário para QJsonObject

class MainWindow; // Forward declaration

namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(MainWindow *parent = nullptr);  // Certifique-se de que essa linha está presente
    ~menu();

private slots:
    void on_pushButton_6_clicked(); // Slot para abrir Cadastro Cliente
    void on_sairButton_clicked();   // Slot para o botão Sair
    void on_agendamentoButton_clicked();
    void on_consultaButton_clicked();

    // Função que será chamada para carregar as consultas do dia
    void carregarConsultas();

private:
    Ui::menu *ui;
    MainWindow *mainWindow; // Ponteiro para a janela principal

    // Função que carrega os tutores do JSON
    QVector<QJsonObject> carregarTutores();  // Declarando corretamente a função carregarTutores

    // Adicionando o QTreeWidget para exibir as consultas
    QTreeWidget *treeWidget; // Declarando o QTreeWidget
};

#endif // MENU_H
