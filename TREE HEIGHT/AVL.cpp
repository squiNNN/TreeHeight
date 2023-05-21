#include <bits/stdc++.h>
#define SPACE 10
using namespace std;

class Node{
    public:
    double data;
    Node* left;
    Node* right;
    int height;
    Node(double data){
        this->data = data;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

class AVLTree{
    public:
    Node* root;

    AVLTree();
    int getHeight(Node*);
    int getBalanceFactor(Node*);
    Node* rotateLeft(Node*);
    Node* rotateRight(Node*);
    Node* insert(Node*, Node*);

    void print2D(Node * r, int space, ofstream& ou) {
    if (r == NULL) // Base case  1
      return;
    space += SPACE; // Increase distance between levels   2
    print2D(r -> right, space, ou); // Process right child first 3 
    ou << endl;
    for (int i = SPACE; i < space; i++) // 5 
      ou << " "; // 5.1  
    ou << r -> data << "\n"; // 6  
    print2D(r -> left, space, ou); // Process left child  7
  }
};

AVLTree::AVLTree(){
    root = nullptr;
}

int AVLTree::getHeight(Node* r) {
	if (r == NULL)
		return -1;
	return r->height;
}


int AVLTree::getBalanceFactor(Node* r){
    return getHeight(r->left) - getHeight(r->right);
}

Node* AVLTree::rotateLeft(Node* node){
    Node* node2 = node->right;

    node->right = node2->left;
    node2->left = node;
    
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    node2->height = max(getHeight(node2->left), getHeight(node2->right)) + 1;

    return node2;
}

Node* AVLTree::rotateRight(Node* node){
    Node* node2 = node->left;
    
    node->left = node2->right;
    node2->right = node;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    node2->height = max(getHeight(node2->left), getHeight(node2->right)) + 1;

    return node2;
}


Node* AVLTree::insert(Node* r, Node* newnode){
    
    if (r == NULL){
        return newnode;
    }
    if (newnode->data < r->data){
        r->left = insert(r->left, newnode);
    }
    else if (newnode->data > r->data){
        r->right = insert(r->right, newnode);
    }
    else if (newnode->data == r->data){
        return r;
    }

    
    r->height = 1 + max(getHeight(r->left), getHeight(r->right));
    int balance = getBalanceFactor(r);
    
    if (balance < -1 && newnode->data > r->right->data){
        return rotateLeft(r); 
    }

    if (balance > 1 && newnode->data < r->left->data){
        return rotateRight(r);
    }

    if (balance < -1 && newnode->data < r->right->data){
        r->right = rotateRight(r->right);
        return rotateLeft(r);
    }

    if (balance > 1 && newnode->data > r->left->data){
        r->left = rotateLeft(r->left);
        return rotateRight(r);
    }
    return r;
    
}

int main(){
    string filename[] = {"Test01.txt","Test02.txt",\
    "Test03.txt","Test04.txt","Test05.txt","Test06.txt",\
    "Test07.txt","Test08.txt","Test09.txt","Test10.txt"};

    ofstream clearfile("AVLHeight.txt");
    clearfile << "";
    clearfile.close();

    ofstream write("AVLHeight.txt", ios::app);
     
    for (int i = 0; i < 10; i++){
        set<double> c;
        AVLTree Tree;
        ifstream read(filename[i]); 
        double te;
        for (int j = 0; j < 1e6; j++){  
            read >> te;
            Node* newnode = new Node(te);
            Tree.root = Tree.insert(Tree.root, newnode);
        }
        
        write << Tree.getHeight(Tree.root) << '\n';
    }

}

