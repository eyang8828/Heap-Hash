#include "PQueue.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
    srand(time(NULL));
    int Random(int i, int j);
    PQueue<int> pq;
    for (int i = 0; i<100; i++){
        pq.insert(Random(1,1000), Random(1,10));
    }
    int out;
    for(int i = 0; i <100;i++){
        out = pq.Pop();
        cout<<"|"<<i+1<<"| number is "<<out<<endl;
    }
}
int Random(int i, int j){
        return rand()%j+i;
}
