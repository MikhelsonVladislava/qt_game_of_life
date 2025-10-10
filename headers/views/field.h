#ifndef FIELD_H
#define FIELD_H
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QObject>
#include <QPainter>
#include "../controller/cell.h"
#include "../controller/state.h"


class Field;

class CustomView : public QGraphicsView
{
protected:
    void mousePressEvent(QMouseEvent *event)
    {

        QGraphicsView::mousePressEvent(event);
    }
public:
    using QGraphicsView::QGraphicsView;
};

class CellView: public QGraphicsRectItem
{
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        cell->is_alive = !cell->is_alive;
        scene()->update();
    }

public:
    Field* field;
    qreal get_width() {return width;}
    Cell* get_cell() {return cell;}
    ~CellView();
    CellView(Cell* new_cell = nullptr, qreal x = 0, qreal y = 0, qreal width = 0, QGraphicsRectItem *parent = nullptr)
        : QGraphicsRectItem(parent) {
        this->cell = new_cell;
        this->width = width ;
    };



    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

private:
    Cell* cell; // назначается не через new
    qreal width;

};

class Field: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    qreal width;
    qreal height;
    bool is_static;
    qreal cell_width;
    qreal cells_field_begin_x = -1;
    qreal cells_field_begin_y = -1;
    int fps;
    bool is_start_state;
    int count_of_rows;
    int count_of_columns;
    State* state;
    QTimer* timer = nullptr;

    void fix_field_size();
    void set_cell_views(State* state);
    void set_cell_width();

public:
    CellView** cell_views;
    QColor cell_color = Qt::white;
    bool is_start_state_status() {return is_start_state;};
    int get_count_of_rows() {return count_of_rows;};
    int get_count_of_columns() {return count_of_columns;};
    State* get_state() {return state;};
    qreal get_cells_field_begin_y() {return cells_field_begin_y;};
    qreal get_cells_field_begin_x() {return cells_field_begin_x;};

    Field(int curr_amount_of_rows, int curr_amount_of_columns, qreal x, qreal y, qreal width, qreal height, bool is_start_state, int fps, QGraphicsRectItem *parent = nullptr);
    Field(qreal x, qreal y, qreal width, qreal height, bool is_start_state, int fps, State* state = nullptr, QGraphicsRectItem *parent = nullptr);
    ~Field();
    void set_random_cells_alive(double alive_precent);
    int get_count_of_cells()
    {
        return count_of_rows * count_of_columns;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

public slots:
    void update();
};

#endif
