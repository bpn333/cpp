#include <iostream>
#include<iomanip>
using namespace std;
struct process{
    int pid;
    int burst_time;
    int arrival_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
};
class processes{
    process *p;
    int size;
    float avg_waiting_time;
    float avg_TAT;
    int end_time;
    public:
    processes(int s){
        p = new process[s];
        size = s;
    }
    void input_datas(){
        for(int i=0; i<size; i++){
            cout<<"process "<<i+1<<endl;
            cout<<"Burst Time : ";
            cin>>p[i].burst_time;
            cout<<"Arrival Time : ";
            cin>>p[i].arrival_time;
            p[i].pid = i;
        }
    }
    void arrange_ascending(){
        for(int i=0;i<size;i++){
            for(int j=i+1;j<size;j++){
                if(p[i].arrival_time > p[j].arrival_time){
                    process tmp = p[i];
                    p[i] = p[j];
                    p[j] = tmp;
                }
            }
        }
    }
    void calculate(){
        arrange_ascending();
        int time = 0;
        avg_TAT = 0;
        avg_waiting_time = 0;
        for(int i=0; i<size; i++){
            time += p[i].burst_time;
            p[i].completion_time = time;
            p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
            p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
            avg_TAT += p[i].turn_around_time;
            avg_waiting_time += p[i].waiting_time;
        }
        avg_TAT /= size;
        avg_waiting_time /= size;
        end_time = time;
    }
    void display_table(){
        cout<<"process"<<setw(20)<<"arrival time"<<setw(20)<<"burst time"<<setw(20)<<"completion time"<<setw(20)<<"turn around time"<<setw(20)<<"waiting time"<<endl;
        for(int i=0;i<size;i++){
            cout<<p[i].pid<<setw(20)<<p[i].arrival_time<<setw(20)<<p[i].burst_time<<setw(20)<<p[i].completion_time<<setw(20)<<p[i].turn_around_time<<setw(20)<<p[i].waiting_time<<endl;
        }
        cout<<"\n\nAvg TAT = "<<avg_TAT<<endl;
        cout<<"Avg waiting time = "<<avg_waiting_time<<endl;
        cout<<"End time = "<<end_time<<endl;
    }
    ~processes(){
        delete[] p;
    }
};
int main(){
    int n;
    cout<<"How many process do you have :";
    cin>>n;
    processes p(n);
    p.input_datas();
    p.calculate();
    p.display_table();
}