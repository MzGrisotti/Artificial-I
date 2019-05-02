#include <iostream>
#include <fstream>
#include "cube_unity.h"
#include <vector>

class Cube{

private:
    Cube_unity ***matrix;
    float obstacle_porcentage;
    std::tuple<int, int, int> pos_inicial;
    std::tuple<int, int, int> pos_final;
    int Size;
public:
    Cube(int Size, int obstacle_porcentage);
    ~Cube();
    void create_obstacles();
    void create_start_finish();
    void read_obstacles();
    void print_matrix();
    std::tuple<int, int, int> A_star_search();
    int least_cost(std::vector<Cube_unity> nodes);
    std::vector<Cube_unity> generate_next_nodes(std::tuple<int, int, int> atual_pos, std::tuple<int, int, int> final_pos);
    bool find_element(std::vector<Cube_unity> nodes, Cube_unity target);
    int print_path(std::tuple<int, int, int> result);
    void set_cost_father(std::tuple<int, int, int> filho, std::tuple<int, int, int> pai);
};
