#include <iostream>
#include <fstream>
#include "cube.h"
#include <sys/time.h>
#include <queue>

void export_data(double time, int distance){

   std::ofstream file;
   std::ofstream create_file;
   char file_name[20];
   sprintf(file_name, "Distance %d.txt", distance);
   file.open(file_name, std::ios::app);
   if(file.is_open()){
      file << time << std::endl;
      std::cout << "Saida exportada para arquivo" << std::endl;
   }
   file.close();
}

int main(){
   //std::cout << "Digite o tamanho do Cubo e a porcentagem (0-100) de obstaculos" << std:endl;
   srand(time(NULL));
   int option, distance;
   float percentage;
   std::tuple<int, int, int> final_node;
   timeval start, end;
   //

   std::cout << "Digite 1 para criar obstaculos, 2 para ler do arquivo ou 3 para executar varias vezes!" << std::endl;
   std::cin >> option;
   std::cout << "Generating Matrix" << std::endl;

   if(option == 1){
      Cube cubo(30, 40);
      cubo.create_obstacles();
   }
   else if(option == 2){
      Cube cubo(30, 40);
      cubo.read_obstacles();
   }
   else if(option == 3){
      for(float i = 0; i < 1000; i++){

         gettimeofday(&start, NULL);
         Cube cubo(30, 40);
         cubo.read_obstacles();
         std::cout << "Generating Start-Finish Points" << std::endl;
         cubo.create_start_finish();
         //cubo.print_matrix();
         std::cout << "Generating Path" << std::endl;
         percentage = (i/1000)*100;
         std::cout << "Run Percentagem: " << percentage << "% - " << i << "/1000" << std::endl;
         final_node = cubo.A_star_search();
         gettimeofday(&end, NULL);
         double runtime = end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;
         distance = cubo.print_path(final_node);
         std::cout << "Time: " << runtime << " secs"<< std::endl;
         export_data(runtime, distance);
         system("cls");

      }
   }
   std::cout << "Job Done" << std::endl;
   system("pause");
   return 1;
}
