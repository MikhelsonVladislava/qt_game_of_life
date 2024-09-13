#include <QStringList>
#include "../../headers/views/mainfieldwindow.h"
#include "../../headers/views/field.h"
#include "../../headers/views/startstatewindowsettings.h"
#include "../../headers/views/mainwindow.h"
#include "../../ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ui->setupUi(this);
    create_interface();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_game()
{
    MainFieldWindow* main_field_window = new MainFieldWindow(this, nullptr);
    main_field_window->show();
}


void MainWindow::on_start_but_clicked()
{
    start_game();
}


void MainWindow::on_state_but_clicked()
{
    if (sub_window == nullptr)
    {
        QComboBox* rows_box = findChild<QComboBox*>("rows_box");
        QComboBox* columns_box = findChild<QComboBox*>("columns_box");
        int count_rows = rows_box->currentText().toInt();
        int count_columns = columns_box->currentText().toInt();
        StartStateWindowSettings* start_state_window = new StartStateWindowSettings(count_rows, count_columns);
        QObject::connect(start_state_window, &StartStateWindowSettings::create_state, this, &MainWindow::create_state);
        QLabel* status = findChild<QLabel*>("state_status");
        QObject::connect(this, &MainWindow::status_string, status, &QLabel::setText);
        sub_window = start_state_window;
        start_state_window->show();
    }
}

void MainWindow::create_state(State* state)
{
    state_is_create = true;
    emit status_string(created);
    if (this->state != nullptr) delete this->state;
    this->state = state;
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


void MainWindow::on_del_state_clicked()
{
    if (this->state != nullptr) delete this->state;
    state_is_create = false;
    this->state = nullptr;
    emit status_string(not_created);
}


void MainWindow::on_set_color_clicked()
{
    QColorDialog* color_window = new QColorDialog();
    QObject::connect(color_window, &QColorDialog::colorSelected, this, &MainWindow::set_color);
    color_window->show();
}

void MainWindow::set_color(const QColor &color)
{
    this->color_cell = color;
}

