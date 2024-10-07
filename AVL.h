#include <iostream>
#include <sstream>
#include <regex>
#include <queue>
using namespace std;

struct Node{
    Node* left;
    Node* right;
    int height;
    string ufid;
    string name;

    Node(string name, string ufid){
        this->name = name;
        this->ufid = ufid;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVL{
private:
    bool removeCalled = false;
    Node* root = nullptr;
    Node* leftRotation(Node* n);
    Node* rightRotation(Node* n);
    Node* leftRightRotation(Node* n);
    Node* rightLeftRotation(Node* n);
    Node* insertHelper(Node* helpRoot, string name, string ufid);
    Node* removeIDHelper(Node* node, string key);
    bool searchNameHelper(Node* node, string key);
    Node* searchIDHelper(Node* node, int key);
    vector<Node*> inOrderHelper(Node* node, vector <Node*>& output);
    vector<Node*> preOrderHelper(Node* node,vector <Node*>& output);
    vector<Node*> postOrderHelper(Node* node, vector <Node*>& output);
    int getHeight(Node* node);
    int getMaxHeightHelper(Node* node);


    void destructorHelper(Node* node);
public:

    vector<string> namesFound;
    void insertNameID(string name, string ufid);
    void removeID(string ufid);
    void search(string input);
    void searchName(string key);
    void searchID(int key);
    void printInOrder();
    void printPreorder();
    void printPostOrder();
    void printLevelCount();
    void removeInorderN(string n);

    ~AVL(){
        //postorder transversal,deleting nodes
        destructorHelper(root);
    }
};