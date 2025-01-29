#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <QDialog>

namespace Ui {
class agendamento;
}

class agendamento : public QDialog
{
    Q_OBJECT

public:
    explicit agendamento(QWidget *parent = nullptr);
    ~agendamento();

private slots:
    void on_menuButton_clicked();

    void on_remarcacaoButton_clicked();

    void on_consultaButton_clicked();

private:
    Ui::agendamento *ui;
};

#endif // AGENDAMENTO_H
