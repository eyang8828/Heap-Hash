/*
 * Author: Eddie Yang
 * Project: PQueue
 * Purpose: to create a PQueue class that implemented heap 
 *        that'll received item with their priority, and 
 *        pop them in respect to their value and priority.
 * Notes: not sure if we should output the tree for the normal
 *        run, cause 100 output means that we had to output it
 *        100 times.
 */
#ifndef PQUEUE_H
#define PQUEUE_H
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "heap.h"
using namespace std;

template <typename T>
struct info{
    T item;
    int priority;
    
    info(){
        item =0;
        priority=0;
    };
    info(T i, int p){
        item = i;
        priority = p;
    };
    
    friend ostream& operator <<(ostream& outs, const info<T>& print_me){
        outs<<"[ "<<print_me.item<<" ]  -- priority--"<<print_me.priority<<endl;
        return outs;
    };
    
    friend bool operator <(const info<T>& lhs, const info<T>& rhs){
        bool flag;
        if(lhs.item == rhs.item){
            flag =  lhs.priority<rhs.priority;
        }else{
            flag = lhs.item < rhs.item;
        }
        return flag;
    };
};


template <typename T>
class PQueue
{
public:
    PQueue();

    bool insert(const T& value, int p);
    T Pop();

    bool is_empty() const{return heap.is_empty();}
    int size() const{return heap.size();}
    void print_tree() const{heap.print_tree(0);}
    friend ostream& operator <<(ostream& outs, const PQueue<T>& print_me){
       print_me.print_tree();
       return outs;
    }


private:
    heap<info<T> > heap;

};

template<class T> PQueue<T>::PQueue(){
};


template<class T> bool PQueue<T>::insert(const T &value, int p){
    info<T> in= info<T>(value,p);
    heap.insert(in);
    return true;
}

template<class T> T PQueue<T>::Pop(){
    info<T> temp = heap.Pop();
    return temp.item;
}



#endif // PQUEUE_H