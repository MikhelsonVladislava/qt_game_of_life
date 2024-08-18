#include "../../headers/controller/field.h"
#include "../../headers/controller/cell.h"

CellCoordinates::CellCoordinates(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
}

std::string CellCoordinates::get_string_coords()
{
    return std::to_string(x) + "," + std::to_string(y);
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
