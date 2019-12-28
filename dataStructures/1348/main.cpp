/*
    File      : main.cpp
    Time      : 2019/12/28 22:16:23 
    Author    : Guo-XuanChen
*/
#include <iostream>
#include <vector>

using namespace std;

class Node
{
	public:
	Node();
	Node(unsigned int);
	vector<unsigned int> datas;
	Node* parent = NULL;
	vector<Node*> child;

	Node* insert(unsigned int, vector<Node*> insertChild = vector<Node*>());
};

class TwoThreeTree
{
	public:
	Node* root = 0;
	Node* search(unsigned int);
	void insert(unsigned int);
	void print();
};


int main(int argc, char **argv)
{
    string cmd;
	TwoThreeTree Tree;

    while(cin >> cmd)
    {
        if(cmd == "insert")
        {
            unsigned int data;
            cin >> data; 
			Tree.insert(data);
        }
        else if(cmd == "print")
        {
			Tree.print();
        }
    }
    return 0;
}

Node::Node()
{
	this->child.push_back(NULL);
}

Node::Node(unsigned int data)
{
	this->datas.push_back(data);
	this->child.push_back(NULL);
	this->child.push_back(NULL);
}

Node* Node::insert(unsigned int data, vector<Node*> insertChild)
{
	unsigned int insertPosition = 0;
	
	for(insertPosition = 0; insertPosition < this->datas.size(); insertPosition++)
	{
		if(data < this->datas[insertPosition])
		{
			break;
		}
	}

	if(insertPosition != 0)
	{
		if(insertChild.size())
		{
			this->child.insert(this->child.begin() + insertPosition + 1, insertChild[1]);
			this->child[insertPosition] = insertChild[0];
		}
		else
		{
			this->child.insert(this->child.begin() + insertPosition + 1, 0);
		}
		
	}
	else
	{
		if(insertChild.size())
		{
			this->child.insert(this->child.begin(), insertChild[0]);
			this->child[1] = insertChild[1];
		}
		else
		{
			this->child.insert(this->child.begin(), 0);
		}	
	}

	this->datas.insert(this->datas.begin() + insertPosition, data);

	if(this->datas.size() > 2)
	{
		int parentValue = this->datas[1];	
		this->datas.erase(this->datas.begin() + 1);

		if(!this->parent)
		{
			this->parent = new Node();
		}

		vector<Node*> nodes;
		Node *node1 = new Node(), *node2 = new Node();

		//left node
		node1->datas.assign(this->datas.begin(), this->datas.begin() + 1);
		node1->child.assign(this->child.begin(), this->child.begin() + this->child.size() / 2);
		node1->parent = this->parent;
		nodes.push_back(node1);

		// right node
		node2->datas.assign(this->datas.begin() + 1, this->datas.end());
		node2->child.assign(this->child.begin() + this->child.size() / 2, this->child.end());
		node2->parent = this->parent;
		nodes.push_back(node2);

		// left and right, child 
		for(unsigned int x = 0; x < nodes.size(); x++)
		{
			for(unsigned int y = 0; y < nodes[x]->child.size(); y++)
			{
				if(nodes[x]->child[y])
				{
					nodes[x]->child[y]->parent = nodes[x];
				}
			}
		}
		return this->parent->insert(parentValue, nodes);
	}
	
	Node* root = this;
	while(root->parent)
	{
		root = root->parent;
	}
	return root;
}

Node* TwoThreeTree::search(unsigned int data)
{
	Node* presentNode = this->root;
	while(presentNode)
	{
		unsigned int position = 0;
		for(position = 0; position < presentNode->datas.size() - 1; position++)
		{
			if(data <= presentNode->datas[position])
			{
				break;
			}
		}
		
		if(data < presentNode->datas[position] && presentNode->child[position])
		{
			presentNode = presentNode->child[position];
		}
		else if(data > presentNode->datas[position] && presentNode->child[position + 1])
		{
			presentNode = presentNode->child[position + 1];
		}
		else
		{
			return presentNode;
		}
	}
	return presentNode;
}

void TwoThreeTree::insert(unsigned int data)
{
	if(this->root)
	{
		Node* inserNode = this->search(data);
		this->root = inserNode->insert(data);
	}
	else
	{
		this->root = new Node(data);
	}
}

// Level Order
void TwoThreeTree::print()
{
	vector<Node *>  store;
	store.push_back(this->root);

	while(!store.empty())
	{
		vector<Node *> childBuff;
		for(unsigned int x = 0; x < store.size() - 1; x++)
		{
			for(unsigned int y = 0; y < store[x]->datas.size() - 1; y++)
			{
				cout << store[x]->datas[y] << " ";
			}
			cout << store[x]->datas[store[x]->datas.size() - 1];
	
			for(unsigned int y = 0; y < store[x]->child.size(); y++)
			{
				if(store[x]->child[y] != NULL)
				{
					childBuff.push_back(store[x]->child[y]);
				}
			}

			cout << " / ";
		}
		
		for(unsigned int x = 0; x < store[store.size() - 1]->datas.size() - 1; x++)
		{
			cout << store[store.size() - 1]->datas[x] << " ";
		}
		cout << store[store.size() - 1]->datas[store[store.size() - 1]->datas.size() - 1];

		for(unsigned int x = 0; x < store[store.size() - 1]->child.size(); x++)
		{
			if(store[store.size() - 1]->child[x] != NULL)
			{
				childBuff.push_back(store[store.size() - 1]->child[x]);
			}
		}
		
		cout << endl;
		store.clear();
		store = childBuff;
	}
}