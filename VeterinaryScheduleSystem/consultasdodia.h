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

private:
    Ui::consultasdodia *ui;
};

#endif // CONSULTASDODIA_H
