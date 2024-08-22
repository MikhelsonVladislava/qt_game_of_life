#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>
#include "./headers/views/field.h"

#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);

    view->setFixedSize(1000,700);
    scene->setSceneRect(0,0,1000,700);

    int count_rows = 200;
    int count_columns = 200;
    int count_cells = count_rows * count_columns;
    Field* field = new Field(count_cells, count_rows, count_columns, 0, 0, view->width(), view->height());
    scene->addItem(field);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
    return a.exec();
}
