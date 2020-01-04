/*
    File      : stack.app
    Time      : 2020/01/04 17:47:17
    Author    : Guo-XuanChen
*/
#include <iostream>

using namespace std;

class Stack;

class Node
{
    unsigned int number;             // stored value will be greater than 0.
    Node* down = NULL;               // pointer to down.
    friend class Stack;
    public:
    Node(unsigned int number):number(number){};
};

class Stack
{
    Node *top = NULL;
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

    Node* delNode = this->top;
    this->top = delNode->down;
    delete delNode; 
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

    Node* current = this->top;
    while(current != NULL)
    {
        if(current->down == NULL)
        {
            cout << current->number << endl;
        }
        else
        {
             cout << current->number << " ";
        }

        current = current->down;
    }
}