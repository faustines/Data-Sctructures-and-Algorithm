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
double calcPostfix(std::string expression);
bool notNumberAndOperator(char C);
bool isOperator(char C);
double calcOperator(char operation, double operand1, double operand2);

int main(){
  input();
  return 0;
}

void input(){
	std::string expression;
	getline(std::cin,expression);

  if (std::cin.eof()){
    //checks for Control-D /
    std::cout << "Bye!" << std::endl;
    exit(0);
  }

  for(unsigned i = 0; i <expression.size(); i++){
    if(expression[i] == ' '){
      continue;
    }
    if (isOperator(expression[i]) && isOperator(expression[i+1])){
      std::cerr << "Error: unknown symbol '" << expression[i] << expression[i+1] << "'" << std::endl;
      input();
    }
    if(notNumberAndOperator(expression[i])){
      std::cerr << "Error: unknown symbol '" << expression[i] << "'" << std::endl;
      input();
    }
  }
	  std::cout << calcPostfix(expression) << std::endl;
	  input();
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

bool notNumberAndOperator(char C){
  if(isdigit(C) || C == '+' || C == '-' || C == '*' || C == '/' || C == '.'){
    return false;
  }else{
    return true;
  }
}

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
