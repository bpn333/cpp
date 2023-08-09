#include <iostream>
using namespace std;
int sleep(){
int k,d;
d=0;
for(k=1;k<=10000000;k++)
{
d=d+k;
}
return 0;
}

int main(){
int i,j,n;
cout<<"num :";
std::cin>>n;
for(i=1;i<=n;i++)
{
for(j=1;j<=i;j++)
{
cout<<i<<",";;
}
sleep();
}
}
