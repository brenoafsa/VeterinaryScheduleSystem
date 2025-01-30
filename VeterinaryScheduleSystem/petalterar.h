#ifndef PETALTERAR_H
#define PETALTERAR_H

#include <QDialog>
#include <QVector>
#include <QJsonObject>

namespace Ui {
class petalterar;
}

class petalterar : public QDialog
{
    Q_OBJECT

public:
    explicit petalterar(QWidget *parent = nullptr);
    ~petalterar();

private slots:
    void on_listarButton_clicked();  // Slot para listar os pets
    void on_alterarButton_clicked(); // Slot para alterar dados do pet
    void on_apagarButton_clicked();  // Slot para apagar um pet

    void on_menuButton_clicked();

    void on_consultaButton_clicked();

    void on_agendamentoButton_clicked();

    void on_cancelarButton_2_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::petalterar *ui;

    QVector<QJsonObject> carregarPets();                  // Função para carregar pets do arquivo JSON
    void salvarPets(const QVector<QJsonObject> &pets);    // Função para salvar os pets no arquivo JSON
};

#endif // PETALTERAR_H
