/*
    File      : main.cpp
    Time      : 2019-09-29 02:21:53
    Author    : Guo-XuanChen
*/
#include <iomanip>
#include <iostream>
#include <string>
 
using namespace std;
 
class stack { 
   private:
        string stackStorage;
        string output;
        int top = -1;
        void push(char operstors);
        void pop();
        int comp(char operstors);
    public:
        string expr;
        void convertPre();      
        void convertPost();
};
 
void stack::convertPre(){
    output.clear();
    unsigned int exprLen = expr.length();
    for(int x = exprLen-1; x>=0;){
        if(expr[x] == ')' || expr[x] == '(' || expr[x] == '+' || expr[x] == '-' || expr[x] == '*' || expr[x] == '/'){
           if(expr[x] != ')' && expr[x] != '('){
                if(top>=0){
                    if(stackStorage[top]==')'){
                        push(expr[x]);
                    }else{
                        if(comp(expr[x]) > comp(stackStorage[top])){
                            pop();
                            continue;
                        }else{
                            push(expr[x]);
                        }
                    }
                }else{
                    push(expr[x]);
                }
            }else if(expr[x] == ')'){
                push(expr[x]);
            }else if(expr[x] == '('){
                pop();
                if(stackStorage[top]!=')'){
                    continue;
                }
            }
            x--;
        }else{
            output += expr[x];
            x--;
        }
    }
     
    while(top>=0){
        pop();
    }
 
    int outputLen = output.length();
    string result;
    cout << "Prefix: ";
    for(int x=outputLen-1; x>=0; x--){
        result += output[x];
    }
    cout << result << endl;
}
 
void stack::convertPost(){
    output.clear();
    unsigned int exprLen = expr.length();
    for(unsigned int x = 0; x<exprLen;){
        if(expr[x] == ')' || expr[x] == '(' || expr[x] == '+' || expr[x] == '-' || expr[x] == '*' || expr[x] == '/'){
           if(expr[x] != ')' && expr[x] != '('){
                if(top>=0){
                    if(stackStorage[top]=='('){
                        push(expr[x]);
                    }else{
                        if(comp(expr[x]) >= comp(stackStorage[top])){
                            pop();
                            continue;
                        }else{
                            push(expr[x]);
                        }
                    }
                }else{
                    push(expr[x]);
                }
            }else if(expr[x]=='('){
                push(expr[x]);
            }else if(expr[x]==')'){
                pop();
                if(stackStorage[top]!='('){
                    continue;
                }else{
                    pop();
                }
                
            }
            x++;
        }else{
            output += expr[x];
            x++;
        }
    }
     
    while(top>=0){
        pop();
    }
 
    int outputLen = output.length();
    string result;
    cout << "Postfix: ";
    for(int x=0; x<outputLen; x++){
        result += output[x];
    }
    cout << result << endl;
 
}
 
void stack::push(char operstors){
    stackStorage += operstors;                                               
    top++;
}
 
void stack::pop(){
    if(stackStorage[top] != ')' && stackStorage[top] != '('){
        output += stackStorage[top];
    }
    string newStackStorage;
    if(top>0){
        newStackStorage.assign(stackStorage,  0, top);
    }
    stackStorage = newStackStorage;
    top--;
}
 
int stack::comp(char operstors){
    if(operstors == '+' || operstors == '-'){
        return 3;
    }else if(operstors == '*' || operstors == '/'){
        return 2;
    }
    return 1;
}
 
int main(int argc, char **argv){
    string input;
    while(cin >> input){
        stack stack1;
        stack1.expr = input;
        stack1.convertPost();
        stack1.convertPre();
        cout << endl;
    }
    return 0;
}
