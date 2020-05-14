/*Faustine Yiu
Student ID: 913062973
ECS 36C Homework 1 Program Info: This program matches generated vectors to
magnitudes via the equation: sqrt(v1*v1 + v2*v2) = ~m; when v is vector and
m is magnitude.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <math.h>

int linearSearch(std::vector<int> v, std::vector<int> m){
  int match = 0;

  for (int i = 0; i < v.size(); i++){
                for (int j = 0; j < m.size(); j++){
      if (v[i] == m[j]){
        match ++;
      }
    }
        }
  return match;
}

int binarySearch(std::vector<int> v, std::vector<int> m){
  int match = 0;

  for (int j = 0; j < v.size(); j++){
    if(v[j] > v[j+1]){
      iter_swap(v.begin() + v[j], v.begin() + v[j+1]);
    }
  }
  for (int l = 0; l < v.size(); l++){
    for (int s = 0; s < m.size(); s++){
      if(v[l] == m[s]){
        match++;
      }
    }
  }
  return match;
}

int userChoice(std::vector<int> v, std::vector<int> m) {
  std::string choice;

  std::cin >> choice;
     if (choice == "l"){
      return linearSearch(v, m);
    }else if (choice == "b"){
      return binarySearch(v, m);
    }else{
      std::cerr << "Incorrect choice" << std::endl;
      std::cin >> choice;
      if (choice == "l"){
        return linearSearch(v, m);
      }else if (choice == "b"){
        return binarySearch(v, m);
      }else{
        std::cerr << "Incorrect choice" << std::endl;
      }
    }
    return 0;
}
int main (int argc, char *argv[]){

  std::vector<int>vec;
  std::vector<int>mag;
  std::ifstream v;
  std::ifstream m;
  std::ofstream outputFile;
  int temp = 0;
  int match = 0;

  if(argc != 4) {
      std::cerr << "Usage: ./vector_search <vector_file.dat> <magnitude_file.dat> <result_file.dat>" << std::endl;
      return -1;
   }

   v.open(argv[1]);
   if(v.fail()){std::cerr << "Error: cannot open file wrong_vect_file.dat" << std::endl; return 0;}
   while(v >> temp){
    vec.push_back(temp);
  }
  v.close();

  m.open(argv[2]);
  if(m.fail()){std::cerr << "Error: cannot open file wrong_mag_file.dat" << std::endl; return 0;}
  while(m >> temp){
    mag.push_back(temp);
  }
  m.close();

  std::cout << "Choice of search method ([l]inear, [b]inary)?" << std::endl;
  std::chrono::high_resolution_clock::time_point start;
  match = userChoice(vec, mag);
  auto end = std::chrono::high_resolution_clock::now();
  double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();

  outputFile.open(argv[3]);
  if(outputFile.fail()){std::cerr << "Error: cannot open file /etc/passwd" << std::endl; return 0;}
  outputFile << match << std::endl;
  outputFile.close();

  std::cout << "CPU time: " << elapsed_us << " microseconds" << std::endl;

  return 0;

}
