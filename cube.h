#include <iostream>
#include <fstream>
#include "cube_unity.h"

class Cube{

private:
    Cube_unity ***matrix;
    float obstacle_porcentage;
    int Size;
public:
    Cube(int Size, int obstacle_porcentage);
    void create_obstacles();
    void read_obstacles();

};
