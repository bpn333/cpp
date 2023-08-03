#include<iostream>
struct student
{
   int roll;
};

int main(){
    student s1,*s2;
    s2=&s1;
    s1.roll = 19;
    std::cout<<s1.roll;
    std::cout<<s2->roll;
}