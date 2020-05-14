/*Faustine Yiu
Student ID: 913062973
ECS 36C Homework 2 Program Info: This program calculates numbers using
+, -, *, / operators by inputing a postfix expression.
Tutor: Sean Young 10/16.
*/

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cstdlib>

void input();
//bool isInvalidExpression(std::string expression);
double calcPostfix(std::string expression);
//bool notNumberAndOperator(char C);
bool isOperator(char C);
//bool isNumber(char C);
double calcOperator(char operation, double operand1, double operand2);

int main(){
  input();
  return 0;
}

void input(){
	std::string expression;
  std::string b = "Bye!";
	getline(std::cin,expression);
  if(expression == b){
    exit(0);
  }else{
	  std::cout << calcPostfix(expression) << std::endl;
	  input();
   }
	return;
}

double calcPostfix(std::string expression){
	std::stack<double> s;
  std::string token;
  std::stringstream ss(expression);
  double d;
  char c;
  double x, y;
  double result;
  double temp;

  while (ss >> token) {
    std::stringstream ss1(token);
    std::stringstream ss2(token);

    if (ss1 >> d){
      s.push(d);
    }else if(ss2 >> c){
      if(isOperator(c)){
        if(!s.empty()){
          y = s.top();
          s.pop();
        }
        if(!s.empty()){
          x = s.top();
          s.pop();
        }
        result = calcOperator(c,x,y);
        s.push(result);
      }
    }
  }

  if(s.empty()){
    std::cerr << "Error: invalid expression" << std::endl;
    input();
  }
  //if stack has more than 1
  temp = s.top();
  s.pop();
  if(!s.empty()){
    std::cerr << "Error: invalid expression" << std::endl;
    input();
  }
  return temp;
}


// bool isInvalidExpression(std::string e){
//   int num = 0;
//   int op = 0;
//
//   for(unsigned i = 0; i < e.length(); i++) {
//     if(e[i] == ' '){
//       continue;
//     }else if(notNumberAndOperator(e[i])){
//       input();
//     }else if(isNumber(e[i])){
//       num++;
//     }else if(isOperator(e[i])){
//       op++;
//     }
//   }
//   if (num != 2) {
//     return true;
//   }else if (op != 1) {
//     return true;
//   }else{
//     return false;
//   }
// }

bool notNumberAndOperator(char C){
  if((C >= 0 && C <= 9)|| C == '+' || C == '-' || C == '*' || C == '/' || C == '.'){
    return false;
  }else{
    std::cerr << "Error: unknown symbol '" << C << "'" << std::endl;
    return true;
  }
}

// bool isNumber(char C){
//   int ia = a - '0';
//
// 	if((C >= '0' && C <= '9') || C == '.'){
//     return true;
//   }else{
// 	  return false;
//   }
// }

bool isOperator(char C){
	if(C == '+' || C == '-' || C == '*' || C == '/'){
		return true;
  }else{
	  return false;
  }
}

double calcOperator(char operation, double operand1, double operand2){
	if(operation == '+'){
     return operand1 + operand2;
   }else if(operation == '-'){
     return operand1 - operand2;
   }else if(operation == '*'){
     return operand1 * operand2;
   }else if(operation == '/'){
     return operand1 / operand2;
   }
  return 0;
}
