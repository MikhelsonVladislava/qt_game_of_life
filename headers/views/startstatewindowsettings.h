#ifndef STARTSTATEWINDOWSETTINGS_H
#define STARTSTATEWINDOWSETTINGS_H
#include "../../headers/controller/state.h"

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
    int count_of_rows;
    int count_of_columns;
    State* get_state();

private slots:
    void on_create_state_but_clicked();

signals:
    void rows_warning(const QString &);
    void columns_warning(const QString &);

private:
    void create_interface();
    Ui::StartStateWindowSettings *ui;
    const QString COLUMNS_WARNING = "Количество столбцов состояния не должно превосходить количества столбцов всего поля!";
    const QString ROWS_WARNING = "Количество строк состояния не должно превосходить количества строк всего поля!";
    State* state;
};

#endif // STARTSTATEWINDOWSETTINGS_H
