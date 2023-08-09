/*jpt*/
#include<iostream>
struct link{
int value;
int *pointer;
};
int main(){
    int i;
    link n[5];
    //input
    for(i=0;i<5;i++){
        std::std::cin>>n[i].value;
        n[i-1].pointer=&n[i].value;
    }
    //print
    i=0;
    while(i<4){
        std::cout<<*n[i].pointer;
        i++;
    }
}