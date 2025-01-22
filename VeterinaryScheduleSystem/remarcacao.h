#ifndef REMARCACAO_H
#define REMARCACAO_H

#include <QDialog>

namespace Ui {
class remarcacao;
}

class remarcacao : public QDialog
{
    Q_OBJECT

public:
    explicit remarcacao(QWidget *parent = nullptr);
    ~remarcacao();

private:
    Ui::remarcacao *ui;
};

#endif // REMARCACAO_H
