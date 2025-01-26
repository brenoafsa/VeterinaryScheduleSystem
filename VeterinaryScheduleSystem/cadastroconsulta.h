#ifndef CADASTROCONSULTA_H
#define CADASTROCONSULTA_H

#include <QDialog>

namespace Ui {
class cadastroconsulta;
}

class cadastroconsulta : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroconsulta(QWidget *parent = nullptr);
    ~cadastroconsulta();

private slots:

    void on_pesquisarrButton_3_clicked();

private:
    Ui::cadastroconsulta *ui;
};

#endif // CADASTROCONSULTA_H
