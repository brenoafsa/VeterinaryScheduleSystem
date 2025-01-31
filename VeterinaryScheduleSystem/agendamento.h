#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <QDialog>

// Interface gerada pelo Qt Designer
namespace Ui {
class agendamento;
}

// Classe que representa a janela de agendamento no sistema
class agendamento : public QDialog
{
    Q_OBJECT

public:
    explicit agendamento(QWidget *parent = nullptr);    // Construtor
    ~agendamento();                                     // Destrutor

private slots:
    // Funções chamadas pelos botões da interface gráfica.
    void on_menuButton_clicked();
    void on_remarcacaoButton_clicked();
    void on_consultaButton_clicked();
    void on_pushButton_10_clicked();
    void on_cancelarconsultaButton_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::agendamento *ui;                                    // Ponteiro para interface
    QJsonArray loadJsonArray(const QString &filename);      // Carrega um array de objetos JSON de um arquivo
    bool saveConsulta(const QJsonObject &consulta);         // Função que salva as consultas (com os dados recebidos em um objeto JSON)
    void showErrorDialog(const QString &message);           // Mensagem de erro
};

#endif
