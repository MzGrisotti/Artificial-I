#include <iostream>
#include <fstream>
#include "cube.h"


int main(){
   Cube cubo(3, 50);
   //cubo.create_obstacles();
   cubo.read_obstacles();
   cubo.print_matrix();
   return 1;
}
