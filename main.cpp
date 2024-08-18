#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "./headers/controller/cell.h"
#include "./headers/controller/field.h"
#include "./headers/controller/game.h"

#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);

    int count_rows = 1000;
    int count_columns = 1000;
    int count_cells = count_rows * count_columns;
    Cell* cells = new Cell[count_cells];
    for (int i = 0; i < count_cells; i++)
        cells[i] = Cell();
    State* state = new State(cells, count_cells, count_rows, count_columns);

    state->get_cell(3, 4)->is_alive = true;
    state->get_cell(3, 5)->is_alive = true;
    state->get_cell(3, 6)->is_alive = true;
    state->get_cell(2, 5)->is_alive = true;
    state->update_state();

    for (int i = 0; i < count_cells; i++)
    {
        if (cells[i].is_alive)
            qDebug() << qDebug().toString(cells[i].get_coordinates()->x) << qDebug().toString(cells[i].get_coordinates()->y);
    }
    view->show();
    return a.exec();
}
