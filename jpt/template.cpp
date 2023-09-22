#include<iostream>
#include<string>
using namespace std;
template <typename T>
T add(T a,T b){
    return a+b;
}
int main(){
    cout<<add((string)"bpn ",(string)"is decent ")<<add((string)"guy ",(string)"with ")<<add(0,0)<<add((string)" or",(string)" ")<<add(0.000,0.0001)<<add((string)"% things he like",(string)"");
}