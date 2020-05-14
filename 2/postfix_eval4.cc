/*
  Evaluation Of postfix Expression in C++
  Input Postfix expression must be in a desired format.
  Operands must be integers and there should be space in between two operands.
  Only '+'  ,  '-'  , '*' and '/'  operators are expected.
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

int main() {
  input();
  return 0;
}

void input() {
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
// Function to evaluate Postfix expression and return output
int calcPostfix(std::string expression) {
	// Declaring a Stack from Standard template library in C++.
	std::stack<int> S;

	for(int i = 0;i < expression.length();i++) {

    // Scanning each character from left.
    // If character is a delimitter, move on.
    if(expression[i] == ' '){
      continue;
    }else if(isOperator(expression[i])) {	// If character is operator, pop two elements from stack, perform operation and push the result back.
			// Pop two operands.
			int operand2 = S.top(); S.pop();
			int operand1 = S.top(); S.pop();
			// Perform operation
			int result = calcOperator(expression[i], operand1, operand2);
			//Push back result of operation on stack.
			S.push(result);
		}else if(isNumber(expression[i])){
			// Extract the numeric operand from the string
			// Keep incrementing i as long as you are getting a numeric digit.
			int operand = 0;
			while(i<expression.length() && isNumber(expression[i])) {
				// For a number with more than one digits, as we are scanning from left to right.
				// Everytime , we get a digit towards right, we can multiply current total in operand by 10
				// and add the new digit.
				operand = (operand*10) + (expression[i] - '0');
				i++;
			}
			// Finally, you will come out of while loop with i set to a non-numeric character or end of string
			// decrement i because it will be incremented in increment section of loop once again.
			// We do not want to skip the non-numeric character by incrementing i twice.
			i--;

			// Push operand on stack.
			S.push(operand);
		}
	}
	// If expression is in correct format, Stack will finally have one element. This will be the output.
	return S.top();
}

bool isInvalidExpression(std::string e){
  int num = 0;
  int op = 0;

  for(int i = 0; i < e.length(); i++) {
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

// Function to verify whether a character is numeric digit.
bool isNumber(char C){
	if(C >= '0' && C <= '9'){
    return true;
  }else{
	return false;
  }
}

// Function to verify whether a character is operator symbol or not.
bool isOperator(char C){
	if(C == '+' || C == '-' || C == '*' || C == '/'){
		return true;
  }else{
	  return false;
  }
}

// Function to perform an operation and return output.
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
