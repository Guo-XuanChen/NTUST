/*
    File      : main.cpp
    Time      : 2019/11/19 19:58:03
    Author    : Guo-XuanChen
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(unsigned int &p1, unsigned int &p2)
{
    unsigned int temp = p1;
    p1 = p2;
    p2 = temp;
}

void maxHeapify(vector<unsigned int> &array, unsigned int root, unsigned int length)
{
    unsigned int left = 2*root, right = 2*root + 1, largest;                

    if(left <= length && array[left] > array[root])
    {
        largest = left;
    }
    else
    {
        largest = root;
    }

    if (right <= length && array[right] > array[largest])
    {
        largest = right;
    }

    if(largest != root) 
    {                        
        swap(array[largest], array[root]);         
        maxHeapify(array, largest, length);        
    }
}

void buildMaxHeap(vector<unsigned int> &array)
{
    for(unsigned int x = (unsigned int)array.size()/2; x >= 1 ; x--)
    {
        maxHeapify(array, x, (unsigned int)array.size() - 1);    
    }
}

void heapSort(vector<unsigned int> &array)
{
    array.insert(array.begin(), 0);                    
    buildMaxHeap(array);                                
    array.erase(array.begin());                        
}

int main(int argc, char **argv)
{
    string cmd;
    unsigned int length; 
    cin >> length;

    unsigned int inputArray[length];
    for(unsigned int x = 0; x < length; x++)
    {
        cin >> inputArray[x];
    }
    
    unsigned int current = 0;
    vector<unsigned int> array(inputArray, inputArray+sizeof(inputArray)/sizeof(unsigned int));
    heapSort(array);

    while(cin >> cmd)
    {
        if(cmd == "heap")
        {
            array.insert(array.begin(), array[array.size()-1]);
            array.erase(array.begin()+1); 
            array.pop_back();
            heapSort(array);
            current = 0;
        }
        else if(cmd == "left")
        {
            current = current * 2 + 1;
            cout << array[current] << endl;
        }
        else if(cmd == "right")
        {
            current = current * 2 + 2;
            cout << array[current] << endl;
        }
        else if(cmd == "show")
        {
            cout << array[current] << endl;
        }
    }
    return 0;
}