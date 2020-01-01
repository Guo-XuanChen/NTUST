/*
    File      : main.cpp
    Time      : 2019/11/05 00:13:15
    Author    : Guo-XuanChen
*/
#include <iostream>
#include <string>

using namespace std;

class Store
{
    private:
        string store;
        unsigned int length;

    public:
        Store(string store):store(store),length(store.length()){};
        void freq();
        void find(const string&);
        void chdel(char);
        void del(unsigned int, unsigned int);

};

int main(int argc, char **argv)
{
    string cmd, store;
    cin >> store;
    Store Store1(store);
    while(cin >> cmd)
    {
        if(cmd == "freq")
        {
            Store1.freq();
        }
        else if(cmd == "find")
        {
            string findString;
            cin >> findString;
            Store1.find(findString);
        }
        else if(cmd == "chdel")
        {
            char delChar;
            cin >> delChar;
            Store1.chdel(delChar);
        }
        else if(cmd == "del")
        {
            unsigned int start, length;
            cin >> start >> length;
            Store1.del(start, length);
        }
    }
    return 0;
}

void Store::chdel(char delchar)
{
    string temp;
    for(unsigned int x = 0; x < this->length; x++)
    {
        if(this->store[x] != delchar)
        {
            temp += this->store[x];
        }
    }
    this->store.clear();
    this->store = temp;
    this->length = store.length();
    cout << this->store << endl;
}

void Store::del(unsigned int start, unsigned int length)
{
    string temp;
    for(unsigned int x = 0; x < this->length; x++)
    {
        if(x < start || x >= (start + length))
        {
            temp += this->store[x];
        }
    }
    this->store.clear();
    this->store = temp;
    this->length = store.length();
    cout << this->store << endl;
}

void Store::find(const string& findString)
{
    int position = -1;
    for(unsigned int x = 0; x < this->length; x++)
    {
        if(this->store[x] == findString[0])
        {
            position = x;
            unsigned int y;
            for(y = 1; y < findString.length(); y++)
            {
                if(x + y >= this->length)
                {
                    position = -1;
                    break;
                }

                if(this->store[x + y] != findString[y])
                {
                    position = -1;
                    break;
                }
            }
            
            if(y == findString.length())
            {
                break;
            }
        }
    }
    cout << position << endl;
}

void Store::freq()
{
    unsigned int freqHole[26] = { 0 };

    for(unsigned int x = 0; x < this->length; x++)
    {
        freqHole[this->store[x] - 97]++;
    }

    for(unsigned int x = 0; x < 26; x++)
    {
        if(freqHole[x] > 0) { 
            printf("%c %d\n", x + 97, freqHole[x]);
        }
    }
}
