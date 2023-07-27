#include<iostream>
#include<vector>

int sum_digit(int n){
    int s=0;
    while(n!=0){
        s=n%10+s;
        n=n/10;
    }
    return s;
}

int main(){
    int n,i,total=0,new_total=0;
    std::cout<<"enter no of data :-";
    std::cin>>n;
    std::vector<int> arr(n),arr2(n);
    for(i=0;i<n;i++){
        std::cout<<"enter value of "<<(char)('a'+i)<<"= ";
        std::cin>>arr[i];
    }
    std::cout<<std::endl;
    for ( i = 0; i < n; i++)
    {
        total += arr[i];
    }
    for(i=0;i<n;i++){
        arr2[i]=total-arr[i];
        std::cout<<"sum excluding "<<(char)('a'+i)<<"= "<<arr2[i]<<std::endl;
    }
    std::cout<<std::endl;
    for ( i = 0; i < n; i++)
    {
        std::cout<<"for :-"<<(char)('a'+i)<<"\nold sum of digit = "<<sum_digit(arr[i])<<"\nnew sum of digit = "<<sum_digit(arr2[i]);
        if(sum_digit(arr2[i]>arr[i])){
            std::cout<<"\nnew sum is highest\n"<<std::endl;
        }
        else{
            std::cout<<"\nold sum was highest\n"<<std::endl;
        }
    }
}
