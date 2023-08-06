#include<iostream>
#include<string>
class test{
    std::string s="\nThis is secret shhhhh...";
    public:
    static int c;    //everyone share same thing
    test(){
        c++;
    }
    friend void hi(test &obj);  //friend function can get private member
};
void hi(test &obj){
    std::cout<<"\nhellow kids";
    std::cout<<obj.s;
}
int test::c=0;
int main(){
    test a,b,c;
    std::cout<<a.c<<b.c<<c.c;  //333 output
    hi(a);
}