#include <iostream>
#include <fstream>

class Cube_unity{
private:
    bool mark;
    bool obstacle;
public:
    Cube_unity();
    void mark_unity();
    void set_mark();
    void set_block();
    bool is_marked();
    bool is_blocked();
};
