#include "AVL.h"


//HELPER FUNCTIONS
bool isInt(string i){
    for (char c: i)
        if(!isdigit(c))
            return false;
    return true;
}
bool isName(string word){
    if(word.length()<1 || word.length()>1000)
        return false;
    for (char c: word) {
        if (!isalpha(c) && c != ' ')
            return false;
    }
    return true;
}
bool isID(string id){
    if(id.length()!=8 || !isInt(id))
        return false;
    return true;
}


int isBalanced(Node* curr){
    if(curr== nullptr)
        return 0;
    int left_height;
    int right_height;

    if(curr->left == nullptr)
        left_height=0;
    else
        left_height= curr->left->height;
    if(curr->right == nullptr)
        right_height=0;
    else
        right_height = curr->right->height;
    return left_height-right_height;
}

int AVL::getHeight(Node *node) {
    return 1+std::max(node->left==nullptr? 0:node->left->height, node->right==nullptr? 0:node->right->height);;
}
//Stepik 4.1 n-ary solution inspired ( vid: Stepik M5 part One)
int AVL::getMaxHeightHelper(Node *node) {
    if(node== nullptr)
        return 0;
    return 1+max(getMaxHeightHelper(node->left), getMaxHeightHelper(node->right));

}

//Rotations
Node* AVL::leftRotation(Node* n){
    Node* rightNode = n->right;
    Node* temp = rightNode->left;
    rightNode->left=n;
    n->right= temp;
    n->height = getMaxHeightHelper(n);
    rightNode->height = getHeight(rightNode);
    //rightNode->height = 1+std::max(rightNode->left==nullptr? 0:rightNode->left->height, rightNode->right==nullptr? 0:rightNode->right->height);
    return rightNode;
}
Node* AVL::rightRotation(Node* n){
    Node* leftNode = n->left;
    Node* temp = leftNode->right;
    leftNode->right = n;
    n->left = temp;
    n->height = getMaxHeightHelper(n);
    leftNode->height = getHeight(leftNode);
    return leftNode;
}
Node *AVL::leftRightRotation(Node *n) {
    n->left= leftRotation(n->left);
    return rightRotation(n);
}
Node *AVL::rightLeftRotation(Node *n) {
    n->right= rightRotation(n->right);
    return leftRotation(n);
}

//Based on EduGator 6.2 Coding Solution
Node* AVL::insertHelper(Node* helpRoot, string name, string ufid){

    if(helpRoot == nullptr) {
        cout<<"successful"<<endl;
        return new Node(name, ufid);
    }
    //move left
    else if(stoi(ufid) < stoi(helpRoot->ufid))
        helpRoot->left = insertHelper(helpRoot->left, name, ufid);
    else if(stoi(ufid) > (stoi(helpRoot->ufid)))
        helpRoot->right = insertHelper(helpRoot->right, name, ufid);
    else {
        cout<<"unsuccessful"<<endl;
        return helpRoot;
    }

    //updating height
    helpRoot->height = getHeight(helpRoot);

//    //Balancing geeks for greeks:  https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    int balance = isBalanced(helpRoot);
    //left-left
    if(balance > 1 && stoi(ufid) < stoi(helpRoot->left->ufid)){
        return rightRotation(helpRoot);
    }
    //right-right
    if(balance < -1 && stoi(ufid)  > stoi(helpRoot->right->ufid)){
        return leftRotation(helpRoot);
    }
    //left right
    if(balance > 1 && stoi(ufid)  > stoi(helpRoot->left->ufid)){
        return leftRightRotation(helpRoot);
    }
    //right left
    if(balance < -1 && stoi(ufid)  < stoi(helpRoot->right->ufid)){
        return rightLeftRotation(helpRoot);
   }
    return helpRoot;
}

//Helper  recursive function that finds the parent of a node (return node*)
//check if it has a child with given id

//Remove Functions
Node *AVL::removeIDHelper(Node* node, string key) {

    if(node== nullptr)
        return node;

    //checking id (in postOrder LRN)
    if(node->ufid > key) {
        node->left = removeIDHelper(node->left, key);
    }
    else if (node->ufid < key) {
        node->right = removeIDHelper(node->right, key);
    }
    else{
        //found node to delete (node has key)
        // no child
        if((node->left == nullptr) && (node->right == nullptr)){
            delete node;
            return nullptr;
        }
        //one child
        else if((node->left == nullptr) || (node->right == nullptr)){
            Node* temp = (node->left != nullptr) ? node->left : node->right;
            delete node;
            return temp;
        }
        //two child
        else if(node->left != nullptr && node->right != nullptr){
            //find the left-most node in right subtree
            //current node (right of node)
            Node* curr = node->right;
            //iterate to find min
            while(curr->left!= nullptr){
                curr = curr->left;
            }
            //curr is now the left/ most node and min
            //attach node left subtree
            node->name = curr->name;
            node->ufid = curr->ufid;
            node->right = removeIDHelper(node->right, curr->ufid);
        }
    }
    return node;
}

//Search Functions
Node*  AVL::searchIDHelper(Node *node, int key)  {
    if(node== nullptr)
        return nullptr;
    if(key == stoi(node->ufid)) {
        //cout<<node->name<<endl;
        return node;
    }
    else if(key < stoi(node->ufid)){
         return searchIDHelper(node->left, key);

    }
    else if(key > stoi(node->ufid)){
        return searchIDHelper(node->right,key);
    }
}
bool AVL::searchNameHelper(Node *node, std::string key) {

    if(node== nullptr)
        return false;
    //name is found
    bool recallBuffer;
    if(key==node->name) {
        cout<<node->ufid<<endl;
        namesFound.push_back(node->ufid);
    }
    if(searchNameHelper(node->left, key))
        recallBuffer =!recallBuffer;
    if(searchNameHelper(node->right, key))
        recallBuffer =!recallBuffer;

    if(!namesFound.empty())
        return true;
    else
        return false;
}

//Inspired by AMAN BST Helper Code (helperInorder)
vector<Node*> AVL::inOrderHelper(Node *node, vector <Node*>& output) {
    //if node doesn't exist
    if(node == nullptr)
        return output;
    //LNR
    inOrderHelper(node->left, output);
    output.push_back(node);
    inOrderHelper(node->right, output);
    //output
    return output;
}
vector<Node*> AVL::preOrderHelper(Node *node, vector <Node*>& output ) {
    //if node doesn't exist
    if(node == nullptr)
        return output;
    //NLR
    output.push_back(node);
    preOrderHelper(node->left, output);
    preOrderHelper(node->right, output);

    return output;
}
vector<Node*> AVL::postOrderHelper(Node *node, vector <Node*>& output) {
    if(node== nullptr)
        return output;
    //LRN
    postOrderHelper(node->left, output);
    postOrderHelper(node->right, output);
    output.push_back(node);

    return output;

}


//MAIN FUNCTIONS
void AVL::insertNameID(string name, string id) {
    //verifies input
    if(!isName(name) || !isID(id)){
        cout<<"unsuccessful"<<endl;
        return;
    }
    //Insert Node
    this->root = insertHelper(this->root, name, id);
}

void AVL::removeID(string ufid) {
    //call search(ufid)
    //transverse recursively through tree to reach desired node to delete
    //if(ufid<root->ufid) root->left = remove(root->left, id); //from Project Breakdown Slide 15
    //3 Scenarios: no child, 1 child, 2 child
    if(!isID(ufid)){
        cout<<"unsuccessful"<<endl;
        return;
    }
    //if id not found: print unsuccessful
    if(!searchIDHelper(this->root, stoi(ufid)))
        cout<<"unsuccessful"<<endl;
    else {
        this->root = removeIDHelper(this->root, ufid);
        cout<<"successful"<<endl;
    }
}

void AVL::search(std::string input) {
    if(isName(input))
        searchName(input);
    else if(isID(input))
        searchID(stoi(input));
    else
        cout<<"unsuccessful"<<endl;
}
void AVL::searchName(string key) {
    if(!isName(key)){
        cout<<"unsuccessful"<<endl;
        return;
    }
    if(this->root== nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }
    if(!searchNameHelper(this->root, key)){
        cout<<"unsuccessful"<<endl;
    }
}
void AVL::searchID(int key) {
    if(this->root== nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }
    Node* foundNode = searchIDHelper(this->root, key);
    if(foundNode == nullptr)
        cout<<"unsuccessful"<<endl;
    else
        cout<<foundNode->name<<endl;
}

//prints
void AVL::printInOrder() {
    //if empty tree
    if(this->root== nullptr){
        cout<<"unsuccessful"<<endl;
        return;
    }
    vector<Node*> output;
    output = inOrderHelper(this->root, output);
    for(int i =0; i<output.size(); i++){
        cout<<output[i]->name;
        if(i<output.size()-1)
            cout<<", ";
    }
    cout<<endl;
}
void AVL::printPreorder() {
    //if empty tree
    if(this->root== nullptr){
        cout<<"unsuccessful"<<endl;
        return;
    }
    vector<Node*> output;
    output = preOrderHelper(this->root, output);
    //print names
    for(int i =0; i<output.size(); i++){
        cout<<output[i]->name;
        if(i<output.size()-1)
            cout<<", ";
    }
    cout<<endl;
}
void AVL::printPostOrder() {
    //if empty tree
    if(this->root== nullptr){
        cout<<"unsuccessful"<<endl;
        return;
    }
    vector<Node*> output;
    output = postOrderHelper(this->root, output);
    for(int i =0; i<output.size(); i++){
        cout<<output[i]->name;
        if(i<output.size()-1)
            cout<<", ";
    }
    cout<<endl;
}
void AVL::printLevelCount() {
    //transverse inorder (recursively)
    cout << getMaxHeightHelper(this->root) << endl;
}

void AVL::removeInorderN(string num) {
    if(!isInt(num)){
        cout << "unsuccessful" << endl;
        return;
    }
    int n = stoi(num);
    //iterating through in order
    Node* foundNode;
    vector <Node*> output;
    //gets vectors of nodes inOrder
    output = inOrderHelper(this->root, output);
    //if n is out of bounds
    if(n>=output.size())
        return;
    //
    foundNode = output[n];
    if(foundNode== nullptr){
        cout<<"unsuccessful"<<endl;
        return;
    }
    //remove node
    removeID(foundNode->ufid);
}

//Destructor Helper - Post Order Destructor
void AVL::destructorHelper(Node *node){
    if(node== nullptr)
        return;
    else{
        destructorHelper(node->left);
        destructorHelper(node->right);
        delete node;
    }
}
