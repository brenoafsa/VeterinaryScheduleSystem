#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

// Gerando interface
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// Classe que gerencia a janela principal (incluindo interação com o usuário)
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);     // Construtor
    ~MainWindow();                                      // Destrutor

private slots:
    // Método chamado quando o botão de login for clicado
    void on_BotaoDeEntrada_clicked();

private:
    Ui::MainWindow *ui;     // Ponteiro para a interface gráfica
    bool verificarCredenciais(const QString &nome, const QString &senha);

};
#endif
