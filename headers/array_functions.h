#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H
#include <iostream>


template <typename T>
void Split(T source[],T Destionation2[],T Destionation1[],int size){

    int j;
    if(size%2 == 0){
        j = size/2;
    }
    else{
        j = size/2 + 1;
    }

    for(int i=0; i<size; i++){
        if(i<j){
            Destionation1[i] = source[i];
        }
        else{
            Destionation2[i-j] = source[i];
        }
    }
}

template <typename T>
int Insert_sorted(T source[], T item, int &size,int capacity){

    if(size == capacity){
        return 0;
    }
    int i;
    for(i = size -1; source[i] > item && i >= 0; i--){
        source[i+1] = source[i];
    }

    source[i+1] = item;

    size+=1;
    return size;
}


template <typename T>
int Where_this_goes(T source[], T item, int size){
    for(int i=0; i<size; i++){
        if(item == source[i]){
            return NULL;
        }
        else if(item < source[i]){
            return i;
        }
    }
    return size;
}





























#endif // ARRAY_FUNCTIONS_H
