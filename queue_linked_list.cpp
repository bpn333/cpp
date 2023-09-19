#include<iostream>
#include<vector>
#include<conio.h>
using namespace std;
struct node{
    int value;
    node* ptr;
};
void display(node* &front,node* &rear){
    if(front == nullptr || rear == nullptr){
        cout<<"EMPTY"<<endl;
        return;
    }
    node *tmp = front;
    while(tmp != nullptr){
        cout<<tmp->value<<"\t";
        tmp=tmp->ptr;
    }
    cout<<endl;
}
node* create_node(node* &rear){
    node *nptr = new node;
    nptr->ptr = nullptr;
    cout<<"Element = ";
    cin>>nptr->value;
    if(rear != nullptr){
        rear->ptr = nptr;
    }
    return nptr;
}
void enqueue(node* &front,node* &rear){
    if(front==nullptr && rear ==nullptr){
        front = rear = create_node(rear);
    }
    else{
        rear = create_node(rear);
    }
}
void dequeue(node* &front,node* &rear){
    if(front==nullptr && rear==nullptr){
        cout<<"NO ELEMENT TO DEQUEUE"<<endl;
        return;
    }
    if(rear == front){
        rear = nullptr;
    }
    node* tmp = front;
    front=front->ptr;
    delete tmp;
}
void count(node* &front,node* &rear){
    int count = 0;
    if(front == nullptr || rear == nullptr){
        cout<<"YOUR QUEUE IS EMPTY"<<endl;
        return;
    }
    node *tmp = front;
    while(tmp != nullptr){
        count++;
        tmp=tmp->ptr;
    }
    cout<<"YOUR QUEUE CURRENTLY HAS "<<count<<" ELEMENTS"<<endl;
}
int main(){
    node *front=nullptr;
    node *rear=nullptr;
    int choice;
    while(true){
        cout << "\x1B[2J\x1B[H";
        cout<<"\t\tcurrent queue:-\n"<<endl;
        cout<<"\t";
        display(front,rear);
        cout<<"\nChoose One Of Following Operations:-\n";
        cout<<"1.enqueue"<<endl;
        cout<<"2.dequeue"<<endl;
        cout<<"3.count"<<endl;
        cout<<"4.exit"<<endl;
        cout<<"choice = ";
        cin>>choice;
        switch(choice){
            case 1:
            enqueue(front,rear);
            break;
            case 2:
            dequeue(front,rear);
            break;
            case 3:
            count(front,rear);
            break;
            case 4:
            return 0;
            break;
            default:
            cout<<"\nINVALID CHOICE\n";
        }
        getch();
    }
}