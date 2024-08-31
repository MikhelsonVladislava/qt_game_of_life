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

void Field::fix_field_size()
{
    cells_field_begin_y = width >= height ? 0 : (height - cell_width * count_of_rows) / 2;
    cells_field_begin_x = width >= height ? (width - cell_width * count_of_columns) / 2 : 0;
}

void Field::set_cell_views(State *state)
{
    int curr_amount_of_cells = get_count_of_cells();
    if (width < height) cell_width = width /count_of_columns;
    else cell_width = height /count_of_rows;
    int cell_count = 0;
    cell_views = new CellView*[curr_amount_of_cells];
    for (int i = 0; i < count_of_columns; i++)
    {
        for (int j = 0; j < count_of_rows; j++)
        {
            cell_views[cell_count] = new CellView(&state->cells_array[i][j], 0, 0, cell_width, this); // leak
            cell_views[cell_count]->field = this;
            cell_count++;
        }
    }

}

Field::Field(int curr_amount_of_rows, int curr_amount_of_columns, qreal x, qreal y, qreal width, qreal height, bool is_start_state, int fps, QGraphicsRectItem *parent)
    : Field(x, y, width, height, is_start_state, fps, nullptr, parent)
{
    this->count_of_rows = curr_amount_of_rows;
    this->count_of_columns = curr_amount_of_columns;

    Cell** cells = new Cell*[curr_amount_of_columns];
    for (int i = 0; i < curr_amount_of_columns; i++)
    {
        cells[i] = new Cell[curr_amount_of_rows];
        for (int j = 0; j < curr_amount_of_rows; j++)
            cells[i][j] = Cell(i, j);
    }

    state = new State(cells, curr_amount_of_rows, curr_amount_of_columns);
    set_cell_views(state);
    fix_field_size();

}

Field::Field(qreal x, qreal y, qreal width, qreal height, bool is_start_state, int fps, State *state, QGraphicsRectItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent)
{
    this->is_start_state = is_start_state;
    this->fps = fps;
    this->width = width;
    this->height = height;

    if (!fps) is_static = true;
    else is_static = false;

    this->state = state;
    if (state != nullptr)
    {
        count_of_rows = state->amount_of_rows;
        count_of_columns = state->amount_of_columns;
        set_cell_views(state);


        fix_field_size();
    }

    if (!is_static)
    {
        QTimer* timer = new QTimer;
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(update()));
        timer->start(fps);
    }
}

void Field::set_random_cells_alive(double alive_precent)
{

    std::srand(std::time(0));
    int amount_of_cells = get_count_of_cells();
    for (int j = 0; j < amount_of_cells; j++)
    {
        int is_alive_choose = std::rand() % 10;
        if (0 <= is_alive_choose && is_alive_choose <= alive_precent / 10 - 1)
            cell_views[j]->cell->is_alive = true;
    }
}

void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawRect(x(), y(), width, height);
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
        setRect(curr_x, curr_y, width, width);
        setPen(cell_color);

        setBrush(cell_color);
        QGraphicsRectItem::paint(painter, option);
    } else if (field->is_start_state && !cell->is_alive)
    {
        setRect(curr_x, curr_y, width, width);
        setPen(cell_color);
        setBrush(Qt::black);
        QGraphicsRectItem::paint(painter, option);
    }
}
