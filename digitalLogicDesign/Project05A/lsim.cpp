/*
    File      : lsim.cpp
    Time      : 2019/12/20 19:38:43
    Author    : Guo-XuanChen
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cmath>
#include <vector>

using namespace std;

struct gate
{
    string name;
    vector<string> inputs;
    string output;
    bool operating = false;
};

string modelName;
map<string, bool> _variable;
vector<string> _inputs; 
vector<string> _outputs;
vector<gate> _gate;


unsigned int pow(unsigned int n, unsigned int X)
{
    if(X == 0)
    {
        return 1;
    }
    else
    {
        return n * pow(n, X - 1);
    }
    
}

string intToBinStr(unsigned int randNumber)
{
    string r = "", result = "";

	while(randNumber)
	{
		r += randNumber % 2 ? '1' : '0';
		randNumber /= 2;
	}

	for(unsigned int x = _variable.size() - r.length(); x > 0; --x)
	{
		r += '0';
	}

	for(int x = r.length() - 1; x >= 0; --x)
	{
		result += r[x];
	}

	return result;
}

void readBlif(char *filename)
{
    string line, cmd;
    bool inputStart  = false;
    bool outputStart = false;
    ifstream file(filename);


    while(getline(file, line))
    {
        istringstream iss(line);
        iss >> cmd;

        if(cmd == ".model")
        {
            iss >> modelName;
        }
        else if(cmd == ".inputs" || inputStart)
        {
            string variableBuff;
            
            if(inputStart)
            {
                variableBuff = cmd;
                inputStart = false;
                _inputs.push_back(variableBuff);
                _variable.insert(pair<string, bool>(variableBuff, 0));
            }

            while(iss >> variableBuff)
            {
                if(variableBuff[0] == 92)
                { 
                    inputStart = true;
                    continue;
                }
                else
                {
                    inputStart = false;
                }
                 _inputs.push_back(variableBuff);
                _variable.insert(pair<string, bool>(variableBuff, 0));
            }
        }            
        else if(cmd == ".outputs" || outputStart)
        {
            string variableBuff;

            if(outputStart)
            {
                variableBuff = cmd;
                _outputs.push_back(variableBuff);
                outputStart = false;
            }
            
            while(iss >> variableBuff)
            {
                if(variableBuff[0] == 92)
                {
                    outputStart = true;
                    continue;
                }
                else
                {
                    outputStart = false;
                }
                _outputs.push_back(variableBuff);
            }
            
        }
        else if(cmd == ".gate")
        {
            gate gateBuff;
            unsigned int inputCount;
            iss >> gateBuff.name;
            if(gateBuff.name == "zero" || gateBuff.name == "one")
            {
                inputCount = 0;
            }
            else if(gateBuff.name == "BUF" || gateBuff.name == "NOT")
            {
                inputCount = 1;
            }
            else 
            {
                inputCount = gateBuff.name[gateBuff.name.size() - 1] - 48;
                gateBuff.name.pop_back();
            }         
        
            string gateLine;
            for(unsigned int x = 0; x < inputCount; x++)
            {
                iss >> gateLine;
                gateBuff.inputs.push_back(gateLine.substr(2, gateLine.size() - 1));
            }
            
            iss >> gateLine;
            gateBuff.output = gateLine.substr(2, gateLine.size() - 1);
            _gate.push_back(gateBuff);
            
        }
        else if(cmd == ".end")
        {
           return;
        }
    }
}

void writeSti(char *filename)
{
    ofstream file;
    file.open(filename);
    file << ".i " << _variable.size() << endl;

    unsigned int num = pow(2, _variable.size()) - 1;
    for(unsigned int x = 0; x <= _variable.size() + _outputs.size(); x++)
    {
        unsigned int randNumber = (rand() % num);
        file << intToBinStr(randNumber) << endl;
    }
    file << ".e" << endl;
}

void gateOperater(gate& currentGate, map<string, bool>& _variableExp)
{
    bool result = 0;

    if(currentGate.operating == true)
    {
        return;
    }

    if(currentGate.name == "zero")
    {
        result = 0;
    }
    else if(currentGate.name == "one")
    {
        result = 1;
    }
    else 
    {
        map<string, bool>::iterator it;
        for(unsigned int x = 0; x < currentGate.inputs.size(); x++)
        {
            it = _variableExp.find(currentGate.inputs[x]);
            if(it == _variableExp.end()) // not found
            {
                return;
            }
        }

        if(currentGate.name == "BUF")
        {
            result = _variableExp[currentGate.inputs[0]];
        }
        else if (currentGate.name == "NOT")
        {
            result = _variableExp[currentGate.inputs[0]];
            result = !result;
        }
        else if(currentGate.name == "AND")
        {
            result = _variableExp[currentGate.inputs[0]] & _variableExp[currentGate.inputs[1]];
            if(currentGate.inputs.size() == 3)
            {
                result &= _variableExp[currentGate.inputs[2]];
            }
        }
        else if(currentGate.name == "NAND")
        {
            result = _variableExp[currentGate.inputs[0]] & _variableExp[currentGate.inputs[1]];
            if(currentGate.inputs.size() == 3)
            {
                result &= _variableExp[currentGate.inputs[2]];
            }
            result = !result;
        }
        else if(currentGate.name == "OR")
        {
            result = _variableExp[currentGate.inputs[0]] | _variableExp[currentGate.inputs[1]];
            if(currentGate.inputs.size() == 3)
            {
                result |= _variableExp[currentGate.inputs[2]];
            }
        }
        else if(currentGate.name == "NOR")
        {
            result = _variableExp[currentGate.inputs[0]] | _variableExp[currentGate.inputs[1]];
            if(currentGate.inputs.size() == 3)
            {
                result |= _variableExp[currentGate.inputs[2]];
            }
            result = !result;
        }
        else if(currentGate.name == "XOR")
        {
            result = _variableExp[currentGate.inputs[0]] ^ _variableExp[currentGate.inputs[1]];
        }
        else if(currentGate.name == "XNOR")
        {
            result = _variableExp[currentGate.inputs[0]] ^ _variableExp[currentGate.inputs[1]];
            result = !result;
        }
    }

    currentGate.operating = true;

    // output not exist.
    if(_variableExp.find(currentGate.output) == _variableExp.end()) 
    {
        _variableExp.insert(pair<string, bool>(currentGate.output, result));
    }
    else
    {
        _variableExp[currentGate.output] = result;
    }
     
}

void operating(char *filename, char *filename2)
{
    map<string, bool> _variableExp = _variable;
    vector<gate> _gateExp = _gate;
    
    string line, cmd;
    unsigned int inputCount = 0;
    ifstream file(filename);
    ofstream file2(filename2);

    while(getline(file, line))
    {
        istringstream iss(line);
        iss >> cmd;
        
        if(cmd == ".i")
        {
            iss >> inputCount;
            file2 << ".i " << inputCount << endl;
            file2 << ".o " << _outputs.size() << endl;
        }
        else if(cmd == ".e")
        {
            file2 << ".e " << endl;
            return;
        }
        else
        {
            _variableExp = _variable;
            _gateExp = _gate;

            for(unsigned int x = 0; x < inputCount; x++)
            {
                _variableExp[_inputs[x]] = cmd[x] - 48;
            }

            for(unsigned int x = 0; x <= _gateExp.size(); x++)
            {
               
                if(x == _gateExp.size())                                // Make sure all gates are calculated
                {
                    for(unsigned int y = 0; y < _gateExp.size(); y++)
                    {
                        if(_gateExp[y].operating == false)
                        {
                            x = 0; 
                            break;
                        }
                    }
                }
                else if(_gateExp[x].operating == false)
                {
                    gateOperater(_gateExp[x], _variableExp);
                }
            }

            string result;
            for(unsigned int x = 0; x < _outputs.size(); x++)
            {
                result += _variableExp[_outputs[x]] + 48;
            }

            file2 << cmd << " " << result << endl;
        }
    }
        
}

int main(int argc, char **argv)
{
    readBlif(argv[1]);                  // BLIF FILE

    writeSti(argv[2]);                  // STI FILE
    
    operating(argv[2], argv[3]);        // Operating
    
    return 0;
}