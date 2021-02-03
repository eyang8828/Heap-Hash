#ifndef CHAINED_HASH_H
#define CHAINED_HASH_H

#include "../!include/List/List.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>

using namespace std;

template <class T>
class chained_hash
{
public:
    static const int CAPACITY = 19;

    chained_hash( );                                    //CTOR

    bool insert(const T& entry);                        //insert entry
    bool remove(int key);                               //remove this key

    bool find(int key, T& result) const;                //result <- record with key
    bool is_present(int key) const;                //is this key present in table?
    int size( ) const { return total_records; }         //number of keys in the table
    template<class TT>
    friend ostream& operator << (ostream& outs, const chained_hash<TT>& print_me){
        for(int i = 0; i<CAPACITY;i++){
            outs<<'['<<setfill('0')<<setw(3)<<i<<']';
            outs<<print_me._data[i];
            outs<<endl;
        }
        return outs;
    }
private:
    List<T> _data[CAPACITY];                          //table chains
    int total_records;                                  //number of keys in the table

    int hash(int key) const;                            //hash function
    typename List<T>::Iterator find_node(int key) const;//find this key in the table
};


//========================================================================



template<class T> 
chained_hash<T>::chained_hash(){
    total_records = 0;
    for(int i = 0; i <CAPACITY; i++){
        List<T> temp = List<T>();
        _data[i] = temp;
    }
}

template <class T>
bool chained_hash<T>::insert(const T& entry){
    bool already_present; // True if entry.key is already in the table
    size_t index; // data[index] is location for the new entry
    assert(entry._key >= 0);
        // Set index so that data[index] is the spot to place the new entry.

    already_present = is_present(entry._key);
    
    index = hash(entry._key);

        // If the key wasn’t already there, then find the location for the new entry.
    if (!already_present){

        assert(size( ) < CAPACITY);
        _data[index].Inserthead(entry);
        total_records++;
    }else{
        assert(size() < CAPACITY);
        _data[index].Insertafter(entry,_data[index].Lastnode());
        total_records++;
    }
    total_records++;
    return true;
}


template <class T>
bool chained_hash<T>::remove(int key){
    bool found; // True if key occurs somewhere in the table
    size_t index; // Spot where data[index].key == key
    assert(key >= 0);
    index = hash(key);
    //call Deletenode to delete target
    found = _data[index].Deletenode(key);
    if (found){ 
        // The key was found, so remove this record and reduce used by 1.
        --total_records;
    }
    return found;
}

template <class T>
bool chained_hash<T>::is_present(int key) const{
    bool found;
    size_t index;
    T result;
    assert(key >= 0);

    //call find to check presentness
    found= find(key, result);

    return found;
}

template<class T>
bool chained_hash<T>::find(int key, T &result) const
{
    bool found = false;
    size_t index;
    assert(key >= 0);
    index = hash(key);
    typename List<T>::Iterator temp;
    
    temp = find_node(key);

    //temp will be null if we found nothing
    if(!temp.is_null()){
        found = true;
        result = *temp;
    }
    
    
    return found;
}

template<class T> 
inline int chained_hash<T>::hash(int key) const
{
    return (key % CAPACITY);
}


template<class T> 
typename List<T>::Iterator chained_hash<T>::find_node(int key) const{
    // initialize variable
    size_t count = 0; 
    size_t i = hash(key);
    typename List<T>::Iterator walker;

    //check if it's empty to prevent error
    if(!_data[i].Empty()){
        //walk through and match
        walker =_data[i].Begin();
        while(walker!=_data[i].Lastnode()){
            T r= *walker;
            
            if(r._key==key){
                return walker;
            }
            walker++;
        }
    }
    walker = _data[i].End();
    
    return walker;

}

#endif // CHAINED_HASH_H