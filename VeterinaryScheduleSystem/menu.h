#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_pushButton_8_clicked(); // Slot para o botão pushButton_8

private:
    Ui::menu *ui;
};

#endif // MENU_H
