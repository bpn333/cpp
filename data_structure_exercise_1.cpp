#include<iostream>
#include<conio.h>
#include<vector>
using namespace std;
std::vector<int> initialize(std::vector<int> a);
void display(std::vector<int> a);
std::vector<int> insert_element(std::vector<int> a);
std::vector<int> delete_element(std::vector<int> a);
int main(){
    int n,c;
    bool running=1;
    cout<<"number of members:-";
    cin>>n;
    std::vector<int> a(n);
    while(running){
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<"\t\tchoose one of the following options\n1.initialize\n2.insert\n3.delete\n4.display\n5.exit\nchoice:-"; 
        cin>>c;
        switch(c){
            case 1:
            a=initialize(a);
            break;

            case 2:
            a=insert_element(a);
            cout<<"\nARRAY MODIFIED\n";
            display(a);
            break;

            case 3:
            a=delete_element(a);
            cout<<"\nARRAY MODIFIED\n";
            display(a);
            break;

            case 4:
            display(a);
            break;

            case 5:
            running=0;
            break;
        }
    }
    return 0;
}
std::vector<int> initialize(std::vector<int> a){
    cout<<"\nenter array data:-\n";
    for(int i=0;i<a.size();i++){
        cin>>a[i];
    }
    return a;
}
void display(std::vector<int> a){
    cout<<"\narray data:-\n";
    for(int i=0;i<a.size();i++){
    cout<<a[i]<<" ";
    }
    cout<<"\n";
    getch();
}
std::vector<int> insert_element(std::vector<int> a){
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
    return a;
}
std::vector<int> delete_element(std::vector<int> a){
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
    return a;
}