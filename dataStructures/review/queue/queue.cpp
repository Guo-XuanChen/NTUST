/*
    File      : queue.cpp
    Time      : 2020/01/03 18:51:04
    Author    : Guo-XuanChen
*/
#include <iostream>

using namespace std;

class Queue;

class Node
{
    unsigned int number;                // stored value will be greater than 0.
    Node* right = NULL;                 // pointer to down.
    friend class Queue;
    public:
    Node(unsigned int number):number(number){};
};

class Queue
{
    Node* front = NULL;
    public:
    bool isEmpty();
    void pop(); 
    void print();  
    void push(unsigned int);     
    unsigned int getFront();             
};

int main(int argc, char **argv)
{
    Queue queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.print();
    queue.pop();
    queue.print();
    if(queue.getFront() > 0)
    {
        cout << queue.getFront() << endl;
    }
    queue.push(4);
    queue.pop();
    queue.print();

    return 0;
}

bool Queue::isEmpty()
{
    if(this->front == NULL)
    {
        return true;
    }
    return false;
}

void Queue::push(unsigned int number)
{
    Node* newNode = new Node(number);
    if(this->isEmpty())
    {
        this->front = newNode;
        return;
    }

    Node* current = this->front;
    while(current->right != NULL)
    {
        current = current->right;
    }
    current->right = newNode;
}

void Queue::pop()
{
    if(this->isEmpty())
    {
        cout << "The queue is empty";
        return;
    }

    Node* delNode = this->front;
    this->front = delNode->right;
    delete delNode;
}

unsigned int Queue::getFront()
{
    if(this->isEmpty())
    {
        cout << "The queue is empty";
        return 0;
    }
    return this->front->number;
}

void Queue::print()
{
    if(this->isEmpty())
    {
        cout << "The queue is empty";
        return;
    }

    Node* current = this->front;
    while(current != NULL)
    {
        if(current->right == NULL)
        {
            cout << current->number << endl;
        }
        else
        {
            cout << current->number << " ";
        }

        current = current->right;
    }
}