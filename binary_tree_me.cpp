#include<iostream>
#include<conio.h>
using namespace std;
struct node{
    int value;
    node *parent_ptr;
    node *child_ptrs[2];
    public:
    node(){
        parent_ptr = nullptr;
        for(int i=0;i<2;i++){
            child_ptrs[i] = nullptr;
        }
        cout<<"enter value = ";
        cin>>value;
    }
};
node *root=nullptr;
void add_child(node *&working,bool replace = false){
    node *nptr = new node;
    if(working == nullptr || replace){
        if(replace){
            delete working;
            working = nullptr;
        }
        root = working = nptr;
    }
    else{
        aa:
        cout<<"1.left = ";
        (working->child_ptrs[0]==nullptr)?cout<<"Empty":cout<<"full";
        cout<<endl;
        cout<<"2.right = ";
        (working->child_ptrs[1]==nullptr)?cout<<"Empty":cout<<"full";
        cout<<endl;
        cout<<"where do you want to fill :- ";
        int choice;
        cin>>choice;
        switch(choice){
            case 1:working->child_ptrs[0] = nptr;working->child_ptrs[0]->parent_ptr=working;break;
            case 2:working->child_ptrs[1] = nptr;working->child_ptrs[1]->parent_ptr=working;break;
            default:
            cout<<"ERROR"<<endl;
            goto aa;
        }
    }
}
void jump_child(node *&working){
    aa:
    int choice;
    cout<<"1.To Parent"<<endl;
    cout<<"2.To Child"<<endl;
    cout<<"choice = ";
    cin>>choice;
    if(choice == 1){
        if(working->parent_ptr == nullptr){
            cout<<"YOU ARE IN ROOT NODE"<<endl;
            return;
        }
        working = working->parent_ptr;
    }
    else if(choice == 2){
        cout<<"1.left = ";
        (working->child_ptrs[0]==nullptr)?cout<<"Empty":cout<<working->child_ptrs[0]->value;
        cout<<endl;
        cout<<"2.right = ";
        (working->child_ptrs[1]==nullptr)?cout<<"Empty":cout<<working->child_ptrs[1]->value;
        cout<<endl;
        cout<<"where do you want to jump :- ";
        cin>>choice;
        switch(choice){
            case 1:
            if(working->child_ptrs[0]==nullptr){
                cout<<"NULL POINTER"<<endl;
                return;
            }
            working = working->child_ptrs[0];
            break;
            case 2:
            if(working->child_ptrs[1]==nullptr){
                cout<<"NULL POINTER"<<endl;
                return;
            }
            working = working->child_ptrs[1];
            break;
            default:
            cout<<"ERROR"<<endl;
            goto aa;
        }
    }
}
void display_childs(node *&working){
    cout<<"\nThis node and its childs:-\n"<<endl;
    cout<<"\t"<<working->value<<endl;
    (working->child_ptrs[0]==nullptr)?cout<<"Empty":cout<<working->child_ptrs[0]->value;
    cout<<"\t\t";
    (working->child_ptrs[1]==nullptr)?cout<<"Empty":cout<<working->child_ptrs[1]->value;
    cout<<endl;
}
void remove_node(node *&working){
    if(working == nullptr){
        cout<<"NO NODES IN TREE"<<endl;
        return;
    }
    if(working->child_ptrs[0] != nullptr){
        delete working->child_ptrs[0];
    }
    if(working->child_ptrs[1] != nullptr){
        delete working->child_ptrs[1];
    }
    node *tmp = working;
    working = working->parent_ptr;
    delete tmp;
}
int main(){
    node *working=nullptr;
    cout<<"root node :- \n";
    add_child(working);
    while(true){
        cout << "\x1B[2J\x1B[H";
        int choice;
        cout<<"choose one of following options:-"<<endl;
        cout<<"1.add child"<<endl;
        cout<<"2.remove node"<<endl;
        cout<<"3.replace node"<<endl;
        cout<<"4.Jump"<<endl;
        cout<<"5.display childs"<<endl;
        cout<<"6.exit"<<endl;
        cout<<"choice = ";
        cin>>choice;
        switch(choice){
            case 1:
            add_child(working);
            break;
            case 2:
            remove_node(working);
            break;
            case 3:
            add_child(working,true);
            break;
            case 4:
            jump_child(working);
            break;
            case 5:
            display_childs(working);
            break;
            case 6:
            return 0;
            break;
            default:
            cout<<"INVALID INPUT"<<endl;
        }
        getch();
    }
}