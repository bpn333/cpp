#include<iostream>

class student{
	public:
	std::string name;
	int age;

	void read(){
		std::cout<<"name="<<name<<"\n";
		std::cout<<"age="<<age<<"\n";
	}
	student(){}  //default something

	student(std::string Name ,int Age){
		name=Name;
		age=Age;
	}
};

int main(){
	student stud[100]{};
	std::string name;
	int age,n,i;
	std::cout<<"no.:-";
	std::std::cin>>n;

	for(i=0;i<=n;i++){
	std::cout<<"name=";
	std::std::cin>>name;
	std::cout<<"age=";
	std::std::cin>>age;
	stud[i]=student(name,age); //std-_-
	}
	std::cout<<"\n\n\n";

	for(i=0;i<=n;i++){
		std::cout<<stud[i].name<<" "<<stud[i].age<<std::endl;
	}
	return 0;
}
