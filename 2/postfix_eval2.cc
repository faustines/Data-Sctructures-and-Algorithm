/*Faustine Yiu
Student ID: 913062973
ECS 36C Homework 2 Program Info: This program calculates numbers using
+, -, *, / operators by inputing a postfix expression.
*/

#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>

void input();
bool isInvalidExpression(std::string expression);
int calcPostfix(std::string expression);
bool notNumberAndOperator(char C);
bool isOperator(char C);
bool isNumber(char C);
int calcOperator(char operation, int operand1, int operand2);

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
  }else if(isInvalidExpression(expression)){
    std::cerr << "Error: invalid expression" << std::endl;
    input();
  }else{
	  std::cout << calcPostfix(expression) << std::endl;
	  input();
   }
	return;
}

int calcPostfix(std::string expression){
	std::stack<int> s;

	for(unsigned i = 0;i < expression.length();i++){
    if(expression[i] == ' '){
      continue;
    }else if(isOperator(expression[i])) {
			int operand2 = s.top(); s.pop();
			int operand1 = s.top(); s.pop();
			int result = calcOperator(expression[i], operand1, operand2);
			s.push(result);
		}else if(isNumber(expression[i])){
			int operand = 0;
			while(i<expression.length() && isNumber(expression[i])) {
				operand = (operand*10) + (expression[i] - '0');
				i++;
			}
			i--;
			s.push(operand);
		}
	}
	return s.top();
}

bool isInvalidExpression(std::string e){
  int num = 0;
  int op = 0;

  for(unsigned i = 0; i < e.length(); i++) {
    if(e[i] == ' '){
      continue;
    }else if(notNumberAndOperator(e[i])){
      input();
    }else if(isNumber(e[i])){
      num++;
    }else if(isOperator(e[i])){
      op++;
    }
  }
  if (num != 2) {
    return true;
  }else if (op != 1) {
    return true;
  }else{
    return false;
  }
}

bool notNumberAndOperator(char C){
  if((C >= '0' && C <= '9')|| C == '+' || C == '-' || C == '*' || C == '/' || C == '.'){
    return false;
  }else{
    std::cerr << "Error: unknown symbol '" << C << "'" << std::endl;
    return true;
  }
}

bool isNumber(char C){
	if((C >= '0' && C <= '9') || C == '.'){
    return true;
  }else{
	  return false;
  }
}

bool isOperator(char C){
	if(C == '+' || C == '-' || C == '*' || C == '/'){
		return true;
  }else{
	  return false;
  }
}

int calcOperator(char operation, int operand1, int operand2){
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
