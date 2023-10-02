#include<iostream>
#include<conio.h>
#include<thread>
#include<chrono>
#define WIDTH 80
#define HEIGHT 20
#define DELAY_DURATION 100
#define DELAY this_thread::sleep_for(chrono::milliseconds(DELAY_DURATION));
using namespace std;
struct snake{
    char head = '@';
    int x = 0;
    int y = 0;
    int dir[2]={0,0};
} s;
struct tail{
    int x = 0;
    int y = 0;
} *t;
struct fruit{
    int x = 5;
    int y = 5;
    char icon = '0';
} f;
bool gameover = false;
int tail_length = 0;
void display(){
    cout << "\x1B[2J\x1B[H";
    (s.x>WIDTH)?s.x=1:0;
    (s.x<1)?s.x=WIDTH:0;
    (s.y>HEIGHT)?s.y=1:0;
    (s.y<1)?s.y=HEIGHT:0;
    for(int y=HEIGHT;y>=1;y--){
        for(int x=1;x<=WIDTH;x++){
            bool tail_present=false;
            for(int i=0;i<tail_length;i++){
                if(t[i].x == x && t[i].y == y){
                    tail_present = true;
                    break;
                }
            }
            if(x==s.x && y==s.y){
                cout<<s.head;
            }
            else if(tail_present){
                cout<<"*";
            }
            else if(x==f.x && y==f.y){
                cout<<f.icon;
            }
            else if((x==WIDTH || x==1) && (y==1 || y==HEIGHT)){
                cout<<"#";
            }
            else if(x==WIDTH || x==1){
                cout<<"|";
            }
            else if(y==1 || y==HEIGHT){
                cout<<"-";
            }
            else{
                cout<<" ";
            }
        }
        cout<<"\n";
    }
}
char input(){
    char c;
    if(kbhit()){
        c = getch();
    }
    else{
        c = '\0';
    }
    return c;
}
void get_direction(char c){
    if(c=='w'){
        s.dir[1] = 1;
        s.dir[0] = 0;
    }
    else if(c=='s'){
        s.dir[1] = -1;
        s.dir[0] = 0;
    }
    else if(c=='a'){
        s.dir[1] = 0;
        s.dir[0] = -1;
    }
    else if(c=='d'){
        s.dir[1] = 0;
        s.dir[0] = 1;
    }
    else if(c=='q'){
        gameover = true;
    }
}
void move_direction(){
    if(s.dir[0]){
        s.x += s.dir[0];
    }
    else if(s.dir[1]){
        s.y += s.dir[1];
    }
}
void add_tail(){
    tail *tmp = new tail[++tail_length];
    for(int i=1;i<tail_length;i++){
        tmp[i].x = t[i-1].x;
        tmp[i].y = t[i-1].y;
    }
    tmp[0].x = s.x;
    tmp[0].y = s.y;
    delete[] t;
    t = tmp;
}
void logic(){
    if(s.x == f.x && s.y == f.y){
        f.x = (rand() % (WIDTH-8)) + 3;
        f.y = (rand() % (HEIGHT-8)) + 3;
        add_tail();
    }
}
void follow_tail(){
    if(!t){
        return;
    }
    for(int i=tail_length-1;i>0;i--){
        t[i].x = t[i-1].x;
        t[i].y = t[i-1].y;
    }
    t[0].x = s.x;
    t[0].y = s.y;
}
void debug_mode(){
    cout<<"snake position = "<<s.x<<","<<s.y<<endl;
    cout<<"fruit position = "<<f.x<<","<<f.y<<endl;
    cout<<"tail length = "<<tail_length<<endl;
    for(int i=0;i<tail_length;i++){
        cout<<"position = "<<t[i].x<<","<<t[i].y<<endl;
    }
}
int main(){
    char c;
    while(!gameover){
        DELAY
        display();
        c=input();
        logic();
        if(c!='\0'){
            get_direction(c);
        }
        follow_tail();
        move_direction();
    }
    debug_mode();
}