#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "binary_tree.h"
using Node = BinaryTree<int>::Node;

void EncodeSuccinctBinaryTree(std::unique_ptr<Node> &n, std::string& structure, std::string& data) {
    int num = 0;
    std::string dataNum = "";

    for (unsigned i = 0; i < data.size(); i++){
        dataNum += data[i];
      if(data[i] == ' '){
        break;
      }
    }
    std::stringstream geek(dataNum);
    int x = 0;
    geek >> x;

    if (structure[0] == '0'){
        structure.erase(0,2);

    }else{
        n = std::unique_ptr<Node>(new Node{x});
        structure.erase(0,2);
        for (unsigned j = 0; j < data.size(); j++){
          if (data[j] == ' '){
            num = j+1;
            break;
          }
        }
        data.erase(0,num);

        EncodeSuccinctBinaryTree(n->left, structure, data);
        EncodeSuccinctBinaryTree(n->right, structure, data);
    }
}

int main (int argc, char *argv[]){

  std::string structure;
  std::string data;
  std::ifstream i;
  std::string str;

  int one = 0;
  int whitespace = 0;

  BinaryTree<int> bt;

  if(argc != 2) {
      std::cerr << "Usage: ./bt_succinct_dec <input_file>" << std::endl;return 1;
   }

  i.open(argv[1]);
  if(i.fail()){std::cerr << "Error: cannot read structure line" << std::endl; return 1;}

  while (std::getline(i, str)) {
    structure = str;
    break;
  }
  while (std::getline(i, str)) {
    data = str;
    break;
  }
  i.close();

  for (unsigned k = 0; k < data.size(); k++){
    if (data[k] == ' '){
      continue;
    }else if (!(isdigit(data[k]))){
      std::cerr << "Error: data line is invalid" << std::endl; return 1;
    }
  }
  if(structure.length() == 0){std::cerr << "Error: cannot read structure line" << std::endl; return 1;}
  if (data.length() == 0){std::cerr << "Error: cannot read data line" << std::endl; return 1;}

  for (unsigned i = 0; i < structure.size(); i++) {
    if (structure[i] == '1') {
      one++;
    }else if(structure[i] == ' '){
      continue;
    }else if(structure[i] == '0'){
      continue;
    }else{
      std::cerr << "Error: structure line is invalid" << std::endl;
      return 1;
    }
  }

  for (unsigned j = 0; j < data.size(); j++){
    if (data[j] == ' '){
      whitespace++;
    }
  }

  if (one != whitespace+1) {std::cerr << "Error: data line is invalid" << std::endl; return 1;}
  data += " ";

  EncodeSuccinctBinaryTree(bt.root,structure,data);

  bt.PreorderPrint();
  bt.InorderPrint();

  return 0;

}
