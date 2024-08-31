#include "../../headers/controller/state.h"
#include "../../headers/controller/cell.h"
#include <QDebug>
#include "../../headers/controller/game.h"

void State::update_state()
{
    State* last_state = copy(this);

    for (int i = 0; i < amount_of_columns; i++)
        for (int j = 0; j < amount_of_rows; j++)
        {
            Cell next_cell_last_state = last_state->cells_array[i][j];
            Cell* next_cell_next_state = &cells_array[i][j];
            if (rules::need_to_change_state(*last_state, next_cell_last_state))
                next_cell_next_state->is_alive = !next_cell_last_state.is_alive;
        }
    delete last_state;
}

void State::supp_state(int needed_count_of_rows, int needed_count_of_columns)
{
    Cell** last_cells = new Cell*[amount_of_columns];
    for (int i = 0; i < amount_of_columns; i++)
    {
        last_cells[i] = new Cell[amount_of_rows];
        std::copy(cells_array[i], cells_array[i] + amount_of_rows, last_cells[i]);
    }

    cells_array = new Cell*[needed_count_of_columns];
    int rows_diff = needed_count_of_rows - amount_of_rows;
    int columns_diff = needed_count_of_columns - amount_of_columns;
    for (int i = 0; i < needed_count_of_columns; i++)
    {
        cells_array[i] = new Cell[needed_count_of_rows];
        for (int j = 0; j < needed_count_of_rows; j++)
        {
            cells_array[i][j] = Cell(i, j);
            if (i < columns_diff / 2 + amount_of_columns && i >= columns_diff / 2 && j < rows_diff /2 + amount_of_rows && j >= rows_diff /2)
            {
                cells_array[i][j].is_alive = last_cells[i - columns_diff / 2][j - rows_diff / 2].is_alive;
            }
        }
    }

    for (int i = 0; i < amount_of_columns; i++)
    {
        delete[] last_cells[i];
    }
    delete[] last_cells;

    amount_of_rows = needed_count_of_rows;
    amount_of_columns = needed_count_of_columns;
}

State::State(Cell **cells, int curr_amount_of_rows, int curr_amount_of_columns)
{
    cells_array = cells;
    amount_of_rows = curr_amount_of_rows;
    amount_of_columns = curr_amount_of_columns;
}

State* State::copy(State *copied_state)
{
    Cell** last_cells = new Cell*[amount_of_columns];
    for (int i = 0; i < amount_of_columns; i++)
    {
        last_cells[i] = new Cell[amount_of_rows];
        std::copy(cells_array[i], cells_array[i] + amount_of_rows, last_cells[i]);
    }
    State* last_state = new State(last_cells, copied_state->amount_of_rows, copied_state->amount_of_columns);
    return last_state;
}

State::~State()
{
    for (int i = 0; i < amount_of_columns; i++)
    {
        delete[] cells_array[i];
    }
    delete[] cells_array;
}
