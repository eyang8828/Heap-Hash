#ifndef COMPARE_H
#define COMPARE_H

using namespace std;

template<typename T>
class big{
    public:
        bool operator()(const T& item1, const T& item2){
            return item1 < item2;
        };
};

template<typename T>
class small{
    public:
        bool operator()(const T& item1, const T& item2){
            return item2 < item1;
        };
};

#endif // COMPARE_H