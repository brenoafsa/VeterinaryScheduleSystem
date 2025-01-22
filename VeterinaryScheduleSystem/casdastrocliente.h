#ifndef CASDASTROCLIENTE_H
#define CASDASTROCLIENTE_H

#include <QDialog>

namespace Ui {
class casdastrocliente;
}

class casdastrocliente : public QDialog
{
    Q_OBJECT

public:
    explicit casdastrocliente(QWidget *parent = nullptr);
    ~casdastrocliente();

private:
    Ui::casdastrocliente *ui;
};

#endif // CASDASTROCLIENTE_H
