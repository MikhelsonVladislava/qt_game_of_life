#include "../../headers/controller/field.h"
#include "../../headers/controller/cell.h"
#include "../../headers/controller/game.h"
#include <QDebug>
#include <cmath>
#include <QString>
#include <map>

Field::Field(State* new_state)
{
    state = new_state;
}

Field::~Field()
{
    for (int i = 0; i < state->amount_of_rows; i++)
        for (int j = 0; j < state->amount_of_columns; j++)
            delete state->get_cell(i, j);
}

void Field::update_state()
{
    Cell* last_cells = new Cell[state->amount_of_cells];
    for (int i = 0; i < state->amount_of_cells; i++)
        last_cells[i] = state->cells_array[i];

    State last_state = State(last_cells, state->amount_of_cells, state->amount_of_rows, state->amount_of_columns);

    for (int i = 0; i < state->amount_of_columns; i++)
        for (int j = 0; j < state->amount_of_rows; j++)
        {
            Cell* next_cell_last_state = last_state.get_cell(i, j);
            Cell* next_cell_next_state = state->get_cell(i, j);
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
