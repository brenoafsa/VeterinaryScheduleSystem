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
    void on_pushButton_8_clicked(); // Slot para o botão pushButton_8
    void on_sairButton_clicked();

private:
    Ui::menu *ui;
    MainWindow *mainWindow; // Ponteiro para a janela principal

};

#endif // MENU_H
