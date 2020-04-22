
#ifndef _FamilyTree_
#define _FamilyTree_
#include <iostream>
#include <string>

using namespace std;
class node {

public:
    string name;
    string sex;
    string relation;
    int height;
    node *father;
    node *mother;

    node(string _name)
    { // Constructor with parameters
        this->name = _name;
        this->height=0;
        this->relation="";
        this->father = this->mother = nullptr;
    }
    ~node(){
        delete this->father;
        delete this->mother;


    }
//    node* findNode(string son,node *node);
};


namespace family
{



    class Tree{

    public:
        node *head;
        //Constractur

//Constractor
        Tree(string _name)
        {
            this->head = new node(_name);

        }



        Tree& addFather(string son, string father);
        Tree& addMother(string son, string mather);
        void display();

        string relation(string ancestor);
        string find(string nameOfFind);
        bool remove(string ancestor);

        void deleteSubTree(node *pNode);
    }; // class Tree
}// namespace family
#endif