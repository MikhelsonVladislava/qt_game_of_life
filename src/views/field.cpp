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
{
    Cell* cells = new Cell[curr_amount_of_cells]; // leak
    cell_views = new CellView[curr_amount_of_cells];
    for (int i = 0; i < curr_amount_of_cells; i++)
        cells[i] = Cell();

    int cell_count = 0;

    qreal cell_width = width / curr_amount_of_columns;
    state = new State(cells, curr_amount_of_cells, curr_amount_of_rows, curr_amount_of_columns);
    for (int i = 0; i < curr_amount_of_columns; i++)
        for (int j = 0; j < curr_amount_of_rows; j++)
        {
            CellView* curr_cell = new CellView(state->get_cell(i,j), 0, 0, cell_width, cell_width, this);
            curr_cell->field = this;
            // rebuild
            if ((curr_cell->cell->get_coordinates()->x == 100 && (curr_cell->cell->get_coordinates()->y == 100
                                                                 || curr_cell->cell->get_coordinates()->y == 101
                                                                 || curr_cell->cell->get_coordinates()->y == 99)) ||
                    (curr_cell->cell->get_coordinates()->x == 99 && (curr_cell->cell->get_coordinates()->y == 100)))
                curr_cell->cell->is_alive = true;
            cell_views[cell_count] = *curr_cell; // хрень какая-то
            cell_count++;
            // rebuild
        }

    QTimer* timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(500);
}

void Field::update()
{
    state->update_state();
    scene()->update();
}

void CellView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    qreal curr_x = field->x() + cell->get_coordinates()->x * width;
    qreal curr_y = field->y() + cell->get_coordinates()->y * width;
    QColor color;
    if (cell->is_alive) color = Qt::white;
    else color = Qt::black;
    painter->setPen(color);
    painter->setBrush(color);
    painter->drawRect(curr_x, curr_y, width, height);
}
