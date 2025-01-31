#ifndef CADASTROALTERAR_H
#define CADASTROALTERAR_H

#include <QDialog>
#include <QPushButton>  // Para criar e manipular os botões

// Interface gerada pelo Qt Designer
namespace Ui {
class cadastroalterar;
}

// Classe que representa a janela de cadastro e alteração dos dados cadastrados
class cadastroalterar : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroalterar(QWidget *parent = nullptr);        // Construtor
    ~cadastroalterar();                                         // Destrutor

private slots:
    // Funções associadas aos botões da interface.
    void on_listarClientesButton_clicked();
    void on_atualizarClienteButton_clicked();
    void on_deletarClienteButton_clicked();
    void on_consultaButton_clicked();
    void on_cancelarButton_clicked();
    void on_pushButton_6_clicked();
    void on_menuButton_clicked();
    void on_agendamentoButton_clicked();

private:
    Ui::cadastroalterar *ui;        // Ponteiro para a interface do usuário

    // Botões movidos para esta classe para ter um controle direto
    QPushButton *listarClientesButton;
    QPushButton *atualizarClienteButton;
    QPushButton *deletarClienteButton;

    QVector<QJsonObject> carregarTutores();                         // Aqui está carregando tutores do arquivo JSON
    void salvarTutores(const QVector<QJsonObject> &tutores);        // Salvamos os dados de tutores no arquivo JSON
};

#endif
