// Your First C++ Program

#include <iostream>
using namespace std;
int main() {
int s;
cout<<"size :";
std::cin>>s;
int n[s],i,j;
char name[10][s];
for(i=1;i<=s;i++)
{
cout<<i<<".Roll :";
std::cin>>n[i];
cout<<"Name :";
std::cin>>name[i];
cout<<"\n\n\n";
}
for(j=1;j<=s;j++)
{
cout<<n[j]<<"."<<name[j];//<<"\n";
}
}
