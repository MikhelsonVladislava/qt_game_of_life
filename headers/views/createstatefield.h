#ifndef CREATESTATEFIELD_H
#define CREATESTATEFIELD_H

#include "field.h"
#include <QWidget>


namespace Ui {
class CreateStateField;
}

class CreateStateField : public QWidget
{
    Q_OBJECT

public:
    explicit CreateStateField(QWidget *parent = nullptr);
    CreateStateField(int count_of_rows, int count_of_columns, QWidget *parent = nullptr)
        : CreateStateField(parent)
    {
        this->count_of_rows = count_of_rows;
        this->count_of_columns = count_of_columns;
        create_interface();
    };
    ~CreateStateField();

signals:
    void close_creator_state(State* state);

private slots:
    void on_create_but_clicked();

private:
    int count_of_rows;
    int count_of_columns;
    Field* field;
    void create_interface();
    Ui::CreateStateField *ui;
};

#endif // CREATESTATEFIELD_H
