#ifndef CADASTROPET_H
#define CADASTROPET_H

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

#endif // CADASTROPET_H
