#include "../../headers/controller/field.h"
#include "../../headers/controller/cell.h"
#include "../../headers/controller/game.h"
#include <QDebug>
#include <QString>
#include <map>

void State::update_state()
{
    Cell* last_cells = new Cell[amount_of_cells];
    std::copy(cells_array, cells_array + amount_of_cells, last_cells);

    State last_state = State(last_cells, amount_of_cells, amount_of_rows, amount_of_columns);

    for (int i = 0; i < amount_of_columns; i++)
        for (int j = 0; j < amount_of_rows; j++)
        {
            Cell* next_cell_last_state = last_state.get_cell(i, j);
            Cell* next_cell_next_state = get_cell(i, j);
            if (next_cell_last_state->is_alive && rules::need_to_change_state(last_state, *next_cell_last_state))
                next_cell_next_state->is_alive = false;
            else if (!next_cell_last_state->is_alive && rules::need_to_change_state(last_state, *next_cell_last_state))
                next_cell_next_state->is_alive = true;
        }

    delete[] last_cells;
}

Cell* State::get_cell(int x, int y)
{
    std::string coords = std::to_string(x) + "," + std::to_string(y);
    Cell* curr_cell = cells_map[coords];
    return curr_cell;
}

State::State(Cell *cells, int curr_amount_of_cells, int curr_amount_of_rows, int curr_amount_of_columns)
{
    if (curr_amount_of_rows * curr_amount_of_columns != curr_amount_of_cells)
        throw InvalidState();
    cells_array = cells;
    int count_cells = 0;
    amount_of_cells = curr_amount_of_cells;
    amount_of_rows = curr_amount_of_rows;
    amount_of_columns = curr_amount_of_columns;

    if (cells[0].get_coordinates()->x == -1)
        for (int i = 0; i < amount_of_columns; i++)
            for (int j = 0; j < amount_of_rows; j++)
            {
                cells[count_cells].set_coordinates(i, j);
                count_cells++;
            }

    for (int j = 0; j < amount_of_cells; j++)
    {
        Cell* curr_cell = &cells[j];
        //if (curr_cell->get_coordinates() == nullptr)
        //    throw NullCoordinates();
        std::string curr_coord = curr_cell->get_coordinates()->get_string_coords();
        //if (cells_map.find(curr_coord) != cells_map.end())
        //    throw CoordsDublicate();
        cells_map[curr_coord] = curr_cell;
    }
}
