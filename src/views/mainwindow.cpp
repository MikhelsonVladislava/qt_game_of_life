#include <QStringList>
#include "../../headers/views/field.h"
#include "../../headers/views/startstatewindowsettings.h"
#include "../../headers/views/mainwindow.h"
#include "../../ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    create_interface();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_game()
{
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    QComboBox* rows_box = findChild<QComboBox*>("rows_box");
    QComboBox* columns_box = findChild<QComboBox*>("columns_box");
    QComboBox* fps_box = findChild<QComboBox*>("fps_box");
    QComboBox* random_cells_percent_box = findChild<QComboBox*>("random_cells_percent");

    view->setFixedSize(1000,700);
    scene->setSceneRect(0,0,1000,700);

    int count_rows = rows_box->currentText().toInt();
    int count_columns = columns_box->currentText().toInt();
    int fps = 1000 / fps_box->currentText().toInt();
    Field* field = new Field(count_rows, count_columns, 0, 0, view->width(), view->height(), false, fps, false);
    scene->addItem(field);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
}


void MainWindow::on_start_but_clicked()
{
    start_game();
}


void MainWindow::on_state_but_clicked()
{
    QComboBox* rows_box = findChild<QComboBox*>("rows_box");
    QComboBox* columns_box = findChild<QComboBox*>("columns_box");
    int count_rows = rows_box->currentText().toInt();
    int count_columns = columns_box->currentText().toInt();
    StartStateWindowSettings* start_state_window = new StartStateWindowSettings(count_rows, count_columns);
    start_state_window->show();
}


void MainWindow::on_exit_but_clicked()
{

}

void MainWindow::create_interface()
{
    QStringList rows_box_variants = (QStringList() << "10" << "50"  << "100" << "200" << "300");
    QStringList columns_box_variants  = rows_box_variants;

    QComboBox* rows_box = findChild<QComboBox*>("rows_box");
    QComboBox* columns_box = findChild<QComboBox*>("columns_box");
    rows_box->addItems(rows_box_variants);
    columns_box->addItems(columns_box_variants);

    QStringList fps_box_variants = (QStringList() << "10" << "5"  << "1");
    QComboBox* fps_box = findChild<QComboBox*>("fps_box");
    fps_box->addItems(fps_box_variants);

    QStringList random_cells_percent_box_variants = (QStringList() << "10" << "30"  << "50" << "70" << "90");
    QComboBox* random_cells_percent_box = findChild<QComboBox*>("random_cells_percent");
    random_cells_percent_box->addItems(random_cells_percent_box_variants);
}

