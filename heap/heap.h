/*
 * Author: Eddie Yang
 * Project: Heap
 * Purpose: to create a Heap class that can store item in incrementing
 *        order or decrementing order.
 * Notes: didn't implement entry struct.
 */
#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <iomanip>
#include "compare.h"
#include "../!include/vector/vector.h"


using namespace std;

template<typename T>
struct entry{
    T* _item;
    int _serial_number;
};

template<class T>
class heap{
    public:
        heap();
        ~heap();
        heap(vector<T> v);
        void insert(const T& insert_me);
        T Pop();
        bool is_empty() const;

        template<class compare>
        void rising(compare& cmp);

        template<class compare>
        void falling(compare& cmp);
        unsigned int size() const; 
        unsigned int capacity() const; 
        friend ostream& operator << (ostream& outs, const heap<T>& print_me){
            print_me.print_tree();
            return outs;
        };
        void print_tree(ostream& outs = cout) const { print_tree(0);}
        void print_tree(unsigned int index, int level = 0, ostream& outs = cout) const{
            if(has_right(index)){
                print_tree(right_child_index(index),level+1);
            }

            outs<<setw(level*4)<<""<<_ar[index]<<endl;

            if(has_left(index)){
                print_tree(left_child_index(index),level+1);
            }
        }
        void set_min_or_max(bool b){max_or_min = b;}
        
    private:
        
        bool is_leaf( unsigned int i) const;

        unsigned int parent_index(unsigned int i) const{ return (i-1)/2; }
        unsigned int left_child_index(unsigned int i)const{ return 2*i+1; }
        unsigned int right_child_index(unsigned int i) const{ return 2*i+2; }
        template<class compare>
        unsigned int compare_child_index(unsigned int i, compare& cmp) const;

        T* left_child( unsigned int i ) { return _ar[left_child_index(i)]; }
        T* right_child( unsigned int i ) { return _ar[right_child_index(i)]; }
        T* parent( unsigned int i ) { return _ar[parent_index(i)];}

        bool has_left( unsigned int i ) const{ return left_child_index(i)< how_many; }
        bool has_right( unsigned int i ) const{ return right_child_index(i)< how_many; }
        bool has_parent( unsigned int i ) const{ 
            if(i ==0){
                return false;
            }else{
                return parent_index(i) >= 0;
            }
        }

        void swap_with_parent(unsigned int i);
        
        vector<T> _ar;

        //true for max, false for min
        //default setting is max
        bool max_or_min;

        unsigned int how_many;
};

template<class T> heap<T>::heap(){
    _ar = vector<T>();
    how_many = 0;
    max_or_min = true;
}
template<class T> heap<T>::~heap(){
    for(int i = 0; i < how_many;i++){
        T* delete_this = &_ar[i];
        delete delete_this;
    }
}

template<class T> heap<T>::heap(vector<T> v){
    _ar = vector<T>(v);
    how_many = v.size();
    max_or_min = true;
}


template<class T> void heap<T>::insert(const T &insert_me){
    _ar.push_back(insert_me);
    how_many++;
    if(max_or_min){
        
        big<T> b;
        rising(b);
    }else{
        small<T> s;
        rising(s);
    }

}

template<class T> T heap<T>::Pop(){
    T item = _ar[0];
    _ar[0] = _ar.pop_back();
    how_many--;
    if(max_or_min){
        big<T> b;
        falling(b);
    }else{
        small<T> s;
        falling(s);
    }
    return item;

}

template<class T> bool heap<T>::is_empty() const{
    return _ar.empty();
}

template<class T> unsigned int heap<T>::size()const{
    return _ar.size();
}

template<class T> unsigned int heap<T>::capacity()const{
    return _ar.capacity();
}

template<class T> bool heap<T>::is_leaf(unsigned int i) const{
    if(!has_right(i) && !has_left(i)){
        return true;
    }else{
        return false;
    }
}



template<class T> void heap<T>::swap_with_parent(unsigned int i){
    if(has_parent(i)){
        T temp = _ar[i];
        _ar[i] = _ar[parent_index(i)];
        _ar[parent_index(i)] = temp;
    }
}

template<class T> template<class compare> void heap<T>::rising(compare& cmp){
    int index = how_many-1;
    //big for max heap, small for min heap
    while( has_parent(index) && cmp(_ar[parent_index(index)],_ar[index])){
        swap_with_parent(index);
        index = parent_index(index);
    }
}


template<class T> template<class compare> void heap<T>::falling(compare& cmp){
    int index = 0;

    //if check wether there is value at left, bc must have left value to have right
    while(has_left(index)){

        int temp = left_child_index(index);
        if(has_right(index)&& cmp(_ar[temp],_ar[right_child_index(index)])){
            temp = right_child_index(index);
        }
        if(cmp(_ar[temp],_ar[index])){
            break;
        }else{
            swap_with_parent(temp);
        }
        index = temp;
    }
}



#endif //HEAP_H