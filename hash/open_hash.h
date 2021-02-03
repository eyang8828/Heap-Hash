#ifndef OPEN_HASH_H
#define OPEN_HASH_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>

using namespace std;

template<class T>
class open_hash{
    public:
        public:
                // MEMBER CONSTANT -- See Appendix E if this fails to compile.  
            static const size_t CAPACITY = 19;
                // CONSTRUCTOR  
            open_hash( );
                // MODIFICATION MEMBER FUNCTIONS
            void insert(const T& entry);
            void remove(int key);
                // CONSTANT MEMBER FUNCTIONS
            bool is_present(int key) const;
            void find(int key, bool& found, T& result) const;
            int check_col(int index, int key, bool& check) const;
            size_t size() const { return used; }
            friend ostream& operator <<(ostream& outs, const open_hash<T>& print_me){
                bool flag;
                for(int i = 0; i<CAPACITY;i++){
                    flag = false;
                    outs<<'['<<setfill('0')<<setw(3)<<i<<']';
                    outs<<print_me.data[i];
                    int temp = print_me.check_col(i, print_me.data[i]._key, flag);
                    if(flag){
                        outs<<"("<<temp<<")  *";
                    }
                    outs<<endl;
                }
                return outs;
            }
        private:
                // MEMBER CONSTANTS -- These are used in the key field of special records.
            static const int NEVER_USED = -1;
            static const int PREVIOUSLY_USED = -2;
                // MEMBER VARIABLES
            T data[CAPACITY];
            size_t used;
                // HELPER FUNCTIONS
            size_t hash(int key) const;
            size_t next_index(size_t index) const;
            void find_index(int key, bool& found, size_t& index) const;
            bool never_used(size_t index) const;
            bool is_vacant(size_t index) const;
            
};



//========================================================================



template <class T>
void open_hash<T>::insert(const T& entry){
    bool already_present; // True if entry.key is already in the table
    size_t index; // data[index] is location for the new entry
    assert(entry._key >= 0);
        // Set index so that data[index] is the spot to place the new entry.
    find_index(entry._key, already_present, index);
        // If the key wasn’t already there, then find the location for the new entry.
    if (!already_present){
        assert(size( ) < CAPACITY);
        index = hash(entry._key);
        while (!is_vacant(index)){
            index = next_index(index);
        }
        ++used;
    }
    data[index] = entry;
}

template<class T>
int open_hash<T>::check_col(int index, int key, bool& check) const{
    // if collision occured return the original index that the data was supposed to be inserted
    if(!is_vacant(index)){
        int i = hash(key);
        check = index != i;
        return i;
    }
    check = false;
    return 0 ;
}

template <class T>
void open_hash<T>::remove(int key){
    bool found; // True if key occurs somewhere in the table
    size_t index; // Spot where data[index].key == key
    assert(key >= 0);
    find_index(key, found, index);
    if (found){ 
        // The key was found, so remove this record and reduce used by 1.
        data[index]._key = PREVIOUSLY_USED; // Indicates a spot that’s no longer in use.
        data[index]._value = 0;
        --used;
    }
}

template<class T> 
open_hash<T>::open_hash(){
    size_t i;
    used = 0;
    for (i = 0; i < CAPACITY; ++i){
        data[i]._key = NEVER_USED;
    }
}

template <class T>
bool open_hash<T>::is_present(int key) const{
    bool found;
    size_t index;
    assert(key >= 0);
    find_index(key, found, index);
    return found;
}

template <class T>
void open_hash<T>::find(int key, bool& found, T& result) const{
    size_t index;
    assert(key >= 0);
    find_index(key, found, index);
    if (found)
    result = data[index];
}

template <class T>
inline size_t open_hash<T>::hash(int key) const{
    return (key % CAPACITY);
}

template <class T>
inline size_t open_hash<T>::next_index(size_t index) const{
    return ((index+1) % CAPACITY);
}

template <class T>
void open_hash<T>::find_index(int key, bool& found, size_t& i) const{
    size_t count; // Number of entries that have been examined
    count = 0;
    i = hash(key);
    while((count < CAPACITY) && (!never_used(i)) && (data[i]._key != key))
    {
        ++count;
        i = next_index(i);
    }
    found = (data[i]._key == key);
}

template <class T>
inline bool open_hash<T>::never_used(size_t index) const{
    return (data[index]._key == NEVER_USED);
}

template <class T>
inline bool open_hash<T>::is_vacant(size_t index) const{
    return (data[index]._key < 0);
}


#endif //OPEN_HASH_H