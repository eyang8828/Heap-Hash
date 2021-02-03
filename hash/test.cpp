#include "open_hash.h"
#include "double_hash.h"
#include "chained_hash.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;
struct record{
    int _key;
    double _value;

    record(int k=0, double v=0):_key(k), _value(v){};
    friend bool operator ==(const record& left, const record& right){
        return (left._key == right._key);
    };
    friend ostream& operator <<(ostream& outs, const record& print_me){
        outs<<setfill(' ')<<setw(5)<<print_me._key<<':'<<setw(4)<<print_me._value;
        return outs;
    };
};

template<class T>
void test_hash_table_random (T hash, int number, string str);

template<class T>
void test_hash_table_interactive(T hash, string str);

int main(){
    cout<<endl<<endl<<endl<<"----------------------"<<endl<<endl<<endl;
    const bool RANDOM_CHAINED = false;
    const bool RANDOM_OPEN = false;
    const bool RANDOM_DOUBLE = false;
    const bool INTERACTIVE_OPEN = true;
    const bool INTERACTIVE_CHAINED = false;
    const bool INTERACTIVE_DOUBLE = false;
    

    if (INTERACTIVE_OPEN){
        cout<<"-------  INTERACTIVE TESTS ---------------------------"<<endl;
        open_hash<record> open;
        test_hash_table_interactive(open, "open_hash_table" );
    }

    if (INTERACTIVE_DOUBLE){
        cout<<"-------  INTERACTIVE TESTS ---------------------------"<<endl;
        open_hash<record> d_hash;
        test_hash_table_interactive(d_hash, "double_hash_table" );
    }

    // if (INTERACTIVE_CHAINED){
    //     cout<<"-------  INTERACTIVE TESTS ---------------------------"<<endl;
    //     chained_hash<record> chained;
    //     test_hash_table_interactive(chained, "chained_hash_table" );
    // }

    if (RANDOM_CHAINED){
        //----------- RANDOM TEST ------------------------------
        // . . . . . .  Chained Hash Table . . . . . . . . . . .;
        chained_hash<record> c_table;
        test_hash_table_random(c_table, 2500, "chained_hash_table<record>");
        cout<<c_table<<endl;
    }

    if (RANDOM_OPEN){
        //----------- RANDOM TEST ------------------------------
        //. . . . . .  Simple Hash Table . . . . . . . . . . .;
        open_hash<record> h_table;
        test_hash_table_random(h_table, 500, "hash_table<record>");
        cout<<h_table<<endl;
    }

    // if (RANDOM_CHAINED){
    //     //----------- RANDOM TEST ------------------------------
    //     //. . . . . .  Simple Hash Table . . . . . . . . . . .;
    //     open_hash<record> chained;
    //     test_hash_table_random(chained, 500, "hash_table<record>");
    //     cout<<chained<<endl;
    // }

    cout<<endl<<endl<<endl<<"---------------------------------"<<endl;

}

template<class T>
void test_hash_table_random (T hash, int number, string str){
    srand(time(NULL));
    cout<<"***RANDOM TEST***    "<<str<<endl;
    cout<<string(24,'=')<<endl;
    cout<<"Index--Key--Value\n\n";
    for( int i = 0; i < number; i ++){
        record temp = record(rand()%999+1,i);
        hash.insert(temp);
    }
}

template<class T>
void test_hash_table_interactive(T hash, string str){
    
    char ans = ' ';

    while (tolower(ans) != 'x'){
        
        cout<<"[S]ize() [I]nsert [R]andom [D]elete [F]ind value [?]exists?   e[X]it  :";
        cin >> ans ;
        cout<<endl;
        switch (tolower(ans)){

            //case random : get a random number from 1~99 and insert to the tree 
            case 'r':{
                int num = rand()%9999 + 1;
                int val = rand()%9999 + 1;
                record r = record(num,val);
                cout<<"-- Inserting "<<r<<endl;
                hash.insert(r);
                cout<<hash;
                break;
            }

            //case insert : ask for a number to insert and insert to hash
            case 'i':{
                int num;
                int val;
                cout<< "key ? \n";
                cin >> num;
                cout<<"val ? \n";
                cin>>val;
                record r = record(num,val);

                cout<<"-- Inserting "<<r<<endl;
                hash.insert(r);
                cout<<hash;
                break;
            }

            //case remove : remove the record that the user asked
            case 'd':{
                int num;
                cout<<"what number?";
                cin>>num;

                hash.remove(num);
                cout<<hash;
                break;
            }

            //case search : ask for number to search, show the result
            case 'f':{
                int num;
                cout<<"what number to search ?";
                cin>> num;
                cout<<endl;

                bool found;
                record r;

                hash.find(num,found,r);


                if(found){
                    cout<<"item is found. "<<r<<endl;
                    cout<<hash;
                }else{
                    cout<<"item not found."<<endl;
                    cout<<hash;
                }
                break;
            }
            case '?':{
                int num;
                cout<<"what number to find ?";
                cin>> num;
                cout<<endl;

                bool found;
                record r;

                hash.find(num,found,r);
                if(found){
                    cout<<"record exist. "<<r<<endl;
                    cout<<hash;
                }else{
                    cout<<"record not found."<<endl;
                    cout<<hash;
                }

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