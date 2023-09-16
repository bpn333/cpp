#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include<vector>
#define ADMIN_PASS 333
using namespace std;
enum state{
    logged,
    notlogged
};
state acnt = notlogged;
class account{
    string username;
    string password;
    string type;
    public:
    bool load(string usr = "NOTGIVEN",string pass = "NOTGIVEN"){
        ifstream users;
        string u,p,t;
        users.open("users.txt");
        string usrnm,passwd;
        if(usr == "NOTGIVEN" || pass == "NOTGIVEN"){
            cout<<"username = ";
            cin>>usrnm;
            cin.ignore();
            cout<<"password = ";
            passwd = passwd_enter();
        }
        else{
            usrnm = usr;
            passwd = pass;
        }
        while(users>>u>>p>>t){
            if(u==usrnm && p==passwd){
                acnt = logged;
                username=u;
                password=p;
                type=t;
                users.close();
                return true;
            }
        }
        users.close();
        return false;
    }
    void overwrite(string user, string pass) {
        ifstream infile("users.txt");
        ofstream outfile("temp.txt");
        string u, p, t;
        while (infile >> u >> p >> t) {
            if (u == username && p == password) {
                u = user;
                p = pass;
            }
            outfile<<u<<"\n"<<p<<"\n"<<t<<endl;
            username = user;
            password = pass;
        }
        infile.close();
        outfile.close();
        remove("users.txt");
        rename("temp.txt", "users.txt");
    }
    void new_account(string t = "student"){
        ofstream users;
        users.open("users.txt",ios::app);
        input:
        cin.ignore();
        cout<<"Username = ";
        cin>>username;
        if(!check_username(username)){
            cout<<"USERNAME ALREADY EXIST\n";
            goto input;
        }
        cin.ignore();
        cout<<"Password = ";
        password = passwd_enter();
        type = t;
        users<<username<<"\n"<<password<<"\n"<<type<<endl;
        acnt = logged;
        fill_details(*this);
    }
    void change_username(){
        string usr;
        if(!authenticate()){
            cout<<"\nAUTHENTICATION FAILED\n";
            return;
        }
        cout<<"\nNew Username = ";
        cin>>usr;
        cin.ignore();
        overwrite(usr,password);
    }
    void change_password(){
        string pass;
        if(!authenticate()){
            cout<<"\nAUTHENTICATION FAILED\n";
            return;
        }
        cout<<"\nNew Password = ";
        pass = passwd_enter();
        overwrite(username,pass);
    }
    bool authenticate() const{
        string usrnm,passwd;
        cout<<"username = ";
        cin>>usrnm;
        cin.ignore();
        cout<<"password = ";
        passwd = passwd_enter();
        if(usrnm==username && passwd==password){
            return true;
        }
        else{
            return false;
        }
    }
    bool check_username(string &s) const{
        ifstream users("users.txt");
        string u;
        while(users>>u){
            if(u==s){
                users.close();
                return false;
            }
            users>>u>>u;
        }
        users.close();
        return true;
    }
    string passwd_enter() const{
        string passwd;
        while(true){
            char c;
            c=getch();
            if(c=='\n' || c=='\r'){
                break;
            }
            passwd.push_back(c);
            cout<<"*";
        }
        return passwd;
    }
    string return_type(){
        return type;
    }
    string return_type(string user){
        ifstream users;
        string u,p,t;
        users.open("users.txt");
        while(users>>u>>p>>t){
            if(u==user){
                return t;
            }
        }
        users.close();
        return "ERROR";
    }
    string return_username(){
        return username;
    }
    friend void fill_details(account &a);
    friend void show_details(account &a);
    friend void store_cookies(account &a,bool option);
};
class result : public account{
    string user_name;
    string session;
    int math;
    int science;
    int computer;
    int english;
    int social;
    public:
    void input(){
        cin.ignore();
        cout<<"Examination = ";
        getline(cin,session);
        aaa:
        cout<<"Students Username = ";
        cin>>user_name;
        if(check_username(user_name) || return_type(user_name)!="student"){
            cout<<"\nERROR\n";
            goto aaa;
        }
        cin.ignore();
        cout<<"Marks in different subjects :-\n";
        cout<<"Math = ";
        cin>>math;
        cout<<"Science = ";
        cin>>science;
        cout<<"Computer = ";
        cin>>computer;
        cout<<"English = ";
        cin>>english;
        cout<<"Social = ";
        cin>>social;
        cin.ignore();
    }
    int get_total(){
        return math+science+computer+english+social;
    }
    float get_percent(){
        return ((math+science+computer+english+social)/500.00)*100.00;
    }
    void write(){
        fstream res;
        ifstream old;
        string tmp0,tmp1,tmp2;
        string filename = user_name;
        filename += ".txt";
        filename = "results/" + filename;
        res.open(filename,ios::app);
        old.open(filename);
        while(old>>tmp0>>tmp1>>tmp2){
            if(tmp0=="Examination" && tmp1=="=" && tmp2==session){
                cout<<"Result Already Exist Of The Exam\n";
                return;
            }
        }
        old.close();
        res<<"Examination = "<<session<<"\nStudent = "<<user_name<<"\nMarks in all subjects :-\n";
        res<<"Math = "<<math<<"\nScience = "<<science<<"\nComputer = "<<computer<<"\nEnglish = "<<english<<"\nSocial = "<<social;
        res<<"\n----------------------\n";
        res<<"Total marks = "<<get_total()<<endl;
        res<<"Total Percentage = "<<get_percent()<<"%"<<endl;
        if(get_percent()>90){
            res<<"Grade = A+"<<endl;
        }
        else if(get_percent()>80){
            res<<"Grade = A"<<endl;
        }
        else if(get_percent()>70){
            res<<"Grade = B+"<<endl;
        }
        else if(get_percent()>60){
            res<<"Grade = B"<<endl;
        }
        else if(get_percent()>50){
            res<<"Grade = c+"<<endl;
        }
        else if(get_percent()>40){
            res<<"Grade = PASS"<<endl;
        }
        else{
            res<<"Grade = FAIL"<<endl;
        }
        res<<"\n\n";
        res.close();
    }
};
void fill_details(account &a){
    if(acnt == logged){
        ofstream data;
        string name,address,phone,DOB,position,DOJ;
        int roll;
        string filename = a.username;
        filename += ".txt";
        filename = "users/" + filename;
        data.open(filename);
        cout<<"\n\tfill the following details\n";
        cout<<"name = ";
        getline(cin,name);
        if(a.return_type()=="student"){
            cout<<"roll no = ";
            cin>>roll;
            cin.ignore();
        }
        else if(a.return_type()=="teacher"){
            cout<<"Employee no = ";
            cin>>roll;
            cin.ignore();
        }
        cout<<"address = ";
        getline(cin,address);
        cout<<"phone no = ";
        cin>>phone;
        cin.ignore();
        cout<<"Date of Birth = ";
        getline(cin,DOB);
        if(a.return_type()=="teacher"){
            cout<<"position = ";
            getline(cin,position);
            cout<<"Date of joining = ";
            cin>>DOJ;
            cin.ignore();
        }
        if(a.return_type()=="student"){
            data<<"NAME = "<<name<<"\nRoll No = "<<roll<<"\nAddress = "<<address<<"\nPhone No = "<<phone<<"\nDate of Birth = "<<DOB<<endl;
        }
        else if(a.return_type()=="teacher"){
            data<<"NAME = "<<name<<"\nEmp No = "<<roll<<"\nAddress = "<<address<<"\nPhone No = "<<phone<<"\nDate of Birth = "<<DOB<<"\nPosition = "<<position<<"\nDate of Joining = "<<DOJ<<endl;
        }
        data.close();
    }
}
void store_cookies(account &a,bool option){
    ofstream cookie;
    cookie.open("cookie.txt");
    if(option){
        cookie<<a.username<<"\n"<<a.password<<"\n"<<a.type<<endl;
    }
    else{
        cookie<<"";
    }
    cookie.close();
}
void read_file(string filename,bool showline=false,bool wait=true,int start_line = 0,int end_line = 0){
    int line=1;
    ifstream data(filename);
    if (!data.is_open()) {
        cout << "Error: Could not open user detail file." << endl;
        return;
    }
    string s;
    while(getline(data, s)){
        if(start_line){
            start_line--;
            continue;
        }
        if(showline){
            cout<<line<<". ";
        }
        cout << s << endl;
        line++;
        if(end_line){
            if(line>end_line){
                break;
            }
        }
        if(line%15 == 0){
            getch();
        }
    }
    if(wait){
       getch(); 
    }
    data.close();
}
void show_details(account &a){
    string filename = a.username + ".txt";
    filename = "users/" + filename;
    read_file(filename);
}
void handle_account(account &a){
    int c;
    int attempt=3;
    aa:
    cout<<"\tWELCOME TO LOGIN PAGE\n";
    cout<<"1.login\n2.register\nchoice=";
    cin>>c;
    switch(c){
        case 1:
        if(!a.load()){
            cout<<"\nERROR ACCOUNT NOT FOUND WITH THOSE DETAILS\n";
        }
        break;
        case 2:
        char c;
        int p;
        cout<<"are you teacher (y/n)= ";
        cin>>c;
        if(c=='y' || c=='Y'){
            cout<<"Admin Pass = ";
            cin>>p;
            if(p==ADMIN_PASS){
                a.new_account("teacher");
            }
        }
        else{
            a.new_account();
        }
        break;
    }
    attempt--;
    if(attempt!=0 && acnt != logged){
        goto aa;
    }
}
void result_list(account &a){
    string s;
    int no = 1,choice;
    int line = 0,string=0;
    vector<int> lines_no;
    ifstream r("results/"+a.return_username()+".txt");
    while(r>>s){
        if(s == "Examination"){
            cout<<no<<".";
            r>>s;
            r>>s;
            while(s != "Student"){
                cout<<s;
                r>>s;
            }
            cout<<endl;
            no++;
            lines_no.push_back(line);
            line+=3;
        }
        else{
            string++;
        }
        if(string==3){
            line++;
            string = 0;
        }
    }
    aaa:
    cout<<"choice = ";
    cin>>choice;
    if(choice>no || choice<1){
        cout<<"\nERROR\n";
        goto aaa;
    }
    read_file("results/"+a.return_username()+".txt",false,true,lines_no[choice-1],(lines_no.size()>choice)?lines_no[choice]:999);
}
void write_file(string filename){
    fstream ano;
    int op;
    aa:
    cout<<"Open in :-\n1.Overwrite\n2.Append\nchoice=";
    cin>>op;
    if(op==1){
        ano.open(filename,ios::out);
    }
    else if(op==2){
        ano.open(filename,ios::app);
    }
    else{
        cout<<"\ninvalid option\n";
        goto aa;
    }
    string s;
    int line_no = 1;
    cin.ignore();
    cout<<"Enter line empty to save :-\n";
    while(true){
        cout<<line_no<<".";
        getline(cin,s);
        if(s.empty()){
            break;
        }
        line_no++;
        ano<<s<<endl;
    }
    ano.close();
}
string choose_subject(){
    int c;
    aa:
    cout<<"choose one of following subjects:-\n";
    cout<<"1.math"<<endl;
    cout<<"2.science"<<endl;
    cout<<"3.computer"<<endl;
    cout<<"4.english"<<endl;
    cout<<"5.social"<<endl;
    cout<<"choice=";
    cin>>c;
    switch(c){
        case 1:
        return "math";
        break;
        case 2:
        return "science";
        break;
        case 3:
        return "computer";
        break;
        case 4:
        return "english";
        break;
        case 5:
        return "social";
        break;
        default:
        cout<<"\n\n\n";
        goto aa;
    }
}
void update_material(string filename){
    fstream stdy;
    stdy.open("study_materials.txt",ios::app);
    stdy<<filename<<endl;
    stdy.close();
}
void student_menu(account &a){
    int choice,c;
    cout<<"\tWELCOME TO AMRITSAR LMS SOFTWARE\n\n";
    cout<<"----------------------------------------\n";
    read_file("announcement.txt",false,false);
    cout<<"-----------------------------------------\n";
    cout<<"\n1.Study Materials"<<endl;
    cout<<"2.View Result"<<endl;
    cout<<"3.Account Manager"<<endl;
    cout<<"4.Logout"<<endl;
    cout<<"choice=";
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
        {
            string tmp;
            int choice,line=1;
            read_file("study_materials.txt",true,false);
            cout<<"choice = ";
            cin>>choice;
            ifstream st("study_materials.txt");
            while(getline(st,tmp)){
                if(line==choice){
                    break;
                }
                line++;
            }
            read_file(tmp);
            break;
        }
        case 2:
        result_list(a);
        //read_file("results/"+a.return_username()+".txt");
        break;
        case 3:
        cout<<"\n\n\tACCOUNT MANAGER\n";
        cout<<"1.View Details"<<endl;
        cout<<"2.Change UserName"<<endl;
        cout<<"3.Change Password"<<endl;
        cout<<"choice=";
        cin>>c;
        cin.ignore();
        switch(c){
            case 1:
            show_details(a);
            break;
            case 2:
            a.change_username();
            break;
            case 3:
            a.change_password();
            break;
            default:
            cout<<"\nINVALID OPTION\n";
        }
        break;
        case 4:
        {
            string str;
            cout<<"Do you want to stay logged in ? ['yes'/'no'] = ";
            cin>>str;
            if(str=="yes"){
                store_cookies(a,true);
            }
            else{
                store_cookies(a,false);
            }
            acnt = notlogged;
        }
        break;
    }
    getch();
}
void teacher_menu(account &a){
    int choice,c;
    result r;
    cout<<"\tWELCOME TO AMRITSAR LMS SOFTWARE\n";
    cout<<"1.Announcement"<<endl;
    cout<<"2.Set Result"<<endl;
    cout<<"3.Upload Study Material"<<endl;
    cout<<"4.Account Manager"<<endl;
    cout<<"5.Logout"<<endl;
    cout<<"choice=";
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
        write_file("announcement.txt");
        break;
        case 2:
        r.input();
        r.write();
        break;
        case 3:
 cout << "\x1B[2J\x1B[H";        {
            int option;
            string filename,subject,path;
            cout<<"Choose One of following ways to provide study material:-\n";
            cout<<"1.Write in Editor"<<endl;
            cout<<"2.Give Path of already written material"<<endl;
            cout<<"choice=";
            cin>>option;
            cin.ignore();
            switch(option){
                case 1:
                subject=choose_subject();
                cin.ignore();
                cout<<"chapter_name=";
                cin>>filename;
                cin.ignore();
                write_file("study_material/"+subject+"/"+filename+".txt");
                update_material("study_material/"+subject+"/"+filename+".txt");
                break;
                case 2:
                cout<<"Provide Full Path of the source file :-\n";
                cout<<"path=";
                cin>>path;
                cin.ignore();
                subject = choose_subject();
                cout<<"chapter_name=";
                cin>>filename;
                cin.ignore();
                filename = "study_material/"+subject+"/"+filename+".txt";
                if (rename(path.c_str(),filename.c_str()) == 0) {
                    cout << "File moved successfully." << endl;
                    update_material(filename);
                } 
                else {
                    cout << "Error: Unable to move the file." << endl;
                }
                break;
                default:
                cout<<"\nERROR INVALID OPTION\n";
            }
        }
        break;
        case 4:
        cout<<"\n\n\tACCOUNT MANAGER\n";
        cout<<"1.View Details"<<endl;
        cout<<"2.Change UserName"<<endl;
        cout<<"3.Change Password"<<endl;
        cout<<"choice=";
        cin>>c;
        cin.ignore();
        switch(c){
            case 1:
            show_details(a);
            break;
            case 2:
            a.change_username();
            break;
            case 3:
            a.change_password();
            break;
            default:
            cout<<"\nINVALID OPTION\n";
        }
        break;
        case 5:
        {
            string str;
            cout<<"Do you want to stay logged in ? ['yes'/'no'] = ";
            cin>>str;
            if(str=="yes"){
                store_cookies(a,true);
            }
            else{
                store_cookies(a,false);
            }
            acnt = notlogged;
        }
        break;
    }
    getch();
}
void check_cookies(account &a){
    ifstream cookie;
    string u,p,t;
    cookie.open("cookie.txt");
    cookie>>u>>p>>t;
    if(a.load(u,p)){
        cout<<"LOGGED IN USING COOKIE\n";
        cout<<"username = "<<u<<endl;
        cout<<"type = "<<t<<endl;
        getch();
    }
    cookie.close();
}
int main(){
    account a;
    cout << "\x1B[2J\x1B[H";
    check_cookies(a);
    if(acnt != logged){
        handle_account(a);
    }
    while(acnt == logged){
        cout << "\x1B[2J\x1B[H";
        if(a.return_type()=="student"){
            student_menu(a);
        }
        else if(a.return_type()=="teacher"){
            teacher_menu(a);
        }
    }
}