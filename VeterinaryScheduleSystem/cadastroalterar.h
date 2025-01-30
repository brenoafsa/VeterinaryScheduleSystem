#ifndef CADASTROALTERAR_H
#define CADASTROALTERAR_H

#include <QDialog>
#include <QPushButton>  // Para os botões

namespace Ui {
class cadastroalterar;
}

class cadastroalterar : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroalterar(QWidget *parent = nullptr);
    ~cadastroalterar();

private slots:
    void on_listarClientesButton_clicked();
    void on_atualizarClienteButton_clicked();
    void on_deletarClienteButton_clicked();

    void on_consultaButton_clicked();

    void on_cancelarButton_clicked();
    void on_pushButton_6_clicked();

    void on_menuButton_clicked();

    void on_agendamentoButton_clicked();

private:
    Ui::cadastroalterar *ui;

    // Botões movidos para esta classe
    QPushButton *listarClientesButton;
    QPushButton *atualizarClienteButton;
    QPushButton *deletarClienteButton;

    QVector<QJsonObject> carregarTutores(); // Carrega tutores do arquivo JSON
    void salvarTutores(const QVector<QJsonObject> &tutores); // Salva tutores no arquivo JSON
};

#endif // CADASTROALTERAR_H
