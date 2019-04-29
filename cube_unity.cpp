#include <tuple>
#include <vector>
#include "cube_unity.h"
#include <cmath>

Cube_unity::Cube_unity(){
    mark = false;
    obstacle = false;
    cost = 0;
}

void Cube_unity::set_pos(int x, int y, int z){
   position = std::make_tuple(x, y, z);
}

std::tuple<int, int, int> Cube_unity::get_pos(){
   return position;
}

void Cube_unity::set_father(int x, int y, int z){
   father = std::make_tuple(x, y, z);
}

std::tuple<int, int, int> Cube_unity::get_father(){
   return father;
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

void Cube_unity::set_cost(int father_cost, std::tuple<int, int, int> final_pos){
   float dist;
   int atual_x, atual_y, atual_z;
   int final_x, final_y, final_z;

   atual_x = std::get<0>(position);
   atual_y = std::get<1>(position);
   atual_z = std::get<2>(position);

   final_x = std::get<0>(final_pos);
   final_y = std::get<1>(final_pos);
   final_z = std::get<2>(final_pos);

   dist = pow(atual_x, 2) + pow(atual_y, 2) + pow(atual_z, 2);
   dist = sqrt(dist);
   this->cost = cost + dist + 1;
}

int Cube_unity::get_cost(){
   return cost;
}
