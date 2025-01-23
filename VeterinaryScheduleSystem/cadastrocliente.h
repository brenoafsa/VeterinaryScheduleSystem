#ifndef CADASTROCLIENTE_H
#define CADASTROCLIENTE_H

#include <QDialog>

namespace Ui {
class cadastrocliente;
}

class cadastrocliente : public QDialog
{
    Q_OBJECT

public:
    explicit cadastrocliente(QWidget *parent = nullptr);
    ~cadastrocliente();

private:
    Ui::cadastrocliente *ui;
};

#endif // CADASTROCLIENTE_H
