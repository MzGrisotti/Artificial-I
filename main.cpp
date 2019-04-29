#include <iostream>
#include <fstream>
#include "cube.h"
#include <time.h>
#include <queue>


int main(){
   //std::cout << "Digite o tamanho do Cubo e a porcentagem (0-100) de obstaculos" << std:endl;
   srand(time(NULL));
   int option;
   std::tuple<int, int, int> final_node;

   Cube cubo(20, 50);

   std::cout << "Digite 1 para criar obstaculos e 2 para ler do arquivo!" << std::endl;
   std::cin >> option;

   if(option == 1)
      cubo.create_obstacles();
   else if(option == 2)
      cubo.read_obstacles();

   cubo.create_start_finish();
   cubo.print_matrix();
   final_node = cubo.A_star_search();
   cubo.print_path(final_node);
   return 1;
}
