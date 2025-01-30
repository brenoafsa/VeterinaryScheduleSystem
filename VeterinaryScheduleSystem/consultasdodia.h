#ifndef CONSULTASDODIA_H
#define CONSULTASDODIA_H

#include <QDialog>

namespace Ui {
class consultasdodia;
}

class consultasdodia : public QDialog
{
    Q_OBJECT

public:
    explicit consultasdodia(QWidget *parent = nullptr);
    ~consultasdodia();

private slots:
    void on_menuButton_2_clicked();

    void on_agendamentoButton_2_clicked();

    void on_pesquisarrButton_3_clicked();

    void carregarConsultasDoDia(); // Método para carregar consultas do dia


    void on_pushButton_6_clicked();

private:
    Ui::consultasdodia *ui;
};

#endif // CONSULTASDODIA_H
