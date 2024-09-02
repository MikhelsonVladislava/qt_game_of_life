#include "../../headers/controller/state.h"
#include "../../headers/controller/cell.h"

Cell::Cell()
{
    x = -1;
    y = -1;
}

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Cell::set_coordinates(int x, int y)
{
    this->x = x;
    this->y = y;
}
