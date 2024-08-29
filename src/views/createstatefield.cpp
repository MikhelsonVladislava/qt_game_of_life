#include "../../headers/views/createstatefield.h"
#include "../../headers/views/field.h"
#include "../../headers/controller/state.h"
#include "../../ui_createstatefield.h"

CreateStateField::CreateStateField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateStateField)
{
    ui->setupUi(this);
}

CreateStateField::~CreateStateField()
{
    delete ui;
}

void CreateStateField::create_interface()
{
    QGraphicsScene* scene = new QGraphicsScene();
    CustomView* view = new CustomView(this);
    view->setScene(scene);

    scene->setSceneRect(0,0,this->width(), this->height() * 0.9);
    view->setFixedSize(this->width(), this->height() * 0.9);

    field = new Field(count_of_rows, count_of_columns, 0, 0, view->width(), view->height(), true, 0, true);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->addItem(field);
}

void CreateStateField::on_create_but_clicked()
{
}

