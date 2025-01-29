#ifndef REMARCACAO_H
#define REMARCACAO_H

#include <QDialog>

namespace Ui {
class remarcacao;
}

class remarcacao : public QDialog
{
    Q_OBJECT

public:
    explicit remarcacao(QWidget *parent = nullptr);
    ~remarcacao();

private slots:
    void on_novaconsultaButton_clicked();

    void on_menuButton_clicked();

    void on_agendamentoButton_clicked();

    void on_consultaButton_clicked();

private:
    Ui::remarcacao *ui;
};

#endif // REMARCACAO_H
