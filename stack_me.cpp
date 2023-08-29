#include<iostream>
using namespace std;
struct node{
    int value;
    node *ptr;
};
void push(node *&top,int value=999999999){
    node *nptr = new node;
    if(value==999999999){
        cout<<"value=";
        cin>>nptr->value;
    }
    else{
        nptr->value=value;
    }
    nptr->ptr=nullptr;
    if(top==nullptr){
        top=nptr;
    }
    else{
        nptr->ptr=top;
        top=nptr;
    }
}
void pop(node *&top){
    node *eptr = top;
    if(top==nullptr){
        cout<<"\nEMPTY STACK CANT POP\n";
        return;
    }
    if(top->ptr!=nullptr){
        top=top->ptr;
    }
    else{
        top=nullptr;
    }
    delete eptr;
}
void display(node *&top){
    node *tmptr=top;
    if(top==nullptr){
        cout<<"\nEMPTY STACK CANT DISPLAY\n";
        return;
    }
    while(tmptr!=nullptr){
        cout<<tmptr->value<<" ";
        tmptr=tmptr->ptr;
    }
}
void search(node *&top){
    node *tmptr=top;
    int i=0,num;
    if(top==nullptr){
        cout<<"\nEMPTY STACK CANT SEARCH\n";
        return;
    }
    cout<<"num=";
    cin>>num;
    while(tmptr!=nullptr){
        if(tmptr->value==num){
            cout<<"\nnum "<<num<<" found "<<i<<" steps from top\n";
            return;
        }
        tmptr=tmptr->ptr;
        i++;
    }
    cout<<"\nnum wasnt present on stack\n";
}
void insert(node *&top){
    int pos,i,count=0,value;
    node *tmptr=top;
    node *top2=nullptr;
    cout<<"position from top = ";
    cin>>pos;
    while(tmptr!=nullptr){
        count++;
        tmptr=tmptr->ptr;
    }
    if(pos>count-1 || pos<0){
        cout<<"\nOUT OF RANGE\n";
        return;
    }
    tmptr=top;
    for(int i=0;i<pos;i++){
        push(top2,tmptr->value);
        tmptr=tmptr->ptr;
    }
    cout<<"Data before pos pushed to stack 2\n";
    for(int i=0;i<pos;i++){
        pop(top);
    }
    cout<<"Popped data before pos from stack 1\n";
    cout<<"value to insert =";
    cin>>value;
    push(top2,value);
    cout<<"pushed new data to stack 2\n";
    node *tmptr2=top2;
    while(tmptr2!=nullptr){
        push(top,tmptr2->value);
        tmptr2=tmptr2->ptr;
    }
    cout<<"Pushed all data of stack 2 to stack 1\n";
    for(int i=0;i<pos+1;i++){
        pop(top2);
    }
    cout<<"Deleted all data of stack 2\n";
}
int main(){
    node *top=nullptr;
    int choice,n;
    cout<<"no of members to initalize stack=";
    cin>>n;
    for(int i=0;i<n;i++){
        push(top);
    }
    do{
        cout<<"\t\tchoose one of the following options\n";
        cout<<"1.push\n";
        cout<<"2.pop\n";
        cout<<"3.display\n";
        cout<<"4.search\n";
        cout<<"5.exit\n";
        cout<<"6.INSERT AT BETWEEN USING 2 STACK\n";
        cout<<"choice:-";
        cin>>choice;
        switch(choice){
            case 1:
            push(top);
            break;
            
            case 2:
            pop(top);
            break;

            case 3:
            display(top);
            break;

            case 4:
            search(top);
            break;

            case 5:
            cout<<"\nEXITING\n";
            break;

            case 6:
            insert(top);
            break;

            default:
            cout<<"ERROR";
        }
    }while(choice!=5);
    return 0;
}