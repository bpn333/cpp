#include<iostream>
struct node
{
    int item;
    node *ptr;
};
node *hptr=nullptr,*tmptr=nullptr;
void create_node(){
    node *nptr = new node;
    nptr->ptr = nullptr;
    std::cout<<"value=";
    std::cin>>nptr->item;
    if(hptr==nullptr){
        hptr=tmptr=nptr;
    }
    else{
        tmptr->ptr=nptr;
        tmptr=nptr;
    }
}
void display(){
    node *tmp = hptr;
    while(tmp!=nullptr){
        std::cout<<tmp->item<<" ";
        tmp=tmp->ptr;
    }
}
int main(){
    for(int i=0;i<5;i++){
        create_node();
    }
    display();
}