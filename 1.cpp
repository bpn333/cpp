// Your First C++ Program

#include <iostream>
using namespace std;
int main() {
int s;
cout<<"size :";
cin>>s;
int n[s],i,j;
char name[10][s];
for(i=1;i<=s;i++)
{
cout<<i<<".Roll :";
cin>>n[i];
cout<<"Name :";
cin>>name[i];
cout<<"\n\n\n";
}
for(j=1;j<=s;j++)
{
cout<<n[j]<<"."<<name[j];//<<"\n";
}
}
