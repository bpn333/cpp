#include<iostream>
using namespace std;
class date{
    int day;
    int month;
    int year;
    public:
    bool check_day_limit(){
        bool c = (month==1)&&(day>31);
        c = c || (year%4==0)&&(month==2)&&(day>29);
        c = c || (year%4!=0)&&(month==2)&&(day>28);
        c = c || (month==3)&&(day>31);
        c = c || (month==4)&&(day>30);
        c = c || (month==5)&&(day>31);
        c = c || (month==6)&&(day>30);
        c = c || (month==7)&&(day>31);
        c = c || (month==8)&&(day>31);
        c = c || (month==9)&&(day>30);
        c = c || (month==10)&&(day>31);
        c = c || (month==11)&&(day>30);
        c = c || (month==12)&&(day>31);
        return c;
    }
    bool check_month_limit(){
        return month>12;
    }
    date(int d,int m,int y):day(d),month(m),year(y){}
    void inc(int d,int m,int y){
        month += m;
        year += y;
        if(check_month_limit()){
            year += (month-1)/12;
            month = (month-1)%12+1;
        }
        while(d){
            day += 1;
            if(check_day_limit()){
                day = 1;
                month += 1;
            }  
            if(check_month_limit()){
                year += (month-1)/12;
                month = (month-1)%12+1;
            }
            d--;
        }
    }
    void display(){
        cout<<day<<" "<<month<<" "<<year<<endl;
    }
};
int main(){
    int d,m,y;
    cout<<"day = ";
    cin>>d;
    cout<<"month = ";
    cin>>m;
    cout<<"year = ";
    cin>>y;
    date dat(d,m,y);
    if(dat.check_day_limit() || dat.check_month_limit()){
        cout<<"\nInvalid date\n";
        return 0;
    }
    cout<<"Give date to increment with :-\n";
    cout<<"day = ";
    cin>>d;
    cout<<"month = ";
    cin>>m;
    cout<<"year = ";
    cin>>y;
    dat.inc(d,m,y);
    dat.display();
}