#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::string data = "10 25 70";
  std::string dataNum = "";

  for (unsigned i = 0; i < data.size(); i++){
      dataNum += data[i];
    if(data[i] == ' '){
      break;
    }
  }
  std::cout << dataNum << std::endl;

}
