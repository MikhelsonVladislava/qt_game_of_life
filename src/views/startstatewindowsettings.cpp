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
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setAttribute(Qt::WA_DeleteOnClose);
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
    warning->setStyleSheet(warning_stylesheet);
    QObject::connect(this, &StartStateWindowSettings::show_warning, warning, &QLabel::setText);

    rows->setInputMask("999");
    columns->setInputMask("999");
}

State *StartStateWindowSettings::get_full_state(State *state)
{
    state->supp_state(count_of_rows, count_of_columns);
    return state;
}

void StartStateWindowSettings::on_create_state_but_clicked()
{
    QLineEdit* rows = findChild<QLineEdit*>("rows_field");
    QLineEdit* columns = findChild<QLineEdit*>("columns_field");

    int rows_count_input = rows->displayText().toInt();
    int columns_count_input = columns->displayText().toInt();
    if (rows->displayText().isEmpty() || columns->displayText().isEmpty()) emit show_warning(COUNT_WARNING);
    else if (rows_count_input > count_of_rows) emit show_warning(ROWS_WARNING);
    else if (columns_count_input > count_of_columns) emit show_warning(COLUMNS_WARNING);
    else if (columns_count_input > 100 || rows_count_input > 100) emit show_warning(H_WARNING);
    else if (columns_count_input == 0 || rows_count_input == 0) emit show_warning(COUNT_WARNING);
    else {
        if (sub_window == nullptr)
        {
            CreateStateField* create_window = new CreateStateField(rows_count_input, columns_count_input);
            QObject::connect(create_window, &CreateStateField::close_creator_state, this, &StartStateWindowSettings::close_creator_state);
            sub_window = create_window;
            create_window->show();
        }
    }
}

void StartStateWindowSettings::close_creator_state(State* state)
{
    State* full_state = get_full_state(state);
    emit create_state(full_state);
    close();
}

