#ifndef STATE_H
#define STATE_H
#include <string>
#include "cell.h"
#include <map>

class State
{
public:
    Cell** cells_array;
    int amount_of_rows;
    int amount_of_columns;
    int get_amount_of_cells()
    {
        return amount_of_rows * amount_of_columns;
    }
    State(Cell **cells=nullptr, int curr_amount_of_rows=0, int curr_amount_of_columns=0);

    State* copy();
    ~State();
    void update_state();
    void supp_state(int needed_count_of_rows, int needed_count_of_columns);
};

#endif
