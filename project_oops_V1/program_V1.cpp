#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include<vector>
#include<thread>
#include<chrono>
#include<filesystem>
#define ADMIN_PASS 333
#define DATABASE "user.dat"
#define DELAY(a) this_thread::sleep_for(chrono::milliseconds(a));
using namespace std;
void print_with_delay(string line,int millisecond=20,bool endline=true){
    for(int i=0;i<line.size();i++){
        cout<<line[i];
        if(line[i]==' ' || line[i]=='-'){
            continue;
        }
        DELAY(millisecond);
    }
    if(endline){
        cout<<endl;
    }
}
class account{
    string username;
    string password;
    string type;
    public:
    bool load(string usrnm="NOTGIVEN",string passwd="NOTGIVEN"){
        ifstream input("users.xyz");
        string u,p,t;
        if(usrnm=="NOTGIVEN" || passwd=="NOTGIVEN"){
            print_with_delay("\t\t\tUsername = ",40,false);
            cin>>usrnm;
            print_with_delay("\t\t\tPassword = ",40,false);
            passwd = passwd_enter();
        }
        while(getline(input,u)){
            getline(input,p);getline(input,t);
            if(u==usrnm && p==passwd){
                username = u;
                password = p;
                type = t;
                input.close();
                return true;
            }
        }
        input.close();
        return false;
    }
    void update_file(string usr,string pass){
        ofstream output("users_tmp.xyz");
        ifstream input("users.xyz");
        string u,p,t;
        while(getline(input,u)){
            getline(input,p);getline(input,t);
            if(u==username && p==password){
                output<<usr<<endl;
                output<<pass<<endl;
                output<<type<<endl;
                username = usr;
                password = pass;
            }
            else{
                output<<u<<endl;
                output<<p<<endl;
                output<<t<<endl;
            }
        }
        output.close();
        input.close();
        remove("users.xyz");
        rename("users_tmp.xyz","users.xyz");
    }
    bool new_account(string t = "student"){
        ofstream users;
        users.open("users.xyz",ios::app);
        input:
        cin.ignore();
        print_with_delay("\t\tUsername = ",40,false);
        cin>>username;
        if(!check_username(username)){
            print_with_delay("\t\t\tUSERNAME ALREADY EXIST");
            goto input;
        }
        cin.ignore();
        print_with_delay("\t\tPassword = ",40,false);
        password = passwd_enter();
        type = t;
        users<<username<<endl<<password<<endl<<type<<endl;
        fill_details(*this);
        return true;
    }
    void change_username(){
        string usr;
        if(!authenticate()){
            print_with_delay("\n\t\t\tAUTHENTICATION FAILED\n");
            return;
        }
        input:
        print_with_delay("\n\t\t\tNew Username = ",40,false);
        cin>>usr;
        if(!check_username(usr)){
            print_with_delay("\t\t\tUSERNAME ALREADY EXIST\n");
            goto input; 
        }
        update_file(usr,password);
    }
    void change_password(){
        string pass1,pass2;
        if(!authenticate()){
            print_with_delay("\n\t\t\tAUTHENTICATION FAILED\n");
            return;
        }
        input:
        print_with_delay("\n\t\t\tNew Password = ",40,false);
        pass1 = passwd_enter();
        print_with_delay("\n\t\t\tRetype New Password = ",40,false);
        pass2 = passwd_enter();
        if(pass1 != pass2){
            goto input;
        }
        update_file(username,pass1);
    }
    bool authenticate() const{
        string usrnm,passwd;
        print_with_delay("\t\t\tusername = ",40,false);
        cin>>usrnm;
        cin.ignore();
        print_with_delay("\t\t\tpassword = ",40,false);
        passwd = passwd_enter();
        if(usrnm==username && passwd==password){
            return true;
        }
        else{
            return false;
        }
    }
    bool check_username(string &s) const{
        ifstream input("users.xyz");
        string l1;
        while(getline(input,l1)){
            if(l1==s){
                input.close();
                return false;
            }
            getline(input,l1);
            getline(input,l1);
        }
        input.close();
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
            print_with_delay("*",40,false);
        }
        return passwd;
    }
    string return_type(){
        return type;
    }
    string return_type(string user){
        ifstream input;
        string l1;
        input.open("users.xyz");
        while(getline(input,l1)){
            if(l1==user){
                getline(input,l1);
                getline(input,l1);
                return l1;
            }
            getline(input,l1);
            getline(input,l1);
        }
        input.close();
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
        print_with_delay("\t\t\tExamination = ",40,false);
        getline(cin,session);
        aaa:
        print_with_delay("\t\t\tStudents Username = ",40,false);
        cin>>user_name;
        if(check_username(user_name) || return_type(user_name)!="student"){
            print_with_delay("\nERROR\n");
            goto aaa;
        }
        cin.ignore();
        print_with_delay("\t\t\tMarks in different subjects :-\n");
        print_with_delay("\t\t\tMath = ",40,false);
        cin>>math;
        print_with_delay("\t\t\tScience = ",40,false);
        cin>>science;
        print_with_delay("\t\t\tComputer = ",40,false);
        cin>>computer;
        print_with_delay("\t\t\tEnglish = ",40,false);
        cin>>english;
        print_with_delay("\t\t\tSocial = ",40,false);
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
        string tmp_line;
        string filename = user_name;
        filename += ".txt";
        filename = "results/" + filename;
        res.open(filename,ios::app);
        old.open(filename);
        while(getline(old,tmp_line)){
            if(tmp_line == "Examination = " + session){
                print_with_delay("Result Already Exist Of The Exam\n");
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
    ofstream data;
    string name,address,phone,DOB,position,DOJ;
    int roll;
    string filename = a.username;
    filename += ".txt";
    filename = "users/" + filename;
    data.open(filename);
    print_with_delay("\n\t\t\tfill the following details\n");
    print_with_delay("\t\t\tName = ",40,false);
    getline(cin,name);
    if(a.return_type()=="student"){
        print_with_delay("\t\t\tRoll no = ",40,false);
        cin>>roll;
        cin.ignore();
    }
    else if(a.return_type()=="teacher"){
        print_with_delay("\t\t\tEmployee no = ",40,false);
        cin>>roll;
        cin.ignore();
    }
    print_with_delay("\t\t\tAddress = ",40,false);
    getline(cin,address);
    print_with_delay("\t\t\tPhone no = ",40,false);
    cin>>phone;
    cin.ignore();
    print_with_delay("\t\t\tDate of Birth = ",40,false);
    getline(cin,DOB);
    if(a.return_type()=="teacher"){
        print_with_delay("\t\t\tPosition = ",40,false);
        getline(cin,position);
        print_with_delay("\t\t\tDate of joining = ",40,false);
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
bool yes_no(){
    char c;
    c = getch();
    if(c == 'Y' || c == 'y'){
        return true;
    }
    else{
        return false;
    }
    cout<<endl;
}
string decrypt(string &in,string &k){
    string decrypted = in;
    for (int i = 0; i < in.size(); i++) {
        decrypted[i] = in[i] ^ k[i % k.size()];
    }
    return decrypted;
}
string encrypt(string &in, string &k) {
    string encrypted = in;
    for (int i = 0; i < in.size(); i++) {
        encrypted[i] = in[i] ^ k[i % k.size()];
    }
    return encrypted;
}
void decrypt_and_create(string input,string output){
    string line;
    string key = "333";
    ifstream f1(input);
    ofstream f2(output);
    while(getline(f1,line)){
        f2<<decrypt(line,key)<<endl;
    }
    f2.close();
    f1.close();
}
void encrypt_and_delete(string input,string output){
    string line;
    string key = "333";
    ifstream f1(input);
    ofstream f2(output);
    while(getline(f1,line)){
        f2<<encrypt(line,key)<<endl;
    }
    f2.close();
    f1.close();
    remove(input.c_str());
}
void store_cookies(account &a,bool option){
    ofstream cookie;
    cookie.open("cookie.dat");
    string key="111";
    if(option){
        cookie<<encrypt(a.username,key)<<endl;
        cookie<<encrypt(a.password,key)<<endl;
        cookie<<encrypt(a.type,key)<<endl;
    }
    else{
        cookie<<"";
    }
    cookie.close();
}
void read_file(string filename,bool showline=false,bool wait=true,int start_line = 0,int end_line = 0,int tab=0){
    int line=1;
    ifstream data(filename);
    if (!data.is_open()) {
        cout << "\t\t\tError: Could not open user detail file." << endl;
        return;
    }
    string s;
    while(getline(data, s)){
        if(start_line){
            start_line--;
            continue;
        }
        for(int i=0;i<tab;i++){
            cout<<"\t";
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
    read_file(filename,false,true,0,0,3);
}
bool handle_account(account &a){
    int c;
    int attempt=3;
    aa:
    print_with_delay("\t\t\tWELCOME TO LOGIN PAGE\n");
    print_with_delay("\t\t\t1.login\n\t\t\t2.register\n\t\t\tchoice=",40,false);
    cin>>c;
    switch(c){
        case 1:
        if(a.load()){
            return true;
        }
        print_with_delay("\nERROR ACCOUNT NOT FOUND WITH THOSE DETAILS\n");
        break;
        case 2:
        char c;
        int p;
        print_with_delay("\t\t\tare you teacher (y/n)= ",40,false);
        if(yes_no()){
            print_with_delay("Admin Pass = ",40,false);
            cin>>p;
            if(p==ADMIN_PASS){
                a.new_account("teacher");
            }
        }
        else{
            a.new_account();
        }
        return true;
        break;
    }
    attempt--;
    if(attempt!=0){
        goto aa;
    }
    return false;
}
void result_list(account &a){
    string s;
    int no = 1,choice;
    int line = 0,string=0;
    vector<int> lines_no;
    ifstream r("results/"+a.return_username()+".txt");
    if(!r){
        print_with_delay("\t\t\tNO RESULT DATA FOUND");
        r.close();
        return;
    }
    while(r>>s){
        if(s == "Examination"){
            cout<<"\t\t\t"<<no<<".";
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
    print_with_delay("\t\t\tchoice = ",40,false);
    cin>>choice;
    if(choice>no || choice<1){
        print_with_delay("\n\t\t\tERROR\n");
        goto aaa;
    }
    read_file("results/"+a.return_username()+".txt",false,false,lines_no[choice-1],(lines_no.size()>choice)?lines_no[choice]:999,3);
}
void write_file(string filename){
    fstream ano;
    int op;
    aa:
    print_with_delay("\t\t\tOpen in :-\n\t\t\t1.Overwrite\n\t\t\t2.Append\n\t\t\tchoice=",40,false);
    if(!filesystem::exists(filename)){
        cout<<"1";
    }
    else{
        cin>>op;
    }
    if(op==1){
        ano.open(filename,ios::out);
    }
    else if(op==2){
        ano.open(filename,ios::app);
    }
    else{
        print_with_delay("\n\t\t\tinvalid option\n");
        goto aa;
    }
    cout << "\x1B[2J\x1B[H";
    string s;
    int line_no = 1;
    cin.ignore();
    print_with_delay("\t\t\tEnter line empty to save :-");
    while(true){
        cout<<"\t\t\t"<<line_no<<".";
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
    print_with_delay("\t\t\tchoose one of following subjects:-\n");
    print_with_delay("\t\t\t1.math");
    print_with_delay("\t\t\t2.science");
    print_with_delay("\t\t\t3.computer");
    print_with_delay("\t\t\t4.english");
    print_with_delay("\t\t\t5.social");
    print_with_delay("\t\t\tchoice=",40,false);
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
        print_with_delay("\n\n\n");
        goto aa;
    }
}
void update_material(string filename){
    fstream stdy;
    stdy.open("study_materials.txt",ios::app);
    stdy<<filename<<endl;
    stdy.close();
}
bool student_menu(account &a){
    int choice,c;
    print_with_delay("\t\t\t\tWELCOME TO AMRITSAR LMS SOFTWARE\n\n");
    print_with_delay("\t\t\t\t\tANNOUNCEMENT");
    print_with_delay("\t\t\t----------------------------------------\n");
    read_file("announcement.txt",false,false,0,0,3);
    print_with_delay("\t\t\t-----------------------------------------\n");
    print_with_delay("\n\t\t\t1.Study Materials");
    print_with_delay("\t\t\t2.View Result");
    print_with_delay("\t\t\t3.Account Manager");
    print_with_delay("\t\t\t4.Logout");
    print_with_delay("\t\t\tchoice=",40,false);
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
        {
            string tmp;
            int choice,line=1;
            read_file("study_materials.txt",true,false,0,0,3);
            print_with_delay("\t\t\tchoice = ",40,false);
            cin>>choice;
            ifstream st("study_materials.txt");
            while(getline(st,tmp)){
                if(line==choice){
                    break;
                }
                line++;
            }
            cout << "\x1B[2J\x1B[H";
            read_file(tmp,false,true,0,0,3);
            break;
        }
        case 2:
        result_list(a);
        //read_file("results/"+a.return_username()+".txt");
        break;
        case 3:
        print_with_delay("\n\n\t\t\tACCOUNT MANAGER\n");
        print_with_delay("\t\t\t1.View Details");
        print_with_delay("\t\t\t2.Change UserName");
        print_with_delay("\t\t\t3.Change Password");
        print_with_delay("\t\t\tchoice=",40,false);
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
            print_with_delay("\n\t\t\tINVALID OPTION\n");
        }
        break;
        case 4:
        print_with_delay("\t\t\tDo you want to stay logged in ? [y/n] = ",40,false);
        if(yes_no()){
            store_cookies(a,true);
        }
        else{
            store_cookies(a,false);
        }
        return false;
        break;
    }
    getch();
    return true;
}
bool teacher_menu(account &a){
    int choice,c;
    result r;
    print_with_delay("\t\t\t\tWELCOME TO AMRITSAR LMS SOFTWARE\n");
    print_with_delay("\t\t\t1.Announcement");
    print_with_delay("\t\t\t2.Set Result");
    print_with_delay("\t\t\t3.Upload Study Material");
    print_with_delay("\t\t\t4.Account Manager");
    print_with_delay("\t\t\t5.Logout");
    print_with_delay("\t\t\tchoice=",40,false);
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
            cout << "\x1B[2J\x1B[H";        
            {
            int option;
            string filename,subject,path;
            print_with_delay("\t\t\tChoose One of following ways to provide study material:-\n");
            print_with_delay("\t\t\t1.Write in Editor");
            print_with_delay("\t\t\t2.Give Path of already written material");
            print_with_delay("\t\t\tchoice=",40,false);
            cin>>option;
            cin.ignore();
            switch(option){
                case 1:
                subject=choose_subject();
                cin.ignore();
                print_with_delay("\t\t\tchapter_name=",40,false);
                cin>>filename;
                cin.ignore();
                if(!filesystem::exists("study_material/"+subject+"/"+filename+".txt")){
                    update_material("study_material/"+subject+"/"+filename+".txt");
                }
                write_file("study_material/"+subject+"/"+filename+".txt");
                break;
                case 2:
                input:
                print_with_delay("\n\t\t\tProvide Full Path of the source file :-\n",40,false);
                print_with_delay("\t\t\tpath=",40,false);
                cin>>path;
                if(!filesystem::exists(path)){
                    cout<<"\t\t\tINVALID PATH";
                    goto input;
                }
                cin.ignore();
                subject = choose_subject();
                print_with_delay("\t\t\tchapter_name=",40,false);
                cin>>filename;
                cin.ignore();
                filename = "study_material/"+subject+"/"+filename+".txt";
                if (rename(path.c_str(),filename.c_str()) == 0) {
                    cout << "File moved successfully." << endl;
                    update_material(filename);
                } 
                else {
                    cout << "\t\t\tError: Unable to move the file." << endl;
                }
                break;
                default:
                print_with_delay("\n\t\t\tERROR INVALID OPTION\n");
            }
        }
        break;
        case 4:
        print_with_delay("\n\n\t\t\tACCOUNT MANAGER\n");
        print_with_delay("\t\t\t1.View Details");
        print_with_delay("\t\t\t2.Change UserName");
        print_with_delay("\t\t\t3.Change Password");
        print_with_delay("\t\t\tchoice=",40,false);
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
            print_with_delay("\n\t\t\tINVALID OPTION\n",40,false);
        }
        break;
        case 5:
        print_with_delay("\t\t\tDo you want to stay logged in ? [y/n] = ",40,false);
        if(yes_no()){
            store_cookies(a,true);
        }
        else{
            store_cookies(a,false);
        }
        return false;
        break;
    }
    getch();
    return true;
}
bool check_cookies(account &a){
    ifstream cookie;
    string u,p,t;
    string key="111";
    cookie.open("cookie.dat");
    getline(cookie,u);getline(cookie,p);getline(cookie,t);
    u = decrypt(u,key);
    p = decrypt(p,key);
    t = decrypt(t,key);
    if(a.load(u,p)){
        print_with_delay("LOGGED IN USING COOKIE\n");
        cout<<"username = "<<u<<endl;
        cout<<"type = "<<t<<endl;
        getch();
        cookie.close();
        return true;
    }
    cookie.close();
    return false;
}
int main(){
    account a;
    decrypt_and_create(DATABASE,"users.xyz");
    cout << "\x1B[2J\x1B[H";
    if(check_cookies(a) || handle_account(a)){
        while(true){
            cout << "\x1B[2J\x1B[H";
            if(a.return_type()=="student"){
                if(!student_menu(a)){
                    break;
                }
            }
            else if(a.return_type()=="teacher"){
                if(!teacher_menu(a)){
                    break;
                }
            }
        }
    }
    encrypt_and_delete("users.xyz",DATABASE);
}