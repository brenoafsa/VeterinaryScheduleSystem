#ifndef CONSULTASDODIA_H
#define CONSULTASDODIA_H

#include <QDialog>

// Gerando interface
namespace Ui {
class consultasdodia;
}

// Classe que gerencia a tela das consultas do dia
class consultasdodia : public QDialog
{
    Q_OBJECT

public:
    explicit consultasdodia(QWidget *parent = nullptr);     // Construtor
    ~consultasdodia();                                      // Destrutor

private slots:
    // Funções associadas aos botões da interface gráfica.
    void on_menuButton_2_clicked();
    void on_agendamentoButton_2_clicked();
    void on_pesquisarrButton_3_clicked();
    void carregarConsultasDoDia();
    void on_pushButton_6_clicked();

private:
    Ui::consultasdodia *ui;     // Ponteiro para interface gráfica
};

#endif
