/*
    File      : main.cpp
    Time      : 2019/12/11 13:14:01
    Author    : Guo-XuanChen
*/
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

class Bucket;

class Object {
    public:
    string key;
    string data;
    Object(string key, string data) :key(key), data(data) {};
    friend class Bucket;
};

class Bucket {
    public:
    vector<Object>* data;
    Bucket() { data = new vector<Object>(); };
    bool overflow = false;
};

unsigned int pow(unsigned int X, unsigned int power)
{
    if (power == 0)
    {
        return 1;
    }
    return X * pow(X, power - 1);
}

unsigned int hashFunction(string key, unsigned int p)
{
    unsigned int index = 0;
    for (unsigned int x = 0; x < p; x++)
    {
        index += (key[5 - x] - '0') * pow(2, x);
    }
    return index;
}

int main(int argc, char** argv)
{
    string cmd;
    vector<Bucket> Buckets;

    unsigned int p = 2;
    for(unsigned int x = 0; x < pow(2, p); x++)
    {
        Buckets.push_back(Bucket());
    }

    while (cin >> cmd)
    {
        if (cmd == "put")
        {
            string data;
            cin >> data;
            string key = "1";
            key += bitset<2>((data[0] - 'A') + 64).to_string();
            key += bitset<3>((data[1] - '0')).to_string();

            Object object(key, data);

            unsigned int index = hashFunction(key, p);

            while(Buckets[index].data->size() >= 2 && Buckets[index].overflow)
            {
                p += 1;
                index = hashFunction(key, p);

                for(unsigned int x = 0; x < pow(2, p - 1); x++)
                {
                    Buckets.push_back(Buckets[x]);
                    Buckets[Buckets.size() - 1].overflow = false;
                }

                for(unsigned int x = 0; x < pow(2, p - 1); x++)
                {
                    if(Buckets[x].data->size() > 0)
                    {
                        for(unsigned int i = 0; i < Buckets[x].data->size(); i++)
                        {
                            auto y = &(*Buckets[x].data)[i];
                            unsigned int newIndex = hashFunction(y->key, p);
                            if(newIndex != x && Buckets[x].overflow)
                            {
                                Object object2(y->key, y->data);
                                Buckets[x].data->erase(Buckets[x].data->begin() + i--);
                                Buckets[x].overflow = false;
                                Buckets[newIndex].data = new vector<Object>();
                                Buckets[newIndex].data->push_back(object2);
                            }
                        }
                    }
                }           
            }

            cout << index << endl;
            if(Buckets[index].data->size() < 2)
            {
                Buckets[index].data->push_back(object);
            }
            else
            {
                Buckets[index].data = new vector<Object>();
                Buckets[index].data->push_back(object);
            }

            if(Buckets[index].data->size() >= 2)
            {
                Buckets[index].overflow = true;
            }
        }
        else if (cmd == "get")
        {
            unsigned int data;
            cin >> data;
            
            if(data >= Buckets.size())
            {
                cout << "Out of range." << endl;
            }
            else
            {
                if(Buckets[data].data->size() == 0)
                {
                    cout << "The bucket is empty." << endl;
                }
                else
                {
                    unsigned int y;
                    for (y = 0; y < Buckets[data].data->size() - 1; y++)
                    {
                        cout << (*Buckets[data].data)[y].data << " ";
                    }
                    cout << (*Buckets[data].data)[y].data << endl;
                }
            }
        }
        else if (cmd == "exit")
        {
            return 0;
        }
    }
 return 0;
}