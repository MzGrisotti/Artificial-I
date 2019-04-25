#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "cube.h"

Cube::Cube(int Size, int obstacle_porcentage){
    this->Size = Size;
    this->obstacle_porcentage = obstacle_porcentage;
    this->matrix = new Cube_unity**[Size];
    for(auto i = 0; i < Size; i++){
        matrix[i] = new Cube_unity*[Size];
        for(auto j = 0; j < Size; j++)
            matrix[i][j] = new Cube_unity[Size];
    }
}

void Cube::create_obstacles(){
    srand(time(NULL));
    int max_obs = pow(Size, 3)* (obstacle_porcentage/100);
    std::cout << "obs: "<< max_obs << std::endl;
    int current_obs = 0;
    int x, y, z;
    while(current_obs < max_obs){
        x = rand()%Size;
        y = rand()%Size;
        z = rand()%Size;
        //std::cout << "x, y, e z: " << x << y << z <<std::endl;
        if(!(matrix[x][y][z].is_blocked())){
            matrix[x][y][z].set_block();
            current_obs++;
        }
    }
    std::ofstream file;
    file.open("obstacles.txt");
    for(auto i = 0; i < Size; i++){
        for(auto j = 0; j < Size; j++){
            for(auto k = 0; k < Size; k++){
                if(matrix[i][j][k].is_blocked())
                    file << "1 ";
                else
                    file << "0 ";
            }
            file << std::endl;
        }
        file << std::endl;
    }
    file.close();

}

void Cube::read_obstacles(){

    std::ifstream file;
    int x, y, z;
    x = y = z = 0;
    char c;
    file.open("obstacles.txt");
    while(file.get(c)){
        if(c != '\n'){
            if(c == '1')
                matrix[x][y][z].set_block();
            if(z < Size)
                z++;
            else{
                if(y < Size)
                    y++;
                else{
                    if(x < Size)
                        x++;
                }
            }
        std::cout << "X: " << x << "Y: " << y << "Z: " << z << std::endl;
        }
    }
}

void Cube::print_matrix(){
    for(auto i = 0; i < Size; i++){
        for(auto j = 0; j < Size; j++){
            for(auto k = 0; k < Size; k++){
                if(matrix[i][j][k].is_blocked())
                    std::cout << "1 ";
                else
                    std::cout << "0 ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
