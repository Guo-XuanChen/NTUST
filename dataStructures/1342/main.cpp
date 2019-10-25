/*
    File      : main.cpp
    Time      : 2019/10/22  10:24:48
    Author    : Guo-XuanChen
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BinaryTree;

class TreeNode 
{
    private:
        TreeNode *leftChild;
        TreeNode *rightChild;
        TreeNode *parent;
        int value;

    public:
        TreeNode():leftChild(NULL),rightChild(NULL),parent(NULL),value(0){};
        TreeNode(int value):leftChild(NULL),rightChild(NULL),parent(NULL),value(value){};
        friend class BinaryTree;
};

class BinaryTree 
{
    private:
        TreeNode *root;
        TreeNode* searchBST(int);
        TreeNode* leftMost(TreeNode*);
        TreeNode* successor(TreeNode*);
        void inOrder(TreeNode*);
        void preOrder(TreeNode*);
        void postOrder(TreeNode*);

        /* feature 3 and 4 */
        void inOrderRank(TreeNode*);
        int searchByValueDepth(TreeNode*);

        int nodeCount;
        vector<int> inOrderQueue;

    public:
        void insertNode(int);
        void deleteNode(int);
        void searchByValue(int);
        void searchByRank(int);
        void showInorder();
        void showPreorder();
        void showPostorder();

        BinaryTree():root(NULL),nodeCount(0){};
};

int main(int argc, char **argv)
{
    unsigned int cmd = 0, value = 0;
    BinaryTree BT;
    
    while(cin >> cmd)
    {
        if(cmd>=5)
        {
            if(cmd == 5)
            {   // inorder
                BT.showInorder();
            }
            else if(cmd == 6)
            {   // preorder
                BT.showPreorder();
            }
            else if(cmd == 7)
            {   // postorder    
                BT.showPostorder();
            }
        }
        else
        {
            cin >> value;
            if(cmd == 1)        
            {  // insertNode
                try
                {
                    BT.insertNode(value);
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }
                
            }
            else if(cmd == 2) 
            {   // deleteNode
                try
                {
                     BT.deleteNode(value);
                }
                catch(const char *msg)
                {
                    cout << msg << endl;
                }
               
            }
            else if(cmd == 3)
            {   // searchByValue
                try
                {
                     BT.searchByValue(value);
                }
                catch(const char *msg)
                {
                    cout << msg << endl;
                }
            }
            else if(cmd == 4)
            {   // searchByBank
                try
                {
                     BT.searchByRank(value);
                }
                catch(const char *msg)
                {
                    cout << msg << endl;
                }
            }
        }

    }
    return 0;
}

TreeNode* BinaryTree::searchBST(int value)
{
    TreeNode *current = root;               

    while (current != NULL && value != current->value) 
    {                                               
        if (current->value > value)
        {                      
            current = current->leftChild;   
        }
        else 
        {
            current = current->rightChild;  
        }
    }
    return current;
}

TreeNode* BinaryTree::leftMost(TreeNode *current)
{
    while (current->leftChild != NULL)
    {
        current = current->leftChild;
    }
    return current;
}

TreeNode* BinaryTree::successor(TreeNode *current)
{
    if (current->rightChild != NULL)
    {
        return leftMost(current->rightChild);
    }
    
    TreeNode *new_node = current->parent;
    
    while (new_node != NULL && current == new_node->rightChild)
    {
        current = new_node;
        new_node = new_node->parent;
    }
    
    return new_node;
}

void BinaryTree::insertNode(int value)
{
    TreeNode *newNode = new TreeNode(value);
    if(root == NULL)
    {
        root = newNode;
        cout << "[INSERT SUCCESS]" << endl;
        return;
    }

    TreeNode *current = root;
    while(current != NULL)
    {
        if(current->value > value)
        {
            if(current->leftChild == NULL)
            {
                newNode->parent = current;
                current->leftChild = newNode;
                nodeCount++;
                cout << "[INSERT SUCCESS]" << endl;
                return;
            }
            else
            {
                current = current->leftChild;
            }
        }
        else if(current->value < value)
        {
            if(current->rightChild == NULL)
            {
                newNode->parent = current;  
                current->rightChild = newNode;
                nodeCount++;
                cout << "[INSERT SUCCESS]" << endl;
                return;
            }
            else
            {
                 current = current->rightChild;
            }
        }
        else if(current->value == value)
        {
            throw "Duplicate data.";
        }
    }
}

void BinaryTree::deleteNode(int value)
{
    TreeNode *_delete = searchBST(value);   
    if(_delete == NULL)
    {
        throw "No such value to delete.";
    }

    TreeNode *deleteBuff = NULL;       
    TreeNode *deleteChild = NULL;      

    if(_delete->leftChild == NULL || _delete->rightChild == NULL)
    {
        deleteBuff = _delete;
    }
    else
    {
        deleteBuff = successor(_delete);
    }

    if(deleteBuff->leftChild != NULL)
    {
        deleteChild = deleteBuff->leftChild;
    }
    else
    {
        deleteChild = deleteBuff->rightChild;
    }

    if(deleteChild != NULL)
    {
        deleteChild->parent = deleteBuff->parent;
    }

    if(deleteBuff->parent == NULL)
    {
        this->root = deleteChild;
    }
    else if(deleteBuff == deleteBuff->parent->leftChild)
    {
        deleteBuff->parent->leftChild = deleteChild;
    }
    else
    {
        deleteBuff->parent->rightChild = deleteChild;
    }
    
    if(deleteBuff != _delete)
    {
        _delete->value = deleteBuff->value;
    }

    delete deleteBuff;
    deleteBuff = NULL;
    cout << "[DELETE SUCCESS]" << endl;
}

void BinaryTree::searchByValue(int value)
{
    TreeNode* node = searchBST(value);
    if(node == NULL)
    {
        throw "No such value.";
    }

    // LeftSize
    int leftSize = 1;
    inOrderQueue.clear();
    inOrderRank(root);
    while(inOrderQueue[leftSize-1] != value)
    {
        leftSize++;
    }

    // Depth
    int depthRoot = searchByValueDepth(root);
    int depthNode = searchByValueDepth(node);
    int depth = depthRoot - depthNode;
    cout << "LeftSize = " << leftSize << ", Depth = " << depth+1 << endl;
}

int BinaryTree::searchByValueDepth(TreeNode *node)
{
    if(node == NULL) return 0;
    int leftDepth = searchByValueDepth(node->leftChild);  
    int rightDepth = searchByValueDepth(node->rightChild);  
    return max(leftDepth, rightDepth)+1;
}

void BinaryTree::searchByRank(int value)
{
    if(value > nodeCount)
    {
        throw "No such value.";
    }

    inOrderQueue.clear();
    inOrderRank(root);
    cout << "The " << value << "th smallest is " << inOrderQueue[value-1] << endl;
}

void BinaryTree::showInorder()
{
    inOrder(root);
    cout << endl;
}

// LVR
void BinaryTree::inOrder(TreeNode *current)
{
    if(current != NULL)
    {
        inOrder(current->leftChild);
        cout << current->value << " ";
        inOrder(current->rightChild);
    }
}

void BinaryTree::inOrderRank(TreeNode *current)
{
    if(current != NULL)
    {
        inOrderRank(current->leftChild);
        inOrderQueue.push_back(current->value);
        inOrderRank(current->rightChild);
    }
}

void BinaryTree::showPreorder()
{
    preOrder(root);
    cout << endl;
}

// VLR
void BinaryTree::preOrder(TreeNode *current)
{
    if(current != NULL)
    {
        cout << current->value << " ";
        preOrder(current->leftChild);
        preOrder(current->rightChild);
    }
}

void BinaryTree::showPostorder()
{
    postOrder(root);
    cout << endl;
}

// LRV
void BinaryTree::postOrder(TreeNode *current)
{
    if(current != NULL)
    {
        postOrder(current->leftChild);
        postOrder(current->rightChild);
        cout << current->value << " ";
    }
}