#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "cube.h"
#include <vector>
#include <tuple>
#include <algorithm>

Cube::Cube(int Size, int obstacle_porcentage){
    this->Size = Size;
    this->obstacle_porcentage = obstacle_porcentage;
    this->matrix = new Cube_unity**[Size];
    for(auto i = 0; i < Size; i++){
        matrix[i] = new Cube_unity*[Size];
        for(auto j = 0; j < Size; j++){
            matrix[i][j] = new Cube_unity[Size];
            for(auto k = 0; k < Size; k++)
               matrix[i][j][k].set_pos(i, j, k);

        }
    }
}

void Cube::create_obstacles(){
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
                    file << "1";
                else
                    file << "0";
            }
            file << std::endl;
        }
    }
    file.close();

}

void Cube::create_start_finish(){

   int start_x, start_y, start_z;
   int finish_x, finish_y, finish_z;
   do{
      start_x = rand()%this->Size;
      start_y = rand()%this->Size;
      start_z = rand()%this->Size;
      finish_x = rand()%this->Size;
      finish_y = rand()%this->Size;
      finish_z = rand()%this->Size;
   }while(matrix[start_x][start_y][start_z].is_blocked() ||
          matrix[finish_x][finish_y][finish_z].is_blocked() ||
          (start_x == finish_x && start_y == finish_y && start_z == finish_z));
   pos_inicial = std::make_tuple(start_x, start_y, start_z);
   pos_final = std::make_tuple(finish_x, finish_y, finish_z);
   std::cout << "Inicio: [" << start_x << "][" << start_y << "][" << start_z << "]" << std::endl;
   std::cout << "Fim: [" << finish_x << "][" << finish_y << "][" << finish_z << "]" << std::endl << std::endl;
}

void Cube::read_obstacles(){

    std::ifstream file;
    int x, y, z;
    x = y = z = 0;
    char c;
    file.open("obstacles.txt");
    while(file.get(c)){
        if(c != '\n'){
            //std::cout << "X: " << x << " Y: " << y << " Z: " << z << std::endl;
            if(c == '1')
                matrix[x][y][z].set_block();
            if(z < Size - 1)
                z++;
            else{
                if(y < Size - 1){
                    z = 0;
                    y++;
                }
                else{
                    if(x < Size - 1){
                        y = 0;
                        z = 0;
                        x++;
                    }
                }
            }
        }
    }
}

void Cube::print_matrix(){
   std::cout << "Cubo " << Size << " x " << Size << std::endl;
    for(auto i = 0; i < Size; i++){
         std::cout <<  "x = " << i<<std::endl;
        for(auto j = 0; j < Size; j++){
            for(auto k = 0; k < Size; k++){
                if(matrix[i][j][k].is_blocked())
                    std::cout << "1 ";
                else
                    std::cout << "0 ";
            }
            std::cout <<"y = "<< j << std::endl;
        }
        std::cout << std::endl;
    }
}

int Cube::least_cost(std::vector<Cube_unity> nodes){
   int menor_custo, node;
   menor_custo = nodes[0].get_cost();
   node = 0;
   for(int i = 0; i < nodes.size(); i++){
      if(nodes[i].get_cost() < menor_custo){
         menor_custo = nodes[i].get_cost();
         node = i;
      }
   }
   return node;
}

std::vector<Cube_unity> Cube::generate_next_nodes(std::tuple<int, int, int> atual_pos, std::tuple<int, int, int> final_pos){
   std::vector<Cube_unity> filhos;
   int atual_x, atual_y, atual_z;

   atual_x = std::get<0>(atual_pos);
   atual_y = std::get<1>(atual_pos);
   atual_z = std::get<2>(atual_pos);

   if(atual_x + 1 < Size){
      filhos.push_back(matrix[atual_x+1][atual_y][atual_z]);
      matrix[atual_x+1][atual_y][atual_z].set_father(atual_x, atual_y, atual_z);
      matrix[atual_x+1][atual_y][atual_z].set_cost(matrix[atual_x+1][atual_y][atual_z].get_cost(), final_pos);
   }
   if(atual_x - 1 >= 0){
      filhos.push_back(matrix[atual_x-1][atual_y][atual_z]);
      matrix[atual_x-1][atual_y][atual_z].set_father(atual_x, atual_y, atual_z);
      matrix[atual_x-1][atual_y][atual_z].set_cost(matrix[atual_x-1][atual_y][atual_z].get_cost(), final_pos);
   }
   if(atual_y + 1 < Size){
      filhos.push_back(matrix[atual_x][atual_y+1][atual_z]);
      matrix[atual_x][atual_y+1][atual_z].set_father(atual_x, atual_y, atual_z);
      matrix[atual_x][atual_y+1][atual_z].set_cost(matrix[atual_x][atual_y+1][atual_z].get_cost(), final_pos);
   }
   if(atual_y - 1 >= 0){
      filhos.push_back(matrix[atual_x][atual_y-1][atual_z]);
      matrix[atual_x][atual_y-1][atual_z].set_father(atual_x, atual_y, atual_z);
      matrix[atual_x][atual_y-1][atual_z].set_cost(matrix[atual_x][atual_y-1][atual_z].get_cost(), final_pos);
   }
   if(atual_z + 1 < Size){
      filhos.push_back(matrix[atual_x][atual_y][atual_z+1]);
      matrix[atual_x][atual_y][atual_z+1].set_father(atual_x, atual_y, atual_z);
      matrix[atual_x][atual_y][atual_z+1].set_cost(matrix[atual_x][atual_y][atual_z+1].get_cost(), final_pos);
   }
   if(atual_z - 1 >= 0){
      filhos.push_back(matrix[atual_x][atual_y][atual_z-1]);
      matrix[atual_x][atual_y][atual_z-1].set_father(atual_x, atual_y, atual_z);
      matrix[atual_x][atual_y][atual_z-1].set_cost(matrix[atual_x][atual_y][atual_z-1].get_cost(), final_pos);
   }

   return filhos;
}

bool Cube::find_element(std::vector<Cube_unity> nodes, Cube_unity target){
   bool result = false;
   for(auto i = 0; i < nodes.size(); i++){
      if(nodes[i].get_pos() == target.get_pos())
         result = true;
   }
   return result;
}

std::tuple<int, int, int> Cube::A_star_search(){
   std::vector<Cube_unity> next_nodes;
   std::vector<Cube_unity> marked_nodes;
   std::vector<Cube_unity> children_nodes;
   std::tuple<int, int, int> atual_pos;
   std::tuple<int, int, int> teste;
   Cube_unity atual_node;

   int start_x, start_y, start_z;
   int finish_x, finish_y, finish_z;
   int atual_x, atual_y, atual_z;
   int node_least_cost;

   start_x = std::get<0>(pos_inicial);
   start_y = std::get<1>(pos_inicial);
   start_z = std::get<2>(pos_inicial);

   finish_x = std::get<0>(pos_final);
   finish_y = std::get<1>(pos_final);
   finish_z = std::get<2>(pos_final);

   next_nodes.push_back(matrix[start_x][start_y][start_z]);


   while(!next_nodes.empty()){
      node_least_cost = least_cost(next_nodes);

      atual_node = next_nodes[node_least_cost];
      atual_pos = atual_node.get_pos();
      atual_x = std::get<0>(atual_pos);
      atual_y = std::get<1>(atual_pos);
      atual_z = std::get<2>(atual_pos);

      next_nodes.erase(next_nodes.begin() + node_least_cost);
      marked_nodes.push_back(atual_node);

      children_nodes = generate_next_nodes(atual_pos, pos_final);

      for(auto i = 0; i < children_nodes.size(); i++){
         teste = children_nodes[i].get_pos();
         if(children_nodes[i].get_pos() == pos_final){
            std::cout << "Bingo" <<std::endl;
            std::cout << "X = " << std::get<0>(teste) << " Y = " << std::get<1>(teste) << " Z = " << std::get<2>(teste) << std::endl;
            std::cout << "Custo: " << children_nodes[i].get_cost() << std::endl;
            return teste;
         }

         if(!children_nodes[i].is_marked() && !children_nodes[i].is_blocked() && !find_element(next_nodes, children_nodes[i])){
            next_nodes.push_back(children_nodes[i]);
         }
      }

      matrix[atual_x][atual_y][atual_z].set_mark();
      //atual_node.set_mark();

      //std::cout << "Atual : [" << atual_x << "][" << atual_y << "][" << atual_z << "]" << "custo: " << matrix[atual_x][atual_y][atual_z].get_cost() <<std::endl;


   }
   std::cout << "Caminho nao encontrado" << std::endl;
   return pos_inicial;
}

void Cube::print_path(std::tuple<int, int, int> result){
   std::tuple<int, int, int> atual_pos = result;
   std::tuple<int, int, int> aux;
   int atual_x, atual_y, atual_z;
   int i =0;
   while(atual_pos != pos_inicial && i < 20){
      atual_x = std::get<0>(atual_pos);
      atual_y = std::get<1>(atual_pos);
      atual_z = std::get<2>(atual_pos);
      std::cout << "Atual : [" << atual_x << "][" << atual_y << "][" << atual_z << "]" <<std::endl;
      atual_pos = matrix[atual_x][atual_y][atual_z].get_father();
      i++;
   }
   std::cout << "Atual : [" << std::get<0>(pos_inicial) << "][" << std::get<1>(pos_inicial) << "][" << std::get<2>(pos_inicial) << "]" <<std::endl;

}
