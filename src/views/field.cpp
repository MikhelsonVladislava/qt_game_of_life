#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <stdlib.h>
#include <QDateTime>
#include <QColor>
#include <ctime>
#include <QGraphicsScene>
#include <QDebug>
#include "../../headers/views/field.h"
#include "../../headers/controller/state.h"
#include "../../headers/controller/cell.h"

Field::Field(int curr_amount_of_rows, int curr_amount_of_columns, qreal new_x, qreal new_y, qreal new_width, qreal new_height, bool is_start_state, int new_fps, bool is_static)
{
    this->is_static = is_static;
    fps = new_fps;
    x = new_x;
    y = new_y;
    width = new_width;
    height = new_height;
    count_of_rows = curr_amount_of_rows;
    count_of_columns = curr_amount_of_columns;
    cells_field_begin_y = width >= height ? 0 : (width - height) / 2;
    cells_field_begin_x = width >= height ? (width - height) / 2 : 0;
    int curr_amount_of_cells = get_count_of_cells();
    qDebug() << curr_amount_of_columns;
    Cell** cells = new Cell*[curr_amount_of_columns];
    qreal cell_width = std::min(width, height) / curr_amount_of_columns;
    int cell_count = 0;
    cell_views = new CellView*[curr_amount_of_cells];
    for (int i = 0; i < curr_amount_of_columns; i++)
    {
        cells[i] = new Cell[curr_amount_of_rows];
        for (int j = 0; j < curr_amount_of_rows; j++)
        {
            cells[i][j] = Cell(i, j);
            cell_views[cell_count] = new CellView(&cells[i][j], 0, 0, cell_width, cell_width, this); // leak
            cell_views[cell_count]->field = this;
            cell_count++;
        }
    }

    state = new State(cells, curr_amount_of_cells, curr_amount_of_rows, curr_amount_of_columns);


    if (!is_static)
    {
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
        timer->start(fps);
    }
}

void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawRect(x, y, width, height);
}

void Field::update()
{
//    QDateTime start = QDateTime::currentDateTime();
    state->update_state();
    scene()->update();
}

void CellView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    qreal curr_x = field->cells_field_begin_x + cell->x * width;
    qreal curr_y = field->cells_field_begin_y + cell->y * width;
    if (cell->is_alive)
    {
        setRect(curr_x, curr_y, width, height);
        setPen(cell_color);
        setBrush(cell_color);
        QGraphicsRectItem::paint(painter, option);
    } else if (field->is_start_state && !cell->is_alive)
    {
        setRect(curr_x, curr_y, width, height);
        setPen(cell_color);
        setBrush(Qt::black);
        QGraphicsRectItem::paint(painter, option);
    }
}
