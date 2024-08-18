#ifndef GAME_H
#define GAME_H
#include "cell.h"
#include "field.h"

namespace rules {

bool need_to_change_state(State& state, Cell& cell);

}

#endif
