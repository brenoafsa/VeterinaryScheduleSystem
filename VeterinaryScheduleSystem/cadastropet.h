#ifndef CADASTROPET_H
#define CADASTROPET_H

#include <QDialog>

// Gerando interface
namespace Ui {
class cadastropet;
}

// Classe que gerencia a janela de cadastro de pets
class cadastropet : public QDialog {
    Q_OBJECT

public:
    explicit cadastropet(QWidget *parent = nullptr);        // Construtor
    ~cadastropet();                                         // Destrutor

private slots:
    // Funções associadas aos botões da interface gráfica.
    void cadastrarPet();
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
    void on_cancelarButton_2_clicked();

private:
    Ui::cadastropet *ui;                                    // Ponteiro para a interface gráfica
    QVector<QJsonObject> carregarDados();                   // Carrega os dados de um arquivo e retorná-los como um vetor de objetos
    void salvarDados(const QVector<QJsonObject> &dados);    // Salva os dados de volta para o arquivo
};

#endif
