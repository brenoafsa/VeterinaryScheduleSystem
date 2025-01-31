#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QTreeWidget>  // Incluir o QTreeWidget para exibir as consultas
#include <QVector>      // Necessário para QVector
#include <QJsonObject>  // Necessário para QJsonObject

class MainWindow; // Forward declaration

// Gerando interface
namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(MainWindow *parent = nullptr);    // Construtor
    ~menu();                                        // Destrutor

private slots:
    // Funções associadas aos botões da interface gráfica.
    void on_pushButton_6_clicked();
    void on_sairButton_clicked();
    void on_agendamentoButton_clicked();
    void on_consultaButton_clicked();

    // Função chamada para carregar as consultas do dia
    void carregarConsultas();

private:
    Ui::menu *ui;               // Ponteiro para a interface gráfica
    MainWindow *mainWindow;     // Ponteiro para a janela principal

    QVector<QJsonObject> carregarTutores();  // Função que carrega os tutores do JSON
    QTreeWidget *treeWidget;                // Ponteiro para o QTreeWidget que exibe as consultas
};

#endif
