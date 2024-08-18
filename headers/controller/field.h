#ifndef FIELD_H
#define FIELD_H
#include <string>
#include "cell.h"
#include <map>

class State
{
private:
    std::map<std::string, Cell*> cells_map;
public:
    Cell* cells_array;
    int amount_of_cells;
    int amount_of_rows;
    int amount_of_columns;
    State(Cell* cells, int curr_amount_of_cells, int curr_amount_of_rows, int curr_amount_of_columns);

    Cell* get_cell(int x, int y);
    class InvalidState {};
    class CoordsDublicate {};
    class NullCoordinates {};
};

class Field
{
private:
    State* state;

public:
    Field(State* new_state);
    ~Field();

    //void set_state(std::map<CellCoordinates*, Cell&> new_state);
    void update_state();
};

#endif
