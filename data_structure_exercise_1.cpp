#include<iostream>
#include<conio.h>
#include<vector>
using namespace std;

void initialize(std::vector<int> &a);
void display(std::vector<int> &a);
void insert_element(std::vector<int> &a);
void delete_element(std::vector<int> &a);
void search(std::vector<int> &a);

int main(){
    int n,c;
    bool running=1;
    cout<<"number of members:-";
    cin>>n;
    std::vector<int> a(n);
    while(running){
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<"\t\tchoose one of the following options\n1.initialize\n2.insert\n3.delete\n4.display\n5.search\n6.exit\nchoice:-"; 
        cin>>c;
        switch(c){
            case 1:
            initialize(a);
            break;

            case 2:
            insert_element(a);
            cout<<"\nARRAY MODIFIED\n";
            display(a);
            break;

            case 3:
            delete_element(a);
            cout<<"\nARRAY MODIFIED\n";
            display(a);
            break;

            case 4:
            display(a);
            break;

            case 5:
            search(a);
            break;

            case 6:
            running=0;
            break;
        }
    }
    return 0;
}

void initialize(std::vector<int> &a){
    cout<<"\nenter array data:-\n";
    for(int i=0;i<a.size();i++){
        cin>>a[i];
    }
}

void display(std::vector<int> &a){
    cout<<"\narray data:-\n";
    for(int i=0;i<a.size();i++){
    cout<<a[i]<<" ";
    }
    cout<<"\n";
    getch();
}

void insert_element(std::vector<int> &a){
    int i,v;
    display(a);
    input:
    cout<<"\nenter index :-";
    cin>>i;
    if(i<0 || i>a.size()){
        cout<<"ERROR OUT OF RANGE";
        goto input;
    }
    cout<<"value=";
    cin>>v;
    a.insert(a.begin()+i,v);
}

void delete_element(std::vector<int> &a){
    int i;
    display(a);
    input:
    cout<<"\nenter index :-";
    cin>>i;
    if(i<0 || i>=a.size()){
        cout<<"ERROR OUT OF RANGE";
        goto input;
    }
    a.erase(a.begin()+i);
}

void search(std::vector<int> &a){
    int v,count=0;
    cout<<"value=";
    cin>>v;
    for(int i=0;i<a.size();i++){
        if(a[i]==v){
            count += 1;
        }
    }
    if(count>0){
        cout<<"\nvalue "<<v<<" found "<<count<<" times in the array\n";
    }
    else{
        cout<<"\nvalue "<<v<<" not found in array\n";
    }
    getch();
}