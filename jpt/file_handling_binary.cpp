#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;
class test{
    char s[20];
    int num;
    public:
    void in(){
        cin>>s>>num;
    }
    void out(){
        cout<<"\n"<<s<<"\n"<<num<<endl;
    }
};
int main(){
    char c;
    test a,tmp;
    fstream f("test.dat",ios::binary|ios::out|ios::in);
    f.seekg(0);
    f.seekp(0);
    a.in();
    while(f.read((char*)(&tmp),sizeof(test))){
        tmp.out();
        cout<<"do you want to paste here "<<f.tellg()<<"/"<<f.tellp()<<" : ";
        c=getch();
        if(c=='y'){
            f.write((char*)(&a),sizeof(test));
            break;
        }
    }
    //a.in();f.write((char*)(&a),sizeof(test));
    f.close();
}