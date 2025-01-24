#ifndef CADASTROPET_H
#define CADASTROPET_H

#include <QDialog>

namespace Ui {
class cadastropet;
}

class cadastropet : public QDialog
{
    Q_OBJECT

public:
    explicit cadastropet(QWidget *parent = nullptr);
    ~cadastropet();

private slots:
    void on_menuButton_clicked();

    void on_clienteButton_2_clicked();

private:
    Ui::cadastropet *ui;
};

#endif // CADASTROPET_H
