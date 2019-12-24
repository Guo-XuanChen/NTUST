/*
    File      : main.cpp
    Time      : 2019/12/24 13:37:01
    Author    : Guo-XuanChen
*/

#include <iostream> 
#include <string>
#include <vector>

using namespace std; 
  
class AVLNode  
{  
    public: 
    int key;  
    AVLNode *left;  
    AVLNode *right;  
    int depth;  
};  

vector<int> output;
  
int max(int a, int b){
    return (a > b) ? a : b;
}  
  
int depth(AVLNode *n)  
{  
    return (n == NULL) ? 0 : n->depth;
}  


AVLNode* newNode(int key)  
{  
    AVLNode* node = new AVLNode(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->depth = 1;
    return(node);  
}  

AVLNode* rightRotate(AVLNode *y)  
{  
    AVLNode *x = y->left;  
    AVLNode *T2 = x->right;  
  
    x->right = y;  
    y->left = T2;  
  
    y->depth = max(depth(y->left), depth(y->right)) + 1;  
    x->depth = max(depth(x->left), depth(x->right)) + 1;  

    return x;  
}  
  
AVLNode* leftRotate(AVLNode *x)  
{   
    AVLNode *y = x->right;  
    AVLNode *T2 = y->left;  
  
    y->left = x;  
    x->right = T2;  

    x->depth = max(depth(x->left), depth(x->right)) + 1;  
    y->depth = max(depth(y->left), depth(y->right)) + 1;  

    return y;  
}  
  
int getBalance(AVLNode *N)  
{  
    return (N == NULL) ? 0 : depth(N->left) - depth(N->right);
}    

AVLNode* insert(AVLNode* node, int key)  
{  

    if(node == NULL)  
    {
        return(newNode(key)); 
    }
         
    if(key < node->key) 
    {
        node->left = insert(node->left, key);
    }          
    else if(key > node->key)  
    {
        node->right = insert(node->right, key);  
    }
    else
    {
        return node; 
    }
         
    node->depth = 1 + max(depth(node->left),  depth(node->right));  
  
    int balance = getBalance(node);       
  
    // Left Left Case  
    if(balance > 1 && key < node->left->key) 
    {
        return rightRotate(node);  
    } 
        
    // Right Right Case  
    if(balance < -1 && key > node->right->key)  
    {
        return leftRotate(node);  
    }
        
    // Left Right Case  
    if(balance > 1 && key > node->left->key)  
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if(balance < -1 && key < node->right->key)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
    return node;  
}  
  
AVLNode* minValueNode(AVLNode* node)  
{  
    AVLNode* current = node;  

    while(current->left != NULL)  
    {
        current = current->left;  
    }
    return current;  
}  

AVLNode* maxValueNode(AVLNode *node)
{
    AVLNode* current = node;

    while(current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

AVLNode* deleteNode(AVLNode* root, int key)  
{  
    if (root == NULL)  
    {
        return root;  
    }

    if(key < root->key)  
    {
        root->left = deleteNode(root->left, key);  
    }
    else if(key > root->key)  
    {
        root->right = deleteNode(root->right, key);  
    }
    else
    {  
        if((root->left == NULL) || (root->right == NULL))  
        {  
            AVLNode *temp = root->left ? root->left :  root->right;  
  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else  
            {
                *root = *temp;   
            }
            free(temp);  
        }  
        else
        {  
            AVLNode* temp = maxValueNode(root->left);  

            root->key = temp->key;  

            root->left = deleteNode(root->left, temp->key);  
        }  
    }  
  
    if (root == NULL)  
    {
        return root;  
    }
    
    // update depth  
    root->depth = 1 + max(depth(root->left), depth(root->right));  
  
    // get balance factor 
    int balance = getBalance(root);  
  
    //rotate the tree if unbalanced
  
    // Left Left Case  
    if (balance > 1 && getBalance(root->left) >= 0)  
    {
        return rightRotate(root);  
    }

    // Left Right Case  
    if(balance > 1 &&  getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
    // Right Right Case  
    if(balance < -1 &&  getBalance(root->right) <= 0) 
    { 
        return leftRotate(root);  
    }

    // Right Left Case  
    if(balance < -1 && getBalance(root->right) > 0)
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
    return root;  
}  


void preOrder(AVLNode *root)  
{  
    if(root != NULL)  
    {  
        output.push_back(root->key);
        preOrder(root->left);
        preOrder(root->right);  
    }  
}  

int main(int argc, char** argv)
{  
    AVLNode *root = NULL;  
  
    string cmd; 
    while(cin >> cmd)
    {
        int value;
        if(cmd == "INSERT")
        {
            cin >> value;
            root = insert(root, value);  
        }
        else if(cmd == "REMOVE")
        {
            cin >> value;
            root = deleteNode(root, value); 
        }
        else if(cmd == "PRINT")
        {
            output.clear();
            preOrder(root);  
            for(unsigned int x = 0; x < output.size() - 1; x++)
            {
                cout << output[x] << ",";
            }
            cout << output[output.size() - 1] << endl;
        }
    }  
    return 0;  
}  