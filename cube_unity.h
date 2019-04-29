#include <iostream>
#include <fstream>
#include <tuple>

class Cube_unity{
private:
    bool mark;
    bool obstacle;
    std::tuple<int, int, int> position;
    std::tuple<int, int, int> father;
    int cost;
public:
    Cube_unity();
    void set_pos(int x, int y, int z);
    void set_father(int x, int y, int z);
    std::tuple<int, int, int> get_pos();
    std::tuple<int, int, int> get_father();
    void mark_unity();
    void set_mark();
    void set_block();
    bool is_marked();
    bool is_blocked();
    void set_cost(int father_cost, std::tuple<int, int, int> final_pos);
    int get_cost();
};
