
#include <iostream>
#include <QApplication>
#include <QGraphicsItem>
#include "./headers/views/mainwindow.h"
#include <QObject>


#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* window = new MainWindow();

    window->show();
    return a.exec();
}
