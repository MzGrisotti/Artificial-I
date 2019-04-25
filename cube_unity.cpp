
#include "cube_unity.h"

Cube_unity::Cube_unity(){
    mark = false;
    obstacle = false;
}

void Cube_unity::set_mark(){
    mark = true;
}

void Cube_unity::set_block(){
    obstacle = true;
}

bool Cube_unity::is_marked(){
    return mark;
}
bool Cube_unity::is_blocked(){
    return obstacle;
}
