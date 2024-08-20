#ifndef STATE_H
#define STATE_H
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
    State(Cell* cells=nullptr, int curr_amount_of_cells=0, int curr_amount_of_rows=0, int curr_amount_of_columns=0);

    Cell* get_cell(int x, int y);
    void update_state();
    class InvalidState {};
    class CoordsDublicate {};
    class NullCoordinates {};
};

#endif
