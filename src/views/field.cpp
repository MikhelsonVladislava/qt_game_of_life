#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <stdlib.h>>
#include <QDateTime>
#include <QColor>
#include <ctime>
#include <QGraphicsScene>
#include <QDebug>
#include "../../headers/views/field.h"
#include "../../headers/controller/state.h"
#include "../../headers/controller/cell.h"

Field::Field(int curr_amount_of_cells, int curr_amount_of_rows, int curr_amount_of_columns, qreal x, qreal y, qreal width, qreal height)
    : QGraphicsRectItem(x, y, width, height)
{
    Cell** cells = new Cell*[curr_amount_of_columns];
    qreal cell_width = width / curr_amount_of_columns;
    int cell_count = 0;
    cell_views = new CellView[curr_amount_of_cells];
    for (int i = 0; i < curr_amount_of_columns; i++)
    {
        cells[i] = new Cell[curr_amount_of_rows];
        for (int j = 0; j < curr_amount_of_rows; j++)
        {
            cells[i][j] = Cell(i, j);
            cell_views[cell_count] = new CellView(&cells[i][j], 0, 0, cell_width, cell_width, this); // leak
            cell_count++;
        }
    }

    state = new State(cells, curr_amount_of_cells, curr_amount_of_rows, curr_amount_of_columns);
    //
    std::srand(std::time(0));
    for (int i = 0; i < curr_amount_of_columns; i++)
        for (int j = 0; j < curr_amount_of_rows; j++)
        {
            int is_alive = std::rand() % 2;
            if (is_alive)
                cells[i][j].is_alive = true;
        }
    //


    QTimer* timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(100);
}

void Field::update()
{
//    QDateTime start = QDateTime::currentDateTime();
    state->update_state();
    scene()->update();
}

void CellView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    qreal curr_x = parentItem()->x() + cell->x * width;
    qreal curr_y = parentItem()->y() + cell->y * width;
    QColor color;
    if (cell->is_alive) color = Qt::white;
    else color = Qt::black;
    painter->setPen(color);
    painter->setBrush(color);
    painter->drawRect(curr_x, curr_y, width, height);
}
