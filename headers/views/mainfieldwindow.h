#ifndef MAINFIELDWINDOW_H
#define MAINFIELDWINDOW_H
#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class MainFieldWindow;
}

class MainFieldWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainFieldWindow(QWidget *parent = nullptr);
    MainFieldWindow(MainWindow* main_window, QWidget *parent = nullptr);
    ~MainFieldWindow();

private:
    void create_interface();
    MainWindow* main_window;
    Field* field = nullptr;
    Ui::MainFieldWindow *ui;
};

#endif // MAINFIELDWINDOW_H
