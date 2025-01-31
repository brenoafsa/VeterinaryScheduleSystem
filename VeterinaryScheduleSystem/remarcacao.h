#ifndef REMARCACAO_H
#define REMARCACAO_H

#include <QDialog>

// Gerando interface
namespace Ui {
class remarcacao;
}

// Classe que gerencia a janela de remarcação das consultas
class remarcacao : public QDialog
{
    Q_OBJECT

public:
    explicit remarcacao(QWidget *parent = nullptr);     // Construtor
    ~remarcacao();                                      // Destrutor

private slots:
    // Funções associadas aos botões da interface gráfica.
    void on_novaconsultaButton_clicked();
    void on_menuButton_clicked();
    void on_alterarButton_clicked();
    void on_consultaButton_clicked();
    void on_cancelarconsultaButton_clicked();
    void on_nomePet_cursorPositionChanged(int arg1, int arg2);
    void on_cancelarButton_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::remarcacao *ui;     // Ponteiro para interface gráfica
    void showErrorDialog(const QString &message);   // Exibe uma caixa de erro
};

#endif
