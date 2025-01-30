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
    void on_alterarButton_clicked(); // Já existente, onde fizemos a adaptação
    void on_consultaButton_clicked();
    void on_cancelarconsultaButton_clicked();
    void on_nomePet_cursorPositionChanged(int arg1, int arg2);

    void on_cancelarButton_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::remarcacao *ui;

    // Função auxiliar para exibir uma caixa de erro
    void showErrorDialog(const QString &message);
};

#endif // REMARCACAO_H
