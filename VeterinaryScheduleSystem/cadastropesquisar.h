#ifndef CADASTROPESQUISAR_H
#define CADASTROPESQUISAR_H

#include <QDialog>

// Gerando a interface gráfica
namespace Ui {
class cadastropesquisar;
}

// Classe para gerenciar a janela de pesquisa de clientes
class cadastropesquisar : public QDialog
{
    Q_OBJECT

public:
    explicit cadastropesquisar(QWidget *parent = nullptr);  // Construtor
    ~cadastropesquisar();                                   // Destrutor

private slots:
    // Funções associadas aos botões da interface gráfica.
    void on_pesquisarrButton_3_clicked();
    void on_clienteButton_clicked();
    void on_clienteButton_2_clicked();
    void on_agendamentoButton_2_clicked();
    void on_menuButton_2_clicked();
    void on_consultaButton_2_clicked();

private:
    Ui::cadastropesquisar *ui;      // Ponteiro para interface do usuário

    void carregarTutoresEPets();        // Carrega e exibe os tutores e pets no TreeWidget

    QJsonArray loadJsonArray(const QString &fileName);     // Ajuda a carregar um array JSON de um arquivo
};

#endif
