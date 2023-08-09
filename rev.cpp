#include<iostream>
int main() {
int n,r,a;
std::cout<<"enter a number :";
std::std::cin>>n;
a=0;
while(n!=0)
{
r=n%10;
a=a*10+r;
n=n/10;
}
std::cout<<"reverse of number :"<<a<<"\n";
}
