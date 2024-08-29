#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../../headers/controller/state.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    State* state = nullptr;

    void start_game();
    void exit();
    void set_state();

private slots:
    void on_start_but_clicked();

    void on_exit_but_clicked();

    void on_state_but_clicked();

private:
    void create_interface();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
