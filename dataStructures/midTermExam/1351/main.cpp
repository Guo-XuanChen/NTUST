/*
    File      : main.cpp
    Time      : 2019/11/05 00:13:15
    Author    : Guo-XuanChen
*/
#include <iostream>

using namespace std;

class String 
{
    char *str;
    unsigned int length;
    
    public:
        String(){};
        bool operator==(const String&);
        bool operator==(const char*);
        // The first appear position of the string 
        void find(const String&);
        // The appear frequency of a - z
        void freq();
        // Remove a specific string from the string
        void del(unsigned int, unsigned int);
        // Remove a specific character from the string
        void chdel(char);
        friend istream& operator>>(istream&, String&);
        void printString();
};

int main(int argc, char **argv)
{
    String string1;
    String cmd;
    
    cin >> string1;
    while(cin >> cmd)
    {
        if(cmd == "chdel"){
            char delChar;
            cin >> delChar;
            string1.chdel(delChar);   
        }
        else if(cmd == "del")
        {
            unsigned int position, len;
            cin >> position >> len;
            string1.del(position, len);
        }
        else if(cmd == "find")
        {
            String string2;
            cin >> string2;
            string1.find(string2);   
        }
        else if(cmd == "freq")
        {
            string1.freq();
        }
    }
    return 0;
}

istream& operator>>(istream& is, String& string)
{
    unsigned int count = 0;
    unsigned int dynamic = 10;
    char *oneChar = new char[dynamic];

    while(is.get(oneChar[count]))
    {
        if(oneChar[count] == '\n' || oneChar[count] == ' ')
        {
            break;
        }
        
        if(count == dynamic - 1)
        {
            char *buff = new char[dynamic];
            for(unsigned int x =0; x<dynamic; x++)
            {
                buff[x] = oneChar[x];
            }

            delete [] oneChar;
            oneChar = NULL;
            
            oneChar = new char[dynamic*2];
            for(unsigned int x =0; x<dynamic; x++)
            {
                oneChar[x] = buff[x];
            }

            delete [] buff;
            buff = NULL;
            dynamic *= 2;
        }
        count++;
    }

    oneChar[count] = '\0';
    string.str = oneChar;
    string.length = count;
    return is;
}

void String::printString()
{
    cout << this->str << endl;
}

bool String::operator==(const String& string)
{
    if(this->length != string.length)
    {
        return false;
    }

    for(unsigned int x = 0; x < this->length; x++)
    {
        if(this->str[x] != string.str[x])
        {
            return false;
        }
    }   
    return true;
}

bool String::operator==(const char* string)
{
    unsigned int stringLength = 0;
    while(string[stringLength] != '\0')
    {
        stringLength++;
    }

    if(this->length != stringLength)
    {
        return false;
    }

    for(unsigned int x = 0; x < this->length; x++)
    {
        if(this->str[x] != string[x])
        {
            return false;
        }
    }   
    return true;
}

void String::del(unsigned int position, unsigned int len)
{
    char *buff = new char[100];
    unsigned int count = 0;
    for(unsigned int x = 0; x < this->length; x++)
    {
        if(x < position || x >= (position + len))
        {
            buff[count] = str[x];
            count++;
        }
    }

    buff[count] = '\0';
    delete [] this->str;

    this->str = buff;
    this->length = count;
    
    printString();
}

void String::chdel(char delChar)
{
    char *buff = new char[100];

    unsigned int count = 0;
    for(unsigned int x = 0; x < this->length; x++)
    {
        if(this->str[x] != delChar)
        {
            buff[count] = this->str[x];
            count++;
        }  
    }

    buff[count] = '\0';
    delete [] this->str;
    
    this->str = buff;
    this->length = count;

    printString();
}

void String::find(const String& findString)
{
    int position = -1;
    for(unsigned int x = 0; x < this->length; x++) {
        if(this->str[x] == findString.str[0])
        {
            position = x;
            unsigned int y;
            for(y = 1;y < findString.length; y++)
            {
                if(x + y >= this->length)
                {
                    position = -1;
                    break;
                }

                if(this->str[x + y] != findString.str[y])
                {
                    position = -1;
                    break;
                }
            }

            if(y == findString.length)
            {
                break;
            }
        }
    }
    cout << position << endl;
}

void String::freq()
{
    unsigned int freqHole[26] = { 0 };
    
    for(unsigned int x = 0; x < this->length; x++)
    {
        freqHole[this->str[x] - 97]++;
    }
    
    for(unsigned int x = 0; x < 26; x++)
    {
        if(freqHole[x] > 0)
        {
            printf("%c %d\n", x + 97, freqHole[x]);
        }
    }
}