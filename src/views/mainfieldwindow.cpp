#include "../../headers/views/mainfieldwindow.h"
#include "../../ui_mainfieldwindow.h"
#include <QComboBox>

MainFieldWindow::MainFieldWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainFieldWindow)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
}

MainFieldWindow::MainFieldWindow(MainWindow *main_window, QWidget *parent) : MainFieldWindow(parent)
{
    setFixedSize(1000,700);
    this->main_window = main_window;
    QGraphicsScene* scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(scene, this);
    QComboBox* rows_box = main_window->findChild<QComboBox*>("rows_box");
    QComboBox* columns_box = main_window->findChild<QComboBox*>("columns_box");
    QComboBox* fps_box = main_window->findChild<QComboBox*>("fps_box");
    QComboBox* random_cells_percent_box = main_window->findChild<QComboBox*>("random_cells_percent");

    view->setFixedSize(1000,700);
    scene->setSceneRect(0,0,1000,700);
    int alive_precent = random_cells_percent_box->currentText().toInt();
    int count_rows = rows_box->currentText().toInt();
    int count_columns = columns_box->currentText().toInt();
    int fps = 1000 / fps_box->currentText().toInt();

    if (main_window->get_state_is_create())
        field = new Field(0, 0, view->width(), view->height(), false, fps, main_window->get_state()->copy());
    else
    {
        field = new Field(count_rows, count_columns, 0, 0, view->width(), view->height(), false, fps);
        field->set_random_cells_alive(alive_precent);
    }
    field->cell_color = main_window->get_color_cell();
    scene->addItem(field);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
}

MainFieldWindow::~MainFieldWindow()
{
    delete field;
    delete ui;
}
