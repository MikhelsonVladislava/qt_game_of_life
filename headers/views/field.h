#ifndef FIELD_H
#define FIELD_H
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QObject>
#include <QDebug>
#include <QPainter>
#include "../controller/cell.h"
#include "../controller/state.h"

class Field;

class CellView: public QGraphicsRectItem
{
public:
    Cell* cell;
    Field* field;
    qreal width;
    qreal height;
    CellView(Cell* new_cell = nullptr, qreal x = 0, qreal y = 0, qreal new_width = 0, qreal new_height = 0, QGraphicsItem *parent = nullptr)
        : QGraphicsRectItem(parent) {
        cell = new_cell;
        width = new_height;
        height = new_height;
    };

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

    CellView& operator=(CellView &other) {
        this->~CellView();
      return *new(this) CellView(other.cell, other.x(), other.y(), other.width, other.height);
    }

    CellView& operator=(CellView *other) {
        this->~CellView();
      return *new(this) CellView(other->cell, other->x(), other->y(), other->width, other->height);
    }
};

class Field: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    qreal x;
    qreal y;
    qreal height;
    qreal width;
    CellView* cell_views;
    State* state;
    Field(int curr_amount_of_cells, int curr_amount_of_rows, int curr_amount_of_columns, qreal x, qreal y, qreal width, qreal height);
    //void update_view();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

public slots:
    void update();
};

#endif
