#ifndef PETALTERAR_H
#define PETALTERAR_H

#include <QDialog>
#include <QVector>
#include <QJsonObject>

// Gerando interface
namespace Ui {
class petalterar;
}

// Classe que gerencia a modificação dos dados do pet
class petalterar : public QDialog
{
    Q_OBJECT

public:
    explicit petalterar(QWidget *parent = nullptr);     // Construtor
    ~petalterar();                                      // Destrutor

private slots:
    // Funções associadas aos botões da interface gráfica.
    void on_listarButton_clicked();
    void on_alterarButton_clicked();
    void on_apagarButton_clicked();
    void on_menuButton_clicked();
    void on_consultaButton_clicked();
    void on_agendamentoButton_clicked();
    void on_cancelarButton_2_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::petalterar *ui;         // Ponteiro para a interface gráfica

    QVector<QJsonObject> carregarPets();                  // Carregando pets do arquivo JSON
    void salvarPets(const QVector<QJsonObject> &pets);    // Salvando os pets no arquivo JSON
};

#endif
