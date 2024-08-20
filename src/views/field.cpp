#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QColor>
#include <QGraphicsScene>
#include "../../headers/views/field.h"
#include "../../headers/controller/state.h"
#include "../../headers/controller/cell.h"
#include "../../headers/views/cell_view.h"

Field::Field(int curr_amount_of_cells, int curr_amount_of_rows, int curr_amount_of_columns, qreal x, qreal y, qreal width, qreal height)
    : QGraphicsRectItem(x, y, width, height)
{
    Cell* cells = new Cell[curr_amount_of_cells]; // leak
    qreal cell_width = width / curr_amount_of_columns;
    int cell_count = 0;
    cell_views = new CellView[curr_amount_of_cells];
    for (int i = 0; i < curr_amount_of_cells; i++)
    {
        cells[i] = Cell();
        cell_views[cell_count] = *new CellView(&cells[i], 0, 0, cell_width, cell_width, this);
        cell_count++;
    }

    state = new State(cells, curr_amount_of_cells, curr_amount_of_rows, curr_amount_of_columns);
    state->get_cell(100, 100)->is_alive = true;
    state->get_cell(100, 102)->is_alive = true;
    state->get_cell(100, 101)->is_alive = true;
    state->get_cell(101, 101)->is_alive = true;

    QTimer* timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(200);
}

void Field::update()
{
    state->update_state();
    scene()->update();
}

void CellView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    qreal curr_x = parentItem()->x() + cell->get_coordinates()->x * width;
    qreal curr_y = parentItem()->y() + cell->get_coordinates()->y * width;
    QColor color;
    if (cell->is_alive) color = Qt::white;
    else color = Qt::black;
    painter->setPen(color);
    painter->setBrush(color);
    painter->drawRect(curr_x, curr_y, width, height);
}
