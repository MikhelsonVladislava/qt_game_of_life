#include "../../headers/controller/state.h"
#include "../../headers/controller/cell.h"

Cell::Cell()
{
    x = -1;
    y = -1;
}

Cell::Cell(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
}

void Cell::set_coordinates(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
}
