#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <queue>

std::vector<int> calcOutput(std::stack<int>t, int c) {
  std::queue<int> temp;
  std::stack<int> temp2;
  std::vector<int> output;
  int firstc = (t.size()) % c;

    for(int i = 0; i < firstc; i++){
      temp.push(t.top());
      t.pop();
    }
    for(int j = 0; j < firstc; j++){
      temp2.push(temp.front());
      temp.pop();
    }
    for (int k = 0; k < firstc; k++){
      output.push_back(temp2.top());
      temp2.pop();
    }

    while (!t.empty()){
      for(int i = 0; i < c; i++){
        temp.push(t.top());
        // std::cout << "first itr: " << t.top() << std::endl;
        t.pop();
      }
      for(int j = 0; j < c; j++){
        temp2.push(temp.front());
        // std::cout << "second itr: " << temp.front() << std::endl;
        temp.pop();
      }
      for (int k = 0; k < c; k++){
        output.push_back(temp2.top());
        // std::cout << "third itr: " << temp2.top() << std::endl;
        temp2.pop();
      }
    }

    // for(int b = 0; b < output.size(); b++){
    //   std::cout << "final itr: " << output[b] << std::endl;
    // }

    return output;
}

int main (int argc, char *argv[]){

  std::stack<int> truck;
  // std::vector<int> output;

  std::ifstream b;
  std::ifstream c;
  int container = 0;
  int temp = 0;

  if(argc != 3){
      std::cerr << "Usage: ./luggage_handling <input_file> <container_size>" << std::endl;
      return 1;
   }

   b.open(argv[1]);
   if(b.fail()){std::cerr << "Error: cannot open file wrong_file" << std::endl; return 0;}
   while(b >> temp){
     truck.push(temp);
   }
   b.close();

  sscanf(argv[2], "%d", &container);
  if(container < 0){std::cerr << "Error: invalid container size" << std::endl; return 0;}

  std::vector<int>output = calcOutput(truck,container);

  for (int i = 0; i < output.size(); i++) {
    std::cout << output.at(i) << " ";
  }
  std::cout << std::endl;

  return 0;
}
