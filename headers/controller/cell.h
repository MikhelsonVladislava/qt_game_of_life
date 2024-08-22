#ifndef CELL_H
#define CELL_H
#include <string>

class Cell
{
public:
    int x;
    int y;
    bool is_alive = false;
    Cell();
    Cell(int new_x, int new_y);

    void set_coordinates(int x, int y);
};
#endif
