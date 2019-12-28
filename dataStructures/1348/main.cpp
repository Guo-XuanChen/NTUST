/*
    File      : main.cpp
    Time      : 2019/12/28 22:16:23 
    Author    : Guo-XuanChen
*/
#include <iostream>
#include <vector>
#include <queue>

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
	this->child.push_back(0);
}

Node::Node(unsigned int data)
{
	this->datas.push_back(data);
	this->child.push_back(0);
	this->child.push_back(0);
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
		int removeIndex = this->datas.size() / 2;
		int parentValue = this->datas[removeIndex];
		
		this->datas.erase(this->datas.begin() + removeIndex);
		if(!this->parent)
		{
			this->parent = new Node();
		}

		vector<Node*> nodes;
		Node *node1 = new Node(), *node2 = new Node();
		node1->datas.assign(this->datas.begin(), this->datas.begin() + removeIndex);
		node1->child.assign(this->child.begin(), this->child.begin() + this->child.size() / 2);
		node1->parent = this->parent;
		nodes.push_back(node1);
		node2->datas.assign(this->datas.begin() + removeIndex, this->datas.end());
		node2->child.assign(this->child.begin() + this->child.size() / 2, this->child.end());
		node2->parent = this->parent;
		nodes.push_back(node2);
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
	Node* presentNode = TwoThreeTree::root;
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
	queue<Node *> q;

	q.push(this->root);					   
    								        
    while(1)
	{
		queue<Node*> q2;
		
		while(q.size() > 1)
		{
			Node *current = q.front(); 	q.pop();

			for(unsigned int x = 0; x < current->datas.size() - 1; x++)
			{
				cout << current->datas[x] << " ";
			}
			cout << current->datas[current->datas.size() - 1];

			for(unsigned int x = 0; x < current->child.size(); x++)
			{
				if(current->child[x] != NULL)
				{
					q2.push(current->child[x]);
				}				
			}

			cout << " / ";
			
		}

		if(!q.empty())
		{
			Node *current = q.front(); q.pop();

			for(unsigned int x = 0; x < current->datas.size() - 1; x++)
			{
				cout << current->datas[x] << " ";
			}
			cout << current->datas[current->datas.size() - 1];

			for(unsigned int x = 0; x < current->child.size(); x++)
			{
				if(current->child[x] != NULL)
				{
					q2.push(current->child[x]);
				}
			}
			cout << endl;
		}

		if(!q2.empty())
		{
			while(!q2.empty())
			{
				q.push(q2.front());
				q2.pop();
			}
		}
		else
		{
			break;
		}
	}	
}