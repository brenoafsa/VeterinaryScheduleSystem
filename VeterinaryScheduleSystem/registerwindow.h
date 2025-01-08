#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_confirmButton();

private:
    Ui::RegisterWindow *ui;
    QSqlDatabase db;
};

#endif // REGISTERWINDOW_H
