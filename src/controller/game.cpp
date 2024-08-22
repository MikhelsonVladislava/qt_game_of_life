#include <QDebug>

#include "../../headers/controller/state.h"
#include "../../headers/controller/cell.h"
#include "../../headers/controller/game.h"


bool rules::need_to_change_state(State& state, Cell& cell)
{
    int count_of_alive = 0;
//    for (int i = (state.amount_of_columns + cell.x - 1) % state.amount_of_columns; i <= (state.amount_of_columns + cell.x + 1) % state.amount_of_columns; i++)
//        for (int j = (state.amount_of_rows + cell.y - 1) % state.amount_of_rows; j <= (state.amount_of_rows + cell.y + 1) % state.amount_of_rows; j++)
//            if (!(j == cell.y && i == cell.x) && state.cells_array[i][j].is_alive) count_of_alive++;

    for (int i = cell.x - 1; i <= cell.x + 1; i++)
        for (int j = cell.y - 1; j <= cell.y + 1; j++)
        {
            int current_x = (state.amount_of_columns + i) % state.amount_of_columns;
            int current_y = (state.amount_of_rows + j) % state.amount_of_rows;
            if (!(current_y == cell.y && current_x == cell.x) && state.cells_array[current_x][current_y].is_alive) count_of_alive++;
        }

    if ((cell.is_alive && (count_of_alive > 3 || count_of_alive < 2)) || (!cell.is_alive && count_of_alive == 3))
        return true;
    return false;
}
