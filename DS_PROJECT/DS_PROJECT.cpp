#include<iostream>
#include<conio.h>
#include<cstring>
#include<fstream>
#define database "data.dat"
using namespace std;
enum account_type{
    saving ,
    active ,
    locked
};
class account{                      //singlylinked list
    protected:
    int account_no;
    char username[20];
    char password[20];
    account_type type;
    int balance;
    account *next;
    public:
    account(int an,char usrnm[],char passwd[],account_type t,int b){
        account_no = an;
        strcpy(username,usrnm);
        strcpy(password,passwd);
        type = t;
        next = nullptr;
        balance = b;
    }
    void show(){
        cout<<"Account no = "<<account_no<<endl;
        cout<<"Username = "<<username<<endl;
        cout<<"Account type = "<<type<<endl;
        cout<<"Balance = "<<balance<<endl;
    }
    friend class accounts;
};
class accounts{
    account *hptr;
    account *tptr;
    public:
    accounts(){
        cout<<"constructor called"<<endl;
        hptr = nullptr;
        tptr = nullptr;
    }
    void loadfile(){
        ifstream db(database);
        account tmp(0,(char*)"",(char*)"",saving,0);
        while(db.read((char*)(&tmp),sizeof(account))){
            add_account(tmp.account_no,tmp.username,tmp.password,tmp.type,tmp.balance);
        }
        db.close();
    }
    void savefile(){
        ofstream db(database);
        account *tmptr=hptr;
        while(tmptr!=nullptr){
            db.write(reinterpret_cast<char*>(tmptr),sizeof(account));
            tmptr = tmptr->next;
        }
        db.close();
    }
    void add_account(int an,char usrnm[],char passwd[],account_type t,int b){
        account *a = new account(an,usrnm,passwd,t,b);
        if(!tptr || !hptr){
            tptr = hptr = a;
        }
        else{
            tptr->next = a;
            tptr = a;
        }
    }
    void show_all(){
        account *tmptr=hptr;
        cout<<"ACCOUNTS :-\n";
        while(tmptr!=nullptr){
            //cout<<tmptr->username;
            tmptr->show();
            tmptr = tmptr->next;
        }
    }
};
bool login(){
    
}
int main(){
    accounts accnts;
    accnts.loadfile();
    accnts.show_all();
}