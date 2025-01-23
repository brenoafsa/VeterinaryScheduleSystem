#ifndef CADASTROPET_H
#define CADASTROPET_H

#include <QDialog>

namespace Ui {
class cadastropet;
}

class cadastropet : public QDialog
{
    Q_OBJECT

public:
    explicit cadastropet(QWidget *parent = nullptr);
    ~cadastropet();

private:
    Ui::cadastropet *ui;
};

#endif // CADASTROPET_H
