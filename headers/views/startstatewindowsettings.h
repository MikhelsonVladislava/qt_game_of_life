#ifndef STARTSTATEWINDOWSETTINGS_H
#define STARTSTATEWINDOWSETTINGS_H
#include "createstatefield.h"
#include "../../headers/controller/state.h"

#include <QPointer>
#include <QWidget>
#include <QString>

namespace Ui {
class StartStateWindowSettings;
}

class StartStateWindowSettings : public QWidget
{
    Q_OBJECT

public:
    explicit StartStateWindowSettings(QWidget *parent = nullptr);
    StartStateWindowSettings(int count_of_rows, int count_of_columns, QWidget *parent = nullptr)
        : StartStateWindowSettings(nullptr)
    {
        this->count_of_rows = count_of_rows;
        this->count_of_columns = count_of_columns;
    };
    ~StartStateWindowSettings();

private slots:
    void on_create_state_but_clicked();
    void close_creator_state(State* state);

signals:
    void rows_warning(const QString &);
    void columns_warning(const QString &);
    void create_state(State* state);

private:
    int count_of_rows;
    int count_of_columns;
    QPointer<CreateStateField> sub_window = nullptr;
    void create_interface();
    Ui::StartStateWindowSettings *ui;
    State* get_full_state(State* state);
    const QString COLUMNS_WARNING = "Количество столбцов состояния не должно превосходить количества столбцов всего поля!";
    const QString ROWS_WARNING = "Количество строк состояния не должно превосходить количества строк всего поля!";
};

#endif // STARTSTATEWINDOWSETTINGS_H
