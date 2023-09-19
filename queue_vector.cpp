#include<iostream>
#include<vector>
#include<conio.h>
#define MAX 5
using namespace std;
void display(vector<int> &queue,int &front,int &rear){
    if(rear==-1 || front==-1){
        for(int i=0;i<MAX;i++){
            cout<<"x\t";
        }
        cout<<endl;
        return;
    }
    for(int i=0;i<front;i++){
        cout<<"x\t";
    }
    for(int i=front;i<=rear;i++){
        cout<<queue[i]<<"\t";
    }
    for(int i=rear+1;i<MAX;i++){
        cout<<"x\t";
    }
    cout<<endl;
}
void enqueue(vector<int> &queue,int &front,int &rear){
    if(front==-1 && rear ==-1){
        front++;
    }
    if(rear == MAX-1){
        cout<<"Queue Full"<<endl;
        return;
    }
    cout<<"Element = ";
    cin>>queue[++rear];
}
void dequeue(vector<int> &queue,int &front,int &rear){
    if(front==-1 && rear==-1){
        cout<<"NO ELEMENT TO DEQUEUE"<<endl;
        return;
    }
    if(rear == front){
        rear = -1;
        front = -1;
        return;
    }
    front++;
}
void count(vector<int> &queue,int &front,int &rear){
    if(rear == -1 && front == -1){
        cout<<"YOUR QUEUE IS EMPTY"<<endl;
        return;
    }
    cout<<"YOUR QUEUE CURRENTLY HAS "<<(rear - front)+1<<" ELEMENTS"<<endl;
}
int main(){
    vector<int> queue(MAX);
    int front = -1;
    int rear = -1;
    int choice;
    while(true){
        cout << "\x1B[2J\x1B[H";
        cout<<"\t\tcurrent queue:-\n"<<endl;
        cout<<"\t";
        display(queue,front,rear);
        cout<<"\nChoose One Of Following Operations:-\n";
        cout<<"1.enqueue"<<endl;
        cout<<"2.dequeue"<<endl;
        cout<<"3.count"<<endl;
        cout<<"4.exit"<<endl;
        cout<<"choice = ";
        cin>>choice;
        switch(choice){
            case 1:
            enqueue(queue,front,rear);
            break;
            case 2:
            dequeue(queue,front,rear);
            break;
            case 3:
            count(queue,front,rear);
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