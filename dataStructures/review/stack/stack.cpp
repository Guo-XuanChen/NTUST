/*
    File      : stack.app
    Time      : 2020/01/04 17:47:17
    Author    : Guo-XuanChen
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stack;

class Node
{
    unsigned int number;             // stored value will be greater than 0.
    Node* down;                      // pointer to down.
    friend class Stack;
    public:
    Node(unsigned int number):number(number){};
};

class Stack
{
    Node *top;
    public:
    bool isEmpty();
    void print();
    void pop();
    void push(unsigned int);
    unsigned int getTop();
};

int main(int argc, char **argv)
{
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.print();
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.pop();
    stack.print();
}

bool Stack::isEmpty()
{
    if(this->top == NULL)
    {
        return true;
    }
    return false;
}

void Stack::push(unsigned int number)
{
    Node *newNode = new Node(number);
    if(this->isEmpty())
    {
        top = newNode;
        return;
    }
    newNode->down = this->top;
    this->top = newNode;
}

void Stack::pop()
{
    if(this->isEmpty())
    {
        cout << "The stack is empty" << endl;
        return;
    }

    Node* del = this->top;
    if(top->down != NULL)
    {
        this->top = this->top->down;
        delete del; 
    }
    else
    {
        this->top = NULL; 
        delete del; 
    }
}
    
unsigned int Stack::getTop()
{
    if(this->isEmpty())
    {
        cout << "The stack is empty" << endl;
        return 0;
    }
    return this->top->number;
}

void Stack::print()
{
    if(this->isEmpty())
    {
        cout << "The stack is empty" << endl;
        return;
    }

    while(!this->isEmpty())
    {
        if(this->top->down == NULL)
        {
           cout << this->getTop() << endl;
        }
        else
        {
           cout << this->getTop() << " ";
        }
        this->pop();
    }
}