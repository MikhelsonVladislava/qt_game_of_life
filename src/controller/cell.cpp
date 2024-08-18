#include "../../headers/controller/field.h"
#include "../../headers/controller/cell.h"

CellCoordinates::CellCoordinates(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
}

std::pair<int, int> CellCoordinates::get_coords()
{
    return std::pair(x, y);
}

Cell::Cell()
{
    coordinates = new CellCoordinates(-1, -1);
}

void Cell::set_coordinates(int x, int y)
{
    coordinates->x = x;
    coordinates->y = y;
}

CellCoordinates* Cell::get_coordinates()
{
    return coordinates;
}
