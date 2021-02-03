#include "heap.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;;

int main(){
    //setting up for the function
    srand(time(NULL));
    heap<int> h;
    char ans = ' ';

    cout<<"is the an max heap or min heap"<<endl;
    cout<<"enter 0 for min and 1 for max"<<endl;
    int i;
    cin>>i;
    if(i == 0){
        h.set_min_or_max(false);
    }

    //while the user's answer is not x, kept the function going
    while (tolower(ans) != 'x'){
        
        cout<<"[R]andom  [I]nsert  [P]op  e[X]it:";
        cin >> ans ;
        cout<<endl;
        switch (tolower(ans)){

            //case random : get a random number from 1~99 and insert to the tree 
            case 'r':{
                int num = rand()%100 +1;

                cout<<"-- Inserting "<<num<<endl;
                cout<<"item: "<<num<<":0"<<endl;
                h.insert(num);
                cout<<h;
                break;
            }

            //case insert : ask for a number to insert and insert to the tree
            case 'i':{
                int num;
                cout<< "what number?";
                cin >> num;

                cout<<"-- Inserting "<<num<<endl;
                cout<<" item: "<<num<<":0"<<endl;
                h.insert(num);
                cout<<h;
                break;
            }

            //case clear : clear the whole tree.
            case 'p':{
                int num = h.Pop();
                cout<<"The number that's being poped : "<<num<<endl;
                cout<<h;
                break;
            }

            //case exit : ans = x ending program
            case 'x':{
                cout<<"ending program~";
                break;
            }

            //if the user answer anything invalid, we tell them
            default:{
                cout<<"please enter a valid input";
                break;
            }
        };

        cout<<endl<<string(32,'=')<<endl;
    }
}