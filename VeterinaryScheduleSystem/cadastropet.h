#ifndef CADASTROPET_H
#define CADASTROPET_H

#include <QDialog>

namespace Ui {
class cadastropet;  // Nome da classe
}

class cadastropet : public QDialog {
    Q_OBJECT

public:
    explicit cadastropet(QWidget *parent = nullptr);
    ~cadastropet();

private slots:
    void cadastrarPet();  // Adicione a declaração do método aqui.

    void on_cadastrarButton_2_clicked();

    void on_ListarPets_clicked();

    void on_AtualizarPet_clicked();

    void on_DeletarPet_clicked();

    void on_clienteButton_2_clicked();

    void on_pesquisarButton_2_clicked();

    void on_telaButton_clicked();

    void on_menuButton_clicked();

    void on_agendamentoButton_clicked();

    void on_consultaButton_clicked();

private:
    Ui::cadastropet *ui;
    QVector<QJsonObject> carregarDados();
    void salvarDados(const QVector<QJsonObject> &dados);
};

#endif // CADASTROPET_H
