#ifndef FIELD_H
#define FIELD_H
#include <string>
#include "cell.h"
#include <map>

class State
{
private:
    std::map<std::pair<int, int>, Cell*> cells_map;
public:
    Cell* cells_array;
    int amount_of_cells;
    int amount_of_rows;
    int amount_of_columns;
    State(Cell* cells, int curr_amount_of_cells, int curr_amount_of_rows, int curr_amount_of_columns);

    Cell* get_cell(int x, int y);
    void update_state();
    class InvalidState {};
    class CoordsDublicate {};
    class NullCoordinates {};
};

#endif
