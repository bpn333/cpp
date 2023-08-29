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
void editor(vector<int> &vec);
void shift(vector<int> &vec,int c);
void operation(vector<int> &vec,char c);

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
        cout<<"6.EDITOR\n";
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

            case 6:
            editor(vec);
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

void editor(vector<int> &vec){
    int choice,num;
    cout<<"\tPerform Operation On All Member\n";
    cout<<"1.Add\n";
    cout<<"2.Sub\n";
    cout<<"3.Product\n";
    cout<<"4.Right Shift\n";
    cout<<"5.Left Shift\n";
    cout<<"choice=";
    cin>>choice;
    switch(choice){
        case 1:
        operation(vec,'+');
        break;

        case 2:
        operation(vec,'-');
        break;

        case 3:
        operation(vec,'*');
        break;

        case 4:
        shift(vec,1);
        break;

        case 5:
        shift(vec,-1);
        break;

        default:
        cout<<"\nERROR\n";
    }
}
void shift(std::vector<int> &vec,int c){
    int num;
    std::vector<int> tmp(vec);
    cout<<"num=";
    cin>>num;
    for(int i=0;i<vec.size();i++){
        if(c==1){
            if(i<num){
                vec[i]=0;
            }
            else{
                vec[i]=tmp[i-num];
            }
        }
        else if(c==-1){
            cout<<"left shift";
            if(i>vec.size()-num-1){
                vec[i]=0;
            }
            else{
                vec[i]=tmp[i+num];
            }
        }
    }
    cout<<"\nARRAY MODIFIED\n";
    display(vec);
}
void operation(std::vector<int> &vec,char c){
    int num;
    cout<<"num=";
    cin>>num;
    for(int i=0;i<vec.size();i++){
        if(c=='+'){
            vec[i]+=num;
        }
        else if(c=='-'){
            vec[i]-=num;
        }
        else if(c=='*'){
            vec[i]*=num;
        }
    }
    cout<<"\nARRAY MODIFIED\n";
    display(vec);
}