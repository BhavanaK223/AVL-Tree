#include <iostream>
#include <regex>
#include "AVL.h"
using namespace std;

//Verifying inputs


int main(){
    string numCommands;
    getline(cin, numCommands);

    //Input Variables
    string line; //take entire line
    string command; //function call
    string junk; //spaces, " (everything don't need!)
    string name; //name of student
    string junk2; //second junk
    string id; //ufid

    AVL tree;

    for (int i = 0; i < stoi(numCommands); i++){
        //reset variables
        command = "";
        junk = "";
        name = "";
        junk2 = "";
        id = "";

        //get variables
        getline(cin, line);
        istringstream inStream(line);
        getline(inStream, command, ' ');
        getline(inStream, junk, '"');
        getline(inStream, name, '"');
        getline(inStream, junk2, ' ');
        getline(inStream, id);

        //TEST PRINTS
//        cout<<line<<endl;
//        cout<<command<<endl;
//        cout<<name<<endl;
//        cout<<id<<endl;
//        cout<<id.size()<<endl;


        if(!command.compare("insert")){
            tree.insertNameID(name, id);
        }
        else if(!command.compare("remove")){
            //key is stored in junk
            tree.removeID(junk);
        }
        else if(!command.compare("search")){
            //name search
            if(junk.empty())
                tree.search(name);
            //ID search
            if(name.empty())
                tree.search(junk);
        }
        else if(!command.compare("printInorder")){
            tree.printInOrder();
        }
        else if(!command.compare("printPreorder")){
            tree.printPreorder();

        }
        else if(!command.compare("printPostorder")){
            tree.printPostOrder();
        }
        else if(!command.compare("printLevelCount")){
            tree.printLevelCount();

        }
        else if(!command.compare("removeInorder")){
            tree.removeInorderN(junk);
        }
        else{
            cout<<"unsuccessful"<<endl;
        }
    }

	return 0;
}
