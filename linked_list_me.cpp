#include<iostream>
#include<conio.h>
struct node
{
    int item;
    node *ptr;
};
void create_node(node *&hptr){
    node *nptr = new node;
    nptr->ptr = nullptr;
    std::cout<<"value=";
    std::cin>>nptr->item;
    if(hptr==nullptr){
        hptr=nptr;
    }
    else{
        node *tmptr = hptr;
        while(tmptr->ptr!=nullptr){
            tmptr=tmptr->ptr;
        }
        tmptr->ptr=nptr;
        tmptr=nptr;
    }
}
void display(node *&hptr){
    node *tmptr = hptr;
    while(tmptr!=nullptr){
        std::cout<<tmptr->item<<" ";
        tmptr=tmptr->ptr;
    }
}
void insert(node *&hptr){
    int pos,count=0;
    bool counter=false;
    std::cout<<"index=";
    std::cin>>pos;
    if(pos<=0){
        std::cout<<"\nERROR\n";
        return;
    }
    node *nptr = new node;
    std::cout<<"value=";
    std::cin>>nptr->item;  
    node *tmptr = hptr;
    while(tmptr!=nullptr){
        count++;
        if(count==pos){
            counter=true;
            break;
        }
        tmptr=tmptr->ptr;
    }
    if(!counter){
        std::cout<<"\nOUT OF RANGE\n";
        return;
    }
    nptr->ptr=tmptr->ptr;
    tmptr->ptr=nptr;
}
void insert_start(node *&hptr){
    node *nptr = new node;
    std::cout<<"value=";
    std::cin>>nptr->item;    
    nptr->ptr = hptr;
    hptr = nptr;
}
void insert_end(node *&hptr){
    node *nptr = new node;
    std::cout<<"value=";
    std::cin>>nptr->item; 
    nptr->ptr = nullptr; 
    node *tmptr = hptr;  
    while(tmptr->ptr!=nullptr){
        tmptr=tmptr->ptr;
    }
    tmptr->ptr = nptr;
}
void del(node *&hptr){
    int pos,count=0;
    bool counter=false;
    std::cout<<"index=";
    std::cin>>pos;
    if(pos<=0){
        std::cout<<"\nERROR\n";
        return;
    }
    node *tmptr = hptr;
    while(tmptr->ptr!=nullptr){
        count++;
        if(count==pos){
            counter=true;
            break;
        }
        tmptr=tmptr->ptr;
    }
    if(!counter){
        std::cout<<"\nOUT OF RANGE\n";
        return;
    }
    node *eptr = tmptr->ptr;
    tmptr->ptr = eptr->ptr;
    delete eptr;
}
void del_start(node *&hptr){
    node *tmp=hptr;
    hptr=hptr->ptr;
    delete tmp;
}
void del_end(node *&hptr){
    node *tmptr = hptr;
    node *eptr;
    while(tmptr->ptr!=nullptr){
        eptr=tmptr;
        tmptr=tmptr->ptr;
    }
    eptr->ptr = nullptr;
    delete tmptr;
}
void search(node *&hptr){
    bool counter=false;
    int v,c=0;
    node *tmptr = hptr;
    std::cout<<"value=";
    std::cin>>v;
    while(tmptr!=nullptr){
        c++;
        if(tmptr->item==v){
            counter=true;
            break;
        }
        tmptr=tmptr->ptr;
    }
    if(counter){
        std::cout<<"\nItem Found at Index "<<c-1;
    }
    else{
        std::cout<<"\nItem Not Found";
    }
}
int main(){
    int n,c,choice;
    node *hptr = nullptr;
    std::cout<<"number of members:-";
    std::cin>>n;
    for(int i=0;i<n;i++){
        create_node(hptr);
    }
    bool run=true;
    int case_1=0,case_2=0,case_3=0,case_4=0;
    do {
        std::cout<<"\t\tchoose one of the following options\n";
        std::cout<<"1.insert\n";
        std::cout<<"2.delete\n";
        std::cout<<"3.display\n";
        std::cout<<"4.search\n";
        std::cout<<"5.exit\n";
        std::cout<<"choice:-"; 
        std::cin>>c;
        switch(c){
            case 1:
            case_1++;
            std::cout<<"\n1.any position\n2.start\n3.end\n4.choice=";
            std::cin>>choice;
            if(choice==1){
                insert(hptr);
            }
            else if(choice==2){
                insert_start(hptr);
            }
            else if(choice==3){
                insert_end(hptr);
            }
            std::cout<<"\nDATA MODIFIED\n";
            display(hptr);
            break;

            case 2:
            case_2++;
            std::cout<<"\n1.any position\n2.start\n3.end\n4.choice=";
            std::cin>>choice;
            if(choice==1){
                del(hptr);
            }
            else if(choice==2){
                del_start(hptr);
            }
            else if(choice==3){
                del_end(hptr);
            }
            std::cout<<"\nDATA MODIFIED\n";
            display(hptr);
            break;

            case 3:
            case_3++;
            display(hptr);
            getch();
            break;

            case 4:
            case_4++;
            search(hptr);
            getch();
            break;

            case 5:
            run=false;
            std::cout<<"\nYOUR ACTIVITY:-\nInsert = "<<case_1<<" times\nDelete = "<<case_2<<" times\nDisplay = "<<case_3<<" times\nSearch = "<<case_4<<" times\n";
            std::cout<<"\nTHANK YOU\n";
            break;
        }
    }while(run);
    return 0;
}