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

    void on_pushButton_10_clicked();

    void on_cancelarconsultaButton_clicked();

private:
    Ui::agendamento *ui;
    QJsonArray loadJsonArray(const QString &filename);
    bool saveConsulta(const QJsonObject &consulta);
    void showErrorDialog(const QString &message);
};

#endif // AGENDAMENTO_H
