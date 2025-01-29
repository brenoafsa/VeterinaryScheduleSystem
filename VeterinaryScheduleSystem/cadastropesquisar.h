#ifndef CADASTROPESQUISAR_H
#define CADASTROPESQUISAR_H

#include <QDialog>

namespace Ui {
class cadastropesquisar;
}

class cadastropesquisar : public QDialog
{
    Q_OBJECT

public:
    explicit cadastropesquisar(QWidget *parent = nullptr);
    ~cadastropesquisar();

private slots:
    void on_pesquisarrButton_3_clicked();

    void on_atualizarButton_3_clicked();

    void on_deletarButton_4_clicked();

    void on_cancelarButton_2_clicked();

    void on_clienteButton_clicked();

    void on_clienteButton_2_clicked();

    void on_agendamentoButton_2_clicked();

    void on_menuButton_2_clicked();

    void on_consultaButton_2_clicked();

private:
    Ui::cadastropesquisar *ui;


    // Função para carregar e exibir tutores e pets no TreeWidget
    void carregarTutoresEPets();

    // Função auxiliar para carregar um array JSON de um arquivo
    QJsonArray loadJsonArray(const QString &fileName);
};

#endif // CADASTROPESQUISAR_H
