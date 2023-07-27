#include<iostream>
#include<string>  //i can also do same as c language but that may have risk of buffer overflow
class student{ //class
    protected: //data abstraction
    int serial_no;
    std::string name;
    int age;
    std::string address;
    
    public:
    void serial(){   //encapsulation
        std::cout<<serial_no<<std::endl;
    }
    virtual void print(){  
    std::cout<<name<<std::endl<<age<<std::endl<<address<<std::endl;
    }
    student(){} //default constructor no aggruments
    student(std::string name,int age,std::string address):name(name), age(age), address(address){}
};
class teacher:public student{   //inheritance
    protected:
    int salary;

    public:
    teacher():student(){}
    teacher(std::string name, int age, std::string address, int salary): student(name, age, address), salary(salary) {}
    void promote(){
        salary += 100;
    }
    void print() override{  //polymorphism
    std::cout<<name<<std::endl<<age<<std::endl<<address<<std::endl<<salary<<std::endl;
    }
};
int main(){
    student bipin("bipin",10,"nepal");  //object
    teacher ramesh("ramesh",22,"india",300);
    bipin.print();
    ramesh.print();
    //bipin.serial();
}