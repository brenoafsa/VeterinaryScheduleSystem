#ifndef CANCELARCONSULTA_H
#define CANCELARCONSULTA_H

#include <QDialog>

namespace Ui {
class cancelarconsulta;
}

class cancelarconsulta : public QDialog
{
    Q_OBJECT

public:
    explicit cancelarconsulta(QWidget *parent = nullptr);
    ~cancelarconsulta();

private slots:
    void on_novaconsultaButton_clicked();
    void on_menuButton_clicked();
    void on_apagarButton_clicked(); // Já existente, onde fizemos a adaptação
    void on_consultaButton_clicked();
    //void on_nomePet_cursorPositionChanged(int arg1, int arg2);

    void on_cancelarButton_2_clicked();

    void on_remarcacaoButton_clicked();

    void on_consultaButton_2_clicked();

    void on_agendamentoButton_2_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::cancelarconsulta *ui;

    // Função auxiliar para exibir uma caixa de erro
    void showErrorDialog(const QString &message);
};

#endif // CANCELARCONSULTA_H
