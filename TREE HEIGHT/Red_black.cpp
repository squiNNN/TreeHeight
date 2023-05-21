#include <bits/stdc++.h>
#define SPACE 10
using namespace std;

bool sta;

class Node{
    public:
    double data;
    Node* left;
    Node* right;
    Node* parent;
    bool color; //1 is red and 0 is black

    Node(double data, bool color){
        this->data = data;
        this->color = color;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

class RBTree{
    public:
    Node *root;
    Node *nil = new Node(-1, false);
    RBTree(){
        root = NULL;
    }

    void insertBST(double);
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void fixInsertViolation(Node*);
    int getHeight(Node*);

    void print2D(Node * r, int space, ofstream& ou) {
    if (r == NULL) // Base case  1
      return;
    space += SPACE; // Increase distance between levels   2
    print2D(r -> right, space, ou); // Process right child first 3 
    ou << endl;
    for (int i = SPACE; i < space; i++) // 5 
      ou << " "; // 5.1  
    ou << r -> data << "(" << r->color << ")" <<"\n"; // 6  
    print2D(r -> left, space, ou); // Process left child  7
  }
};

void RBTree::insertBST(double value){
    Node* newnode = new Node(value, true);
    newnode->left = nil;
    newnode->right = nil;

    if(root == NULL){
        root = newnode;
        newnode->color = false;
        //return newnode;
        return;
    }

    Node* temp = root;

    while(true){
        if(value < temp->data){
            if(temp->left == nil){
                temp->left = newnode;
                newnode->parent = temp;
                //return newnode; 
                break;
            }
            else
                temp = temp->left;
        }
        else if(value > temp->data){
            if(temp->right == nil){
                temp->right = newnode;
                newnode->parent = temp;
                //return newnode;
                break;
            }
            else 
                temp = temp->right;
        }
        else return;
    }

    fixInsertViolation(newnode);
}

void RBTree::rotateLeft(Node* node){
    Node* node2 = node->right;

    node->right = node2->left;
    if(node2->left != nil)
        node2->left->parent = node;
    
    node2->parent = node->parent;
    if (node->parent == NULL)
        this->root = node2;
    else if(node == node->parent->left)
        node->parent->left = node2;
    else
        node->parent->right = node2;
    
    node2->left = node;
    node->parent = node2;
    //cout << "left at " << node->data;
}

void RBTree::rotateRight(Node* node){
    Node* node2 = node->left;
    
    node->left = node2->right;

    if(node2->right != nil)
        node2->right->parent = node;
    node2->parent = node->parent;
    if (node->parent == NULL)
        this->root = node2;
    else if (node == node->parent->left)
        node->parent->left = node2;
    else 
        node->parent->right = node2;

    node2->right = node;
    node->parent = node2;
    //cout << "Right at " << node->data;
}

void RBTree::fixInsertViolation(Node* fixNode){
    if(fixNode->parent == NULL){
        fixNode->color = false;
        return;
    }
    if (fixNode->parent->color == false){
        return;
    }

    if(fixNode->parent->parent->left->color && fixNode->parent->parent->right->color){
        fixNode->parent->parent->left->color = false;
        fixNode->parent->parent->right->color = false;
        fixNode->parent->parent->color = true;
        fixInsertViolation(fixNode->parent->parent);
        return;
    }

    if(fixNode->parent->parent->left == fixNode->parent && fixNode->parent->right == fixNode){
        rotateLeft(fixNode->parent);
        fixNode = fixNode->left;
    }
    else if(fixNode->parent->parent->right == fixNode->parent && fixNode->parent->left == fixNode){
        rotateRight(fixNode->parent);
        fixNode  = fixNode->right;
    }

    fixNode->parent->color = false;
    fixNode->parent->parent->color = true;

    if(fixNode->parent->parent->left == fixNode->parent && fixNode->parent->left == fixNode)
        rotateRight(fixNode->parent->parent);
    else if (fixNode->parent->parent->right == fixNode->parent && fixNode->parent->right == fixNode)
        rotateLeft(fixNode->parent->parent);
}

int RBTree::getHeight(Node* r){
    if(r == NULL)
        return -1;
    else
        return 1 + max(getHeight(r->left), getHeight(r->right));
}


int main(){
    string filename[] = {"Test01.txt","Test02.txt",\
    "Test03.txt","Test04.txt","Test05.txt","Test06.txt",\
    "Test07.txt","Test08.txt","Test09.txt","Test10.txt"};

    ofstream clearfile("RBHeight.txt");
    clearfile << "";
    clearfile.close();

    ofstream write("RBHeight.txt", ios::app);
     
    for (int i = 0; i < 10; i++){
        RBTree Tree;
        ifstream read(filename[i]); 
        double te;
        for (int j = 0; j < 1e6; j++){  
            read >> te;
            Tree.insertBST(te);     
        }
        write << Tree.getHeight(Tree.root) << '\n';
    }

}