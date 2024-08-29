#include <QLabel>
#include  <QLineEdit>

#include "../../headers/views/createstatefield.h"
#include "../../headers/views/startstatewindowsettings.h"
#include "../../ui_startstatewindowsettings.h"
#include "../../headers/views/field.h"

StartStateWindowSettings::StartStateWindowSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartStateWindowSettings)
{
    ui->setupUi(this);
    create_interface();
}

StartStateWindowSettings::~StartStateWindowSettings()
{
    delete ui;
}

void StartStateWindowSettings::create_interface()
{
    QLineEdit* rows = findChild<QLineEdit*>("rows_field");
    QLineEdit* columns = findChild<QLineEdit*>("columns_field");
    QLabel* warning = findChild<QLabel*>("warning_label");
    QObject::connect(this, &StartStateWindowSettings::rows_warning, warning, &QLabel::setText);
    QObject::connect(this, &StartStateWindowSettings::columns_warning, warning, &QLabel::setText);

    rows->setInputMask("999");
    columns->setInputMask("999");
}

void StartStateWindowSettings::on_create_state_but_clicked()
{
    QLineEdit* rows = findChild<QLineEdit*>("rows_field");
    QLineEdit* columns = findChild<QLineEdit*>("columns_field");

    int rows_count_input = rows->displayText().toInt();
    int columns_count_input = columns->displayText().toInt();
    if (rows_count_input > count_of_rows) emit rows_warning(ROWS_WARNING);
    else if (columns_count_input > count_of_columns) emit columns_warning(COLUMNS_WARNING);
    else {
        CreateStateField* create_window = new CreateStateField(rows_count_input, columns_count_input);
        create_window->show();
    }
}

