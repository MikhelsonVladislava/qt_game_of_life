#ifndef CELL_H
#define CELL_H
#include <string>

class CellCoordinates
{
public:
    int x;
    int y;

    CellCoordinates(int new_x, int new_y);
    std::string get_string_coords();
};

class Cell
{
private:
    CellCoordinates* coordinates;

public:
    bool is_alive = false;
    Cell();

    void set_coordinates(int x, int y);
    CellCoordinates* get_coordinates();
};
#endif
