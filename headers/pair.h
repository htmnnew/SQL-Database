#ifndef PAIR_H
#define PAIR_H
#include <iostream>


using namespace std;

template <typename K, typename V>
struct Pair{


public:

    Pair();

    Pair(K key, V val);

    Pair<K,V> MakePair(K key, V value);

    V getval();
    K getkey();

    //Operators
    template <typename KK, typename VV>
    friend bool operator <(const Pair<KK, VV>& left, const Pair<KK, VV>& right);

    template <typename KK, typename VV>
    friend bool operator ==(const Pair<KK, VV>& left, const Pair<KK, VV>& right);

    template <typename KK, typename VV>
    friend ostream& operator <<(ostream& outs, const Pair<KK, VV>& printMe);

//-------
    K k;
    V v;

};

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

template <typename K, typename V>
Pair<K,V>::Pair(){
    k = '\0';
    v = 0;
}

template <typename K, typename V>
Pair<K,V>::Pair(K key, V val){
    k = key;
    v = val;
}

template <typename K, typename V>
Pair<K,V> Pair<K,V>::MakePair(K key, V value){
    Pair<K,V> A(key,value);
    return A;
}

template <typename K, typename V>
V Pair<K,V> ::getval(){
    return v;
}

template <typename K, typename V>
K Pair<K,V> ::getkey(){
    return k;
}

template <typename KK, typename VV>
bool operator <(const Pair<KK, VV>& left, const Pair<KK, VV>& right){
    //cout<<" < OPER (pair.h) "<<endl;
    if(left.k < right.k) return true;
    else                               return false;
}

template <typename KK, typename VV>
bool operator ==(const Pair<KK, VV>& left, const Pair<KK, VV>& right){
//    cout<<" == OPER (pair.h) "<<endl;
//    cout<<"("<<left.k<<")("<<right.k<<") "<<endl;
    if(left.k == right.k) return true;
    else                                return false;
}

template <typename KK, typename VV>
ostream& operator <<(ostream& outs, const Pair<KK, VV>& printMe){
//    cout<<" << OPER (pair.h) "<<endl;
     outs<<"  ["<<printMe.k<<"]("<<printMe.v<<")  ";
     return outs;
 }

#endif // PAIR_H
