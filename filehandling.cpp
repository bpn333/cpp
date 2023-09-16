#include<iostream>
#include<fstream>
using namespace std;
int main(){
    ofstream test;
    test.open("data.txt");
    test<<"test plz work goddam";
    test.close();
    //system("cat data.txt");
}