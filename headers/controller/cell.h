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
    Cell(int x, int y);

    void set_coordinates(int x, int y);
};
#endif
