#ifndef FIELD_H
#define FIELD_H
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QObject>
#include <QDebug>
#include <QPainter>
#include "../controller/cell.h"
#include "../controller/state.h"


class Field;
//class CustomScene : public QGraphicsScene
//{
//protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event)
//    {

//        QGraphicsScene::mousePressEvent(event);
//    }
//public:
//    using QGraphicsScene::QGraphicsScene;
//};

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
        qDebug() << "Custom view clicked.";
        cell->is_alive = !cell->is_alive;
        scene()->update();
    }

public:
    Cell* cell;
    QColor cell_color = Qt::white;
    qreal width;
    qreal height;
    Field* field;
    CellView(Cell* new_cell = nullptr, qreal x = 0, qreal y = 0, qreal new_width = 0, qreal new_height = 0, QGraphicsRectItem *parent = nullptr)
        : QGraphicsRectItem(parent) {
        cell = new_cell;
        width = new_height;
        height = new_height;
    };



    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
};

class Field: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    qreal x;
    qreal y;
    qreal height;
    qreal width;
    qreal cells_field_begin_y = -1;
    qreal cells_field_begin_x = -1;
    bool is_static;
    bool is_start_state;
    int count_of_rows = 200;
    int fps = 100;
    int count_of_columns = 200;
    CellView** cell_views;
    State* state;
    Field(int curr_amount_of_rows, int curr_amount_of_columns, qreal x, qreal y, qreal width, qreal height, bool is_start_state, int new_fps, bool is_static);
    int get_count_of_cells()
    {
        return count_of_rows * count_of_columns;
    }
    //void update_view();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

public slots:
    void update();
};

#endif
