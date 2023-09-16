#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
using namespace std;
struct{
    enum{
        logged,
        notlogged
    } acnt = notlogged;
} state;
class account{
    string username;
    string password;
    string type;
    public:
    void load(){
        ifstream users;
        string u,p,t;
        users.open("users.txt");
        string usrnm,passwd;
        cout<<"username = ";
        cin>>usrnm;
        cout<<"password = ";
        passwd = passwd_enter();
        while(users>>u){
            users>>p;
            users>>t;
            if(u==usrnm && p==passwd){
                cout<<"found";
                users.close();
                return;
            }
            cout<<u<<p<<t;
        }
        cout<<"\nERROR ACCOUNT NOT FOUND WITH THOSE DETAILS\n";
        users.close();
    }
    void new_account(string t = "student"){
        cout<<"Username = ";
        cin>>username;
        cout<<"Password = ";
        cin.ignore();
        getline(cin,password);
        type = t;
    }
    void change_username(){
        if(!authenticate()){
            cout<<"\nAUTHENTICATION FAILED\n";
            return;
        }
        cout<<"New Username = ";
        cin.ignore();
        cin>>username;
    }
    void change_password(){
        if(!authenticate()){
            cout<<"\nAUTHENTICATION FAILED\n";
            return;
        }
        cout<<"New Password = ";
        cin.ignore();
        getline(cin,password);
    }
    bool authenticate(){
        string usrnm,passwd;
        cout<<"username = ";
        cin>>usrnm;
        cout<<"password = ";
        passwd = passwd_enter();
        if(usrnm==username && passwd==password){
            return true;
        }
        else{
            return false;
        }
    }
    string passwd_enter(){
        string passwd;
        while(true){
            char c;
            c=getch();
            if(c=='\n' || c=='\r'){
                passwd.push_back(c);
                break;
            }
            passwd.push_back(c);
            cout<<"*";
        }
        return passwd;
    }
};
void handle_account(){
    account a;
    int c;
    cout<<"1.login\n2.register\nchoice=";
    cin>>c;
    switch(c){
        case 1:
        a.load();
        break;
    }
}
int main(){
    if(state.acnt != state.logged){
        handle_account();
    }
}