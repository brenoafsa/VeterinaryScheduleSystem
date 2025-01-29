#ifndef MENU_H
#define MENU_H

#include <QDialog>

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
    void on_pushButton_8_clicked(); // Slot para abrir Agendamento
    void on_pushButton_6_clicked(); // Slot para abrir Cadastro Cliente
    void on_sairButton_clicked();   // Slot para o botão Sair

    void on_agendamentoButton_clicked();

    void on_consultaButton_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::menu *ui;
    MainWindow *mainWindow; // Ponteiro para a janela principal
};

#endif // MENU_H
