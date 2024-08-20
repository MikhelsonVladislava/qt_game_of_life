#include "../../headers/controller/state.h"
#include "../../headers/controller/cell.h"
#include "../../headers/controller/game.h"


bool rules::need_to_change_state(State& state, Cell& cell)
{
    int cell_x = cell.get_coordinates()->x;
    int cell_y = cell.get_coordinates()->y;

    int count_of_alive = 0;

    for (int i = (state.amount_of_columns + cell_x - 1) % state.amount_of_columns; i <= (state.amount_of_columns + cell_x + 1) % state.amount_of_columns; i++)
        for (int j = (state.amount_of_rows + cell_y - 1) % state.amount_of_rows; j <= (state.amount_of_rows + cell_y + 1) % state.amount_of_rows; j++)
            if (!(j == cell_y && i == cell_x) && state.get_cell(i, j)->is_alive) count_of_alive++;

    if ((cell.is_alive && (count_of_alive > 3 || count_of_alive < 2)) || (!cell.is_alive && count_of_alive == 3)) return true;
    return false;
}
