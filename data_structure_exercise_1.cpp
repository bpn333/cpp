#include<iostream>
#include<conio.h>
#include<vector>
#include <algorithm>
using namespace std;

void initialize(vector<int> &vec);
void display(vector<int> &vec);
void insert_element(vector<int> &vec);
void delete_element(vector<int> &vec);
void search(vector<int> &vec);

int main(){
    int n,c;
    cout<<"number of members:-";
    cin>>n;
    vector<int> vec(n);
    initialize(vec);
    bool run=true;
    do {
        cout<<"\t\tchoose one of the following options\n";
        cout<<"1.insert\n";
        cout<<"2.delete\n";
        cout<<"3.display\n";
        cout<<"4.search\n";
        cout<<"5.exit\n";
        cout<<"choice:-"; 
        cin>>c;
        switch(c){
            case 1:
            insert_element(vec);
            cout<<"\nARRAY MODIFIED\n";
            display(vec);
            break;

            case 2:
            delete_element(vec);
            cout<<"\nARRAY MODIFIED\n";
            display(vec);
            break;

            case 3:
            display(vec);
            getch();
            break;

            case 4:
            search(vec);
            getch();
            break;

            case 5:
            run=false;
            break;
        }
    }while(run);
    return 0;
}

void initialize(vector<int> &vec){
    cout<<"\nenter array data:-\n";
    for(int i=0;i<vec.size();i++){
        cin>>vec[i];
    }
}

void display(vector<int> &vec){
    cout<<"\narray data:-\n";
    for(auto i : vec){
    cout<<i<<" ";
    }
    cout<<"\n";
}

void insert_element(vector<int> &vec){
    int i,v;
    display(vec);
    input:
    cout<<"\nenter index :-";
    cin>>i;
    if(i<0 || i>vec.size()){
        cout<<"ERROR OUT OF RANGE";
        goto input;
    }
    cout<<"value=";
    cin>>v;
    vec.insert(vec.begin()+i,v);
}

void delete_element(vector<int> &vec){
    int i;
    display(vec);
    input:
    cout<<"\nenter index :-";
    cin>>i;
    if(i<0 || i>=vec.size()){
        cout<<"ERROR OUT OF RANGE";
        goto input;
    }
    vec.erase(vec.begin()+i);
}

void search(vector<int> &vec){
    int v;
    cout<<"value=";
    cin>>v;
    auto it = find(vec.begin(), vec.end(), v);
    if (it != vec.end()){
        cout << "\nElement found at index: " << distance(vec.begin(), it) << endl;
    } 
    else{
        cout << "\nElement not found" << endl;
    }
}