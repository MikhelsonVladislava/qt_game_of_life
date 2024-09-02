#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPointer>
#include "startstatewindowsettings.h"
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

    void start_game();

signals:
    void status_string(const QString &);

private slots:
    void on_start_but_clicked();
    void on_exit_but_clicked();
    void on_state_but_clicked();
    void create_state(State* state);

private:
    QPointer<StartStateWindowSettings> sub_window = nullptr;
    bool state_is_create = false;
    State* state = nullptr;
    const QString created = "задано";
    const QString not_created = "не задано";
    void create_interface();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
