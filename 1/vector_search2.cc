/*Faustine Yiu
Student ID: 913062973
ECS 36C Homework 1 Program Info: This program matches generated vectors to
magnitudes via the equation: sqrt(v1*v1 + v2*v2) = ~m; when v is vector and
m is magnitude.
Tutor: Taz Atwell, CS Tutor, 10/10.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <math.h>
#include <cmath>
#include <algorithm>

class Position {
  private:
    int x;
    int y;
    int magnitude;
  public:
    Position(int x_val, int y_val){
      x = x_val;
      y = y_val;
      magnitude = sqrt(x * x + y * y );
    };

    const int getMagnitude(){
      return magnitude;
    };

    bool operator< (Position& mag){
      return(magnitude < mag.getMagnitude());
    }
};


int linearSearch(std::vector<Position> v, std::vector<int> m){
  int num = 0;
  int match = 0;

  for (unsigned i = 0; i < m.size(); i++){
    num = m[i];
		for (unsigned j = 0; j < v.size(); j++){
      if (v[j].getMagnitude() == num){
        match ++;
        break;
      }
    }
	}
  return match;
}

int binarySearch(std::vector<Position> &v, int m){
  int low = 0;
  int high = v.size()-1;

  while(low <= high){
    int mid = low+(high-low)/2;
    if(v[mid].getMagnitude() < m){
      low = mid + 1;
    }else if(v[mid].getMagnitude() > m){
      high = mid - 1;
    }else if(v[mid].getMagnitude() == m){
      return 1;
    }
  }
  return 0;
}

int multipleBinarySearch (std::vector<Position>v, std::vector<int>m){
  int num = 0;
  int match = 0;

  for (unsigned i = 0; i < m.size(); i++){
    num = m[i];
    match += binarySearch(v, num);
	}
  return match;
}

int userChoice(std::vector<Position> v, std::vector<int> m) {
  std::string choice;

  std::cin >> choice;
     if (choice == "l"){
      return linearSearch(v, m);
    }else if (choice == "b"){
      std::sort(m.begin(), m.end());
      return multipleBinarySearch(v, m);
    }else{
      std::cerr << "Incorrect choice" << std::endl;
      std::cin >> choice;
      if (choice == "l"){
        return linearSearch(v, m);
      }else if (choice == "b"){
        std::sort(m.begin(), m.end());
        return multipleBinarySearch(v, m);
      }else{
        std::cerr << "Incorrect choice" << std::endl;
      }
    }
    return 0;
}

int main (int argc, char *argv[]){

  std::vector<Position>vec;
  std::vector<int>mag;
  std::ifstream v;
  std::ifstream m;
  std::ofstream outputFile;
  int temp= 0;
  int x_val = 0;
  int y_val = 0;
  int match = 0;

  if(argc != 4) {
      std::cerr << "Usage: ./vector_search <vector_file.dat> <magnitude_file.dat> <result_file.dat>" << std::endl;
      return -1;
   }

   v.open(argv[1]);
   if(v.fail()){std::cerr << "Error: cannot open file wrong_vect_file.dat" << std::endl; return 0;}
   while(v >> x_val >> y_val){
    vec.push_back(Position(x_val,y_val));
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
  start = std::chrono::high_resolution_clock::now();
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
