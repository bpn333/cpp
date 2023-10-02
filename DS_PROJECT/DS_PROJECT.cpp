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
class account{
    protected:
    int account_no;
    char username[20];
    char password[20];
    account_type type;
    int balance;
    account *next;
    public:
    account(){}
    account(int an,char usrnm[],char passwd[],account_type t,int b){
        account_no = an;
        strcpy(username,usrnm);
        strcpy(password,passwd);
        type = t;
        next = nullptr;
        balance = b;
    }
    void show(){
        cout<<endl;
        cout<<"Account no = "<<account_no<<endl;
        cout<<"Username = "<<username<<endl;
        //cout<<"Password = "<<password<<endl;            //testing
        switch(type){
            case 0:cout<<"Account type = saving"<<endl;break;
            case 1:cout<<"Account type = active"<<endl;break;
            case 2:cout<<"Account type = locked"<<endl;break;
        }
        cout<<"Balance = "<<balance<<" /-"<<endl;
    }
    void transfer(account *&o){
        if(!security_check() || !o->security_check()){
            return;
        }
        int amount;
        cout<<"Amount to transfer = ";
        cin>>amount;
        if(amount <= 0 ){
            cout<<"Minimum Amount should be greater than 0"<<endl;
        }
        else if(amount > balance){
            cout<<"Not enough balance in account"<<endl;
        }
        else{
            balance -= amount;
            o->balance += amount;
            record(Date+" Transferred "+to_string(amount)+" /-"+" to "+to_string(o->account_no));
            o->record(Date+" Received "+to_string(amount)+" /-"+" from "+to_string(account_no));
        }
    }
    void Deposit(){
        if(!security_check()){
            return;
        }
        int amount;
        cout<<"Amount to Deposit = ";
        cin>>amount;
        if(amount > 500000){
            cout<<"YOU WILL NEED SPECIAL DOCUMENT AND PERMISSION TO Deposit MORE THAN 500000"<<endl;
        }
        else if(amount <= 0){
            cout<<"Minimum Amount should be greater than 0"<<endl;
        }
        else{
            balance += amount;
            record(Date+" Deposited "+to_string(amount)+" /-");
        }
    }
    void withdraw(){
        if(!security_check()){
            return;
        }
        int amount;
        cout<<"Amount to debit = ";
        cin>>amount;
        if(amount > 50000){
            cout<<"YOU WILL NEED SPECIAL DOCUMENT AND PERMISSION TO DEBIT MORE THAN 50000"<<endl;
        }
        else if(amount <= 0){
            cout<<"Minimum Amount should be greater than 0"<<endl;
        }
        else{
            balance -= amount;
            record(Date+" Withdrawn "+to_string(amount)+" /-");
        }
    }
    void record(string msg){
        ofstream r;
        string accnt = to_string(account_no);
        r.open("records/" + accnt + "_history.txt",ios::app);
        //cout<<"called record for file "<<"/records/" + accnt + ".txt"<<endl;
        //cout<<"msg:-\n"<<msg<<endl;
        r<<msg<<endl;
        r.close();
    }
    int return_accnt_no(){
        return account_no;
    }
    char* return_username(){
        return username;
    }
    bool security_check(){
        ifstream r;
        string l;
        int count = 0;
        string accnt = to_string(account_no);
        r.open("records/" + accnt + "_history.txt",ios::app);
        while(getline(r,l)){
            if(l.find(Date) != std::string::npos){
                count += 1;
            }
        }
        if(count>=5){
            cout<<"WE LOCKED ACCOUNT "<<account_no<<" FOR REACHING TRANSACTION LIMIT"<<endl;
            record(Date+" Attempted to use "+to_string(count)+"th service today");
            record(Date+" ACCOUNT LOCKED FOR REACHING LIMIT");
            type = locked;
        }
        else{
            type = saving;
        }
        if(type == locked){
            cout<<account_no<<" ACCOUNT LOCKED"<<endl;
            return false;
        }
        else{
            return true;
        }
    }
    friend class accounts;
};
class accounts{                             //singlylinked list implementation with 2 pointers at start and end
    private:
    account *hptr;
    account *tptr;
    public:
    int total_number;
    accounts(){
        total_number = 0;
        hptr = nullptr;
        tptr = nullptr;
    }
    void loadfile(){
        ifstream db(database);
        account tmp;
        while(db.read(reinterpret_cast<char*>(&tmp),sizeof(account))){
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
        total_number += 1;
    }
    void show_all(){           //testing
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
    account* find_account(int acnt_num){
        account *tmptr=hptr;
        while(tmptr!=nullptr){
            if(tmptr->account_no == acnt_num){
                return tmptr;
            }
            tmptr = tmptr->next;
        }
        return nullptr;
    }
};
class account_detail{
    account_detail *node;
    int account_no;
    char name[20];
    char address[20];
    char DOB[20];
    char father_name[20];
    char mother_name[20];
    char profession[20];
    account_detail *node_left;
    account_detail *node_right;
    public:
    account_detail(){}
    account_detail(int accnt_no,char nm[],char add[],char DBirth[],char father[],char mother[],char ocuptn[]){
        account_no = accnt_no;
        strcpy(name,nm);
        strcpy(address,add);
        strcpy(DOB,DBirth);
        strcpy(father_name,father);
        strcpy(mother_name,mother);
        strcpy(profession,ocuptn);
        node_left = nullptr;
        node_right = nullptr;
    }
    void show_detail(){
        cout<<"ACCOUNT DETAIL :- "<<endl;
        cout<<"Account No : "<<account_no<<endl;
        cout<<"Name : "<<name<<endl;
        cout<<"Address : "<<address<<endl;
        cout<<"Father's Name : "<<father_name<<endl;
        cout<<"Mother's Name : "<<mother_name<<endl;
        cout<<"Profession : "<<profession<<endl;
        cout<<endl;
    }
    friend class account_details; 
};
class account_details{          //Binary Search Tree implementation to store user details
    account_detail *root;
    public:
    account_details(){
        root = nullptr;
    }
    void loadfile(){
        ifstream db("users_details.dat");
        account_detail tmp;
        while(db.read(reinterpret_cast<char*>(&tmp),sizeof(account_detail))){
            add_account_detail(tmp.account_no,tmp.name,tmp.address,tmp.DOB,tmp.father_name,tmp.mother_name,tmp.profession);
            //tmp.show_detail();        //testing
        }
        db.close();
    }
    void savefile(account_detail *node,ofstream &db){           //saves in inorder sequence
        if(node->node_left){
            savefile(node->node_left,db);
        }
        db.write(reinterpret_cast<char*>(node),sizeof(account_detail));
        if(node->node_right){
            savefile(node->node_right,db);
        }
    }
    void savefile(){
        ofstream db("users_details.dat");
        savefile(root,db);
        db.close();
    }
    void add_account_detail(int accnt_no,char nm[],char add[],char DBirth[],char father[],char mother[],char ocuptn[]){
        account_detail *nptr = new account_detail(accnt_no,nm,add,DBirth,father,mother,ocuptn);
        if(root == nullptr){
            root = nptr;
        }
        else{
            account_detail *current_node=root;
            while(true){
                if(accnt_no > current_node->account_no){
                    if(current_node->node_right == nullptr){
                        current_node->node_right = nptr;
                        break;
                    }
                    current_node = current_node->node_right;
                }
                else{
                    if(current_node->node_left == nullptr){
                        current_node->node_left = nptr;
                        break;
                    }
                    current_node = current_node->node_left;
                }
            }
        }
    }
    account_detail* find_detail(int accnt_no){
        if(root == nullptr){
            return nullptr;
        }
        account_detail *current_node=root;
        while(true){
            if(current_node->account_no == accnt_no){
                return current_node;
            }
            if(accnt_no > current_node->account_no){
                if(!current_node->node_right){
                    return nullptr;
                }
                current_node = current_node->node_right;
            }
            else{
                if(!current_node->node_left){
                    return nullptr;
                }
                current_node = current_node->node_left;
            }
        }
        return nullptr;
    }
    void show_account_detail(int accnt_no){
        account_detail *acnt_detail = find_detail(accnt_no);
        if(acnt_detail == nullptr){
            cout<<"NO DETAILS FOUND";
            return;
        }
        acnt_detail->show_detail();
    }
    void fill_detail(int accnt_no){
        account_detail *nptr = new account_detail;
        cout<<endl;
        cout<<"\nACCOUNT DETAIL :- "<<endl;
        cout<<"\nAccount No : "<<accnt_no<<endl;
        nptr->account_no = accnt_no;
        cin.ignore();
        cout<<"\nName : ";
        fgets(nptr->name,20,stdin);
        cout<<"Address : ";
        fgets(nptr->address,20,stdin);
        cout<<"Father's Name : ";
        fgets(nptr->father_name,20,stdin);
        cout<<"Mother's Name : ";
        fgets(nptr->mother_name,20,stdin);
        cout<<"Profession : ";
        fgets(nptr->profession,20,stdin);
        cout<<endl;
        add_account_detail(nptr->account_no,nptr->name,nptr->address,nptr->DOB,nptr->father_name,nptr->mother_name,nptr->profession);
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
void password_enter(char passwd[]){
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
    cout<<endl;
}
void read_file(string file_name){
    int max = 20;
    int count = 1;
    ifstream f(file_name);
    string line;
    while(getline(f,line)){
        cout<<line<<endl;
        count++;
        if(count % max == 0){
            getch();
        }
    }
    getch();
}
void register_account(accounts &accnts){
    char usrnm[20],passwd_1[20],passwd_2[20];
    int account_number;
    char c;
    cout << "Do you want to Register Account :- ";
    c = getch();
    cout << "\x1B[2J\x1B[H";
    if(c!='y'){
        return;
    }
    cout<<endl;
    aa:
    cout << "\x1B[2J\x1B[H";  //clrscr();
    cout<<"\t\t\tWELCOME TO REGISTER PAGE"<<endl;
    cout<<"\n\nUserName = ";
    cin>>usrnm;
    cout<<"\nPassword = ";
    password_enter(passwd_1);
    cout<<"\nRetype Password = ";
    password_enter(passwd_2);
    if(strcmp(passwd_1,passwd_2)!=0){
        cout<<"BOTH PASSWORD DOESNT MATCH"<<endl;
        getch();
        cout << "\x1B[2J\x1B[H";
        goto aa;
    }
    for(int i=0;i<accnts.total_number;i++){
        account_number = rand() % (1000000 - 1000 + 1) + 1000;      //formula = rand() % (higher_limit - lower_limit + 1) + lower_limit
    }
    accnts.add_account(account_number,usrnm,passwd_1,saving,0);
    account_details a;
    a.loadfile();
    a.fill_detail(account_number);
    a.savefile();
    cout << "\x1B[2J\x1B[H";
}
bool login(accounts &accnts, account *&working_acnt){
    char usrnm[20],passwd[20];
    register_account(accnts);
    cout<<"##############################################################################"<<endl;
    cout<<"\t\t\tWELCOME TO LOGIN PAGE"<<endl;
    cout<<"\n\nUserName = ";
    cin>>usrnm;
    cout<<"\nPassword = ";
    password_enter(passwd);
    cout<<endl;
    working_acnt = accnts.user_account(usrnm,passwd);
    if(!working_acnt){
        cout<<"LOGIN FAILED"<<endl;
        return false;
    }
    return true;
}
void user_dashboard(account *&working_acnt,accounts &accnts){
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
        cout<<"3.Withdraw Balance"<<endl;
        cout<<"4.History"<<endl;
        cout<<"5.User Details"<<endl;
        cout<<"6.Exit"<<endl;
        cout<<"choice = ";
        cin>>choice;
        switch(choice){
            case 1:
            {
                int acnt_num;
                account *receiver_acnt;
                cout<<"Enter the account number of receiver_acnt = ";
                cin>>acnt_num;
                receiver_acnt = accnts.find_account(acnt_num);
                if(!receiver_acnt){
                    cout<<"ACCOUNT NOT FOUND WITH THAT ACCOUNT NUMBER"<<endl;
                }
                else{
                    working_acnt->transfer(receiver_acnt);
                }
            }
            break;
            case 2:
            working_acnt->Deposit();
            break;
            case 3:
            working_acnt->withdraw();
            break;
            case 4:
            read_file("records/" + to_string(working_acnt->return_accnt_no()) + "_history.txt");
            break;
            case 5:
            {
                account_details a;
                a.loadfile();
                a.show_account_detail(working_acnt->return_accnt_no());
            }
            break;
            case 6:
            return;
            break;
            default:
            cout<<"ERROR INVALID OPTION"<<endl;
        }
        getch();
    }
}
int main(){
    Date = readDate();
    accounts accnts;
    account *working_acnt;
    accnts.loadfile();
    accnts.show_all();
    cout << "\x1B[2J\x1B[H";
    if(login(accnts,working_acnt)){
        cout << "\x1B[2J\x1B[H";
        cout<<"\n\n\t\tLOGIN SUCESSFULL.....\n";
        working_acnt->show();
        getch();
        user_dashboard(working_acnt,accnts);
    }
    updateDate();
    accnts.savefile();
}