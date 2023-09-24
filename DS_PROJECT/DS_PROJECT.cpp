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
string Date;
class account{        //singly linked list
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
        switch(type){
            case 0:cout<<"Account type = saving"<<endl;break;
            case 1:cout<<"Account type = active"<<endl;break;
            case 2:cout<<"Account type = locked"<<endl;break;
        }
        cout<<"Balance = "<<balance<<endl;
    }
    friend class accounts;
};
class accounts{                             //singlylinked list implementation with 2 pointers at start and end
    private:
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
    account* user_account(char usrnm[],char passwd[]){
        account *tmptr=hptr;
        while(tmptr!=nullptr){
            if(strcmp(tmptr->username,usrnm)==0 && strcmp(tmptr->password,passwd)==0){
                return tmptr;
            }
            tmptr = tmptr->next;
        }
        return nullptr;
    }
};
string readDate(){
    ifstream i("date.txt");
    string date;
    getline(i,date);
    i.close();
    return date;
}
void updateDate(){
    ifstream i("date.txt");
    string month;
    int day,year;
    i>>day>>month>>year;
    i.close();
    string months[12] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
    day += 1;
    bool c = (month==months[0])&&(day>31);
    c = c || (year%4==0)&&(month==months[1])&&(day>29);
    c = c || (year%4!=0)&&(month==months[1])&&(day>28);
    c = c || (month==months[2])&&(day>31);
    c = c || (month==months[3])&&(day>30);
    c = c || (month==months[4])&&(day>31);
    c = c || (month==months[5])&&(day>30);
    c = c || (month==months[6])&&(day>31);
    c = c || (month==months[7])&&(day>31);
    c = c || (month==months[8])&&(day>30);
    c = c || (month==months[9])&&(day>31);
    c = c || (month==months[10])&&(day>30);
    c = c || (month==months[11])&&(day>31);
    if(c){
        day=1;
        for(int i=0;i<12;i++){
            if(month == months[i]){
                if(i!=11){
                    month = months[i+1];
                }
                else{
                    month = months[0];
                    year += 1;
                }
                break;
            }
        }
    }
    ofstream o("date.txt");
    o<<day<<" "<<month<<" "<<year;
}
bool login(accounts &accnts, account *&working_acnt){
    cout << "\x1B[2J\x1B[H";
    char usrnm[20],passwd[20];
    cout<<"##############################################################################"<<endl;
    cout<<"\t\t\tWELCOME TO LOGIN PAGE"<<endl;
    cout<<"\n\nUserName = ";
    cin>>usrnm;
    cout<<"\nPassword = ";
    int count = 0;
    char c;
    while(true){
        c = getch();
        if(c=='\n' || c=='\r'){
            passwd[count++] = '\0';
            break;
        }
        cout<<"*";
        passwd[count++] = c;
    }
    cout<<endl<<endl;
    working_acnt = accnts.user_account(usrnm,passwd);
    if(!working_acnt){
        return false;
    }
    cout<<"##############################################################################"<<endl;
    return true;
}
void user_dashboard(account *&working_acnt){
    while(true){
        int choice;
        cout << "\x1B[2J\x1B[H";
        cout<<"\t\tSBI MOBILE BANKING SYSTEM"<<endl;
        cout<<"--------------------------------------------------------------------------"<<endl;
        working_acnt->show();
        cout<<"\nDATE = "<<Date<<endl;
        cout<<"\nChoose one of the following options:-"<<endl;
        cout<<"1.Fund Transfer"<<endl;
        cout<<"2.Deposit Balance"<<endl;
        cout<<"3.History"<<endl;
        cout<<"choice = ";
        cin>>choice;
        switch(choice){
            //i will do later
        }
        return;
    }
}
int main(){
    Date = readDate();
    accounts accnts;
    account *working_acnt;
    accnts.loadfile();
    accnts.show_all();
    if(login(accnts,working_acnt)){
        cout << "\x1B[2J\x1B[H";
        cout<<"\n\n\t\tLOGIN SUCESSFULL.....\n";
        working_acnt->show();
        getch();
        user_dashboard(working_acnt);
    }
    updateDate();
}