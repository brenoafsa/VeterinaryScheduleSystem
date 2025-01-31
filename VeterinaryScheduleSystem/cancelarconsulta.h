#ifndef CANCELARCONSULTA_H
#define CANCELARCONSULTA_H

#include <QDialog>

// Gerando interface
namespace Ui {
class cancelarconsulta;
}

// Classe que gerencia a janela de cancelamento das consultas
class cancelarconsulta : public QDialog
{
    Q_OBJECT

public:
    explicit cancelarconsulta(QWidget *parent = nullptr);   // Construtor
    ~cancelarconsulta();                                    // Destrutor

private slots:
    // Funções associadas aos botões da interface gráfica.
    void on_novaconsultaButton_clicked();
    void on_menuButton_clicked();
    void on_apagarButton_clicked();
    void on_consultaButton_clicked();
    void on_cancelarButton_2_clicked();
    void on_remarcacaoButton_clicked();
    void on_consultaButton_2_clicked();
    void on_agendamentoButton_2_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::cancelarconsulta *ui;       // Ponteiro para a interface gráfica

    void showErrorDialog(const QString &message);   // Função para exibir uma caixa de erro
};

#endif
