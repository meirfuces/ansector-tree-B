#include "FamilyTree.hpp"
#define COUNT 10
using namespace family;
using namespace std;

void print2DUtil(node *root, int space);
string relationFunc(string ancestor, node *runner,string ans);
node* search(string son, node* runner);
//change


///Help Function

 node* findNode(string son, node *head){

    if (head==nullptr) return nullptr; //Here Need To Change
    if (head->name==son)
        return head;
    //fother

    head= findNode(son, head->father);
     if (head->name==son)
         return head;
    //mother
     head =   findNode(son, head->mother);
return head;
 }

Tree& Tree::addMother(string son, string mother)
{
    node *node_find = search(son, this->head);

    if (node_find==nullptr)
        throw out_of_range(son+" dosn't exist");
    if(node_find->mother != nullptr)
        throw runtime_error(son+" already has a mother");
        node_find->mother = new node (mother);
    node_find->mother->sex="f";
    if (node_find->relation=="")
        node_find->mother->relation= "mother";
    else if (node_find->relation=="mother" || node_find->relation=="father")
        node_find->mother->relation= "grandmother";
     // else - grandmother or grandfather
     else {
       string ans  = "great-" + node_find->relation ;

        node_find->mother->relation = ans;
    }
    return *this;
}

Tree& Tree::addFather(string son, string father){
//Tree n;
    node* node_find = search(son, this->head);
    if (node_find==nullptr)
        throw out_of_range(son+" dosn't exist");
    if(node_find->father != nullptr)
        throw runtime_error(son+" already has a father");
    node_find->father = new node (father);

    node_find->father->sex="m";
    if (node_find->relation=="")
        node_find->father->relation= "father";
    else if (node_find->relation=="mother" || node_find->relation=="father")
        node_find->father->relation= "grandfather";
        // else - grandmother or grandfather
    else {
        string ans  = "great-" + node_find->relation ;

        node_find->father->relation = ans;
    }


    return *this;
}

void Tree::display(){
    print2DUtil(this->head, 0);

}


//Help function From "https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/"
void print2DUtil(node *runner, int space)
{
    // Base case
    if (runner == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(runner->father, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<runner->name<<"\n";

    // Process left child
    print2DUtil(runner->mother, space);
}

node* search(string son, node* runner){
    if(runner != nullptr){
        if(runner->name==son){
            return runner;
        } else {
            node* foundNode = search(son, runner->father);
            if(foundNode == nullptr) {
                foundNode = search(son, runner->mother);
            }
            return foundNode;
        }
    } else {
        return nullptr;
    }
}




string Tree::relation(string ancestor) {
    if (ancestor == this->head->name) return "me";
    node *temp = search(ancestor, this->head);
    if (temp == nullptr) return "unrelated";
    string ans = temp->relation;
    return ans;
}

node* searchFind(string findRel, node* runner){
    if(runner != nullptr){
        if(runner->relation==findRel){
            return runner;
        } else {
            node* foundNode = searchFind(findRel, runner->father);
            if(foundNode == nullptr) {
                foundNode = searchFind(findRel, runner->mother);
            }
            return foundNode;
        }
    } else {
        return nullptr;
    }
}



string Tree::find(string findName){
    node *temp = searchFind(findName, this->head);
    if (temp == nullptr)
        throw out_of_range("false");
    string ans = temp->name;
    return ans;

}


bool Tree::remove(string ancestor){
    node* temp =  search(ancestor, this->head);
    if (temp== nullptr) throw out_of_range("the name is no in the tree");
    deleteSubTree (temp->mother);
    deleteSubTree (temp->father);
   temp->father= nullptr;
    temp->mother= nullptr;

    delete temp;
    return true;
}

void Tree::deleteSubTree(node *pNode) {
if (pNode== nullptr) return;
     if (pNode->father!= nullptr)
    deleteSubTree(pNode->father);
if(pNode->mother!= nullptr)
    deleteSubTree(pNode->mother);
    delete pNode;

}
