#ifndef SET_H
#define SET_H
#include <iostream>
#include "array_functions.h"

using namespace std;
template <typename T>
class set
{
public:
    set();
    set(const set& source);


    ostream& print(ostream &out, int levels);
    bool insert(const T& entry);
    bool erase(const T& target);



    //Helper functions
    bool is_leaf( ) const { return (_childcount == 0); }
    bool loose_insert(const T& entry);
    bool loose_erase(const T& target);
    void fix_excess(int i);
    void fix_shortage(int i);
    void remove_biggest(T &removed_entry);


    const static int MINIMUM = 1;
    const static int MAXIMUM = 2 * MINIMUM;


    T _data[MAXIMUM + 1];//main items
    set<T>* _children[MAXIMUM + 2];//children
    int _datacount;//item count inside main array
    int _childcount;//adress count to children
};


template <typename T>
void set<T>::remove_biggest(T& removed_entry){
    if(is_leaf()){//check if I am a leaf
        removed_entry = _data[_datacount - 1];
        _datacount--;
    }
    else{
        _children[_childcount-1]->remove_biggest(removed_entry);
        if(_children[_childcount - 1]->_datacount < MINIMUM){
            fix_shortage(_childcount-1);
        }
    }
}

template <typename T>
bool set<T>::erase(const T &target){
    if(!loose_erase(target)){

        return false;//item not found
    }
    if((_datacount == 0) && (_childcount == 1)){
        //empty node, lose height connect to only child
        set<T>* child = _children[0];


        for(int i = 0; i < child->_datacount;i++){
            _data[_datacount] = child->_data[i];
            _datacount++;
        }



        _childcount = 0;
        for(int i = 0; i < child->_childcount;i++){
            _children[i] = child->_children[i];
            _childcount++;
        }

        delete child;

    }
    return true;
}

template <typename T>
bool set<T>::loose_erase(const T &target){
    int idx = 0;
    while (target > _data[idx] && idx < _datacount){
        idx++;
    }

    if(idx < _datacount && _data[idx] != target && is_leaf()){
        return false;
    }
    else if (idx < _datacount && _data[idx] == target && is_leaf()){
        for(int i = idx + 1; i < _datacount; i++){
            _data[i-1] = _data[i];
        }
        _datacount --;
        return true;
    }
    else if(_data[idx] != target && !is_leaf()){
        _children[idx]->loose_erase(target);
        if(_children[idx]->_datacount < MINIMUM){
            fix_shortage(idx);
        }

        return true;
    }
    else if(_data[idx] != target && !is_leaf()){
        _children[idx]->loose_erase(target);
        if(_children[idx]->_datacount < MINIMUM){
            fix_shortage(idx);
        }
        return true;
    }
    else{
        _children[idx]->remove_biggest(_data[idx]);
        if(_children[idx]->_datacount < MINIMUM){
            fix_shortage(idx);
        }
        return true;
    }


}


template <typename T>
void set<T>::fix_shortage(int idx){
    if(idx == 0){
        if(_children[idx+1]->_datacount > MINIMUM){
            _children[idx]->_datacount++;
            _children[idx]->_data[_children[idx]->_datacount-1] = _data[idx];
            _data[idx] = _children[idx+1]->_data[0];

            for(int i = 0; i < _children[idx+1]->_datacount; i++){
                _children[idx+1]->_data[i] = _children[idx+1]->_data[i+1];
            }

            _children[idx+1]->_datacount--;

            if(!(_children[idx+1]->is_leaf())){
                _children[idx]->_children[0] = _children[idx+1]->_children[0];
                for(int i=0;i<_children[idx+1]->_childcount;i++){
                    _children[idx+1]->_children[i] = _children[idx+1]->_children[i+1];
                }
                _children[idx]->_childcount++;
                _children[idx+1]->_childcount--;
            }
        }
        else{
            _children[idx]->_data[_children[idx]->_childcount] = _data[idx];
            for(int i=idx; i<_datacount; i++){
                _data[i] = _data[i+1];
            }
            _datacount--;
            _children[idx]->_datacount++;

            for(int i=0;i<_children[idx+1]->_datacount;i++){
                _children[idx]->_data[_children[idx]->_datacount] = _children[idx+1]->_data[i];
                _children[idx]->_datacount++;
            }
            for(int i=0;i<_children[idx+1]->_childcount;i++){
                _children[idx]->_children[_children[idx]->_childcount] = _children[idx+1]->_children[i];
                _children[idx]->_childcount++;
            }
            _children[idx+1]->_datacount = 0;
            _children[idx+1]->_childcount = 0;

            delete _children[idx+1];
            _children[idx+1] = new set<T>();
            for(int i=idx+1;i<_childcount;i++){
                _children[i] = _children[i+1];
            }
            _childcount--;
        }
    }
    else if(idx == _childcount-1){
        if(_children[idx-1]->_datacount > MINIMUM){
            for(int i=_children[idx]->_datacount;i>0;i--){
                _children[idx]->_data[i] = _children[idx]->_data[i-1];
            }
            _children[idx]->_data[0] = _data[idx-1];
            _children[idx]->_datacount++;
            _data[idx-1] = _children[idx-1]->_data[_datacount-1];
            _children[idx-1]->_datacount--;
            if(!(_children[idx-1]->is_leaf())){
              _children[idx]->_children[0] = _children[idx-1]->_children[_children[idx-1]->_childcount-1];
              _children[idx]->_childcount++;
              _children[idx-1]->_childcount--;
            }
        }
    }
    else if(_children[idx-1]->_datacount == MINIMUM){
        _children[idx-1]->_data[_children[idx-1]->_datacount] = _data[idx-1];
        for(int i = idx-1; i<_datacount;i++){
            _data[idx-1] = _data[i+1];
        }
        _datacount--;
        _children[idx-1]->_datacount++;
        for(int i=0;i<_children[idx]->_datacount;i++){
            _children[idx-1]->_data[_children[idx-1]->_datacount] = _children[idx]->_data[i];
            _children[idx-1]->_datacount++;
        }
        for(int i=0;i<_children[idx]->_childcount;i++){
            _children[idx-1]->_children[_children[idx-1]->_childcount] = _children[idx]->_children[i];
            _children[idx-1]->_childcount++;
        }
        _children[idx]->_datacount=0;
        _children[idx]->_childcount=0;

        delete _children[idx];
        _children[idx] = new set<T>();
        for(int i=idx;i<_childcount;i++){
            _children[i] = _children[i+1];
        }
        _childcount--;

    }
    else{
        if(_children[idx-1]->_datacount > MINIMUM){
            for(int i=_children[idx]->_datacount; i >0; i--){
                _children[idx]->_data[i] = _children[idx]->_data[i-1];
            }
            _children[idx]->_data[0] = _data[idx-1];
            _children[idx]->_datacount++;
            _data[idx-1] = _children[idx-1]->_data[_datacount-1];
            _children[idx-1]->_datacount--;

            if(!(_children[idx-1]->is_leaf())){
                _children[idx]->_childcount++;
                _children[idx-1]->_childcount--;
            }
        }
    }
}



template <typename T>
set<T>::set(){
    _datacount = 0;
    _childcount = 0;

}

template <typename T>
set<T>::set(const set &source){

}

template <typename T>
bool set<T>::insert(const T &entry){
    if (!loose_insert(entry)){
        return false;
    }

    if(_datacount > MAXIMUM){
        set<T> *child = new set<T>();

        child->_datacount = _datacount;
        child->_childcount = _childcount;

        for(int j=0;j< _childcount;j++){
            child->_children[j] = _children[j];
        }
        for(int k=0;k< _datacount;k++){
            child->_data[k] = _data[k];
        }

        _datacount = 0;
        _childcount = 1;

        _children[0] = child;


        fix_excess(0);
    }
}

template <typename T>
bool set<T>::loose_insert(const T &entry){

    //cout<<endl<<"Loose Insert->"<<endl;
    if(_childcount== 0){
        //cout<<endl<<"LEAF, Insert"<<endl;
        _datacount = Insert_sorted(_data,entry,_datacount,MAXIMUM+1);
        //cout<<endl<<"Loose Insert END"<<endl;
        return true;
    }
    else{

        int i =0;
        while(entry > _data[i] && i < _datacount){
            i++;
        }

        _children[i]->loose_insert(entry);

        if(_children[i]->_datacount >= MAXIMUM+1){
            //cout<<endl<<"CHILD TOO BIG"<<endl;
            fix_excess(i);
        }
        return true;
    }

}

template <typename T>
void set<T>::fix_excess(int i){
//    cout<<endl<<"Fix Excess"<<endl;
//    print(cout,0);
//    cout<<endl;

    int count = 0;

    //cout<<endl<<"EXCESS before loop"<<endl;

    for(count = _datacount; count > i; count--){
        _data[count] = _data[count-1];
    }
    _data[i] = _children[i]->_data[MINIMUM];
    _datacount++;

    //cout<<endl<<"EXCESS before child"<<endl;

    //Make 2 new children
    set<T> *left = new set<T>();
    set<T> *right = new set<T>();
    left->_datacount = MINIMUM;
    right->_datacount = MINIMUM;



    //cout<<endl<<"EXCESS middle"<<endl;

    //Copy Stuff into Children
    for(count = 0; count< MINIMUM; count++){
        left->_data[count] = _children[i]->_data[count];
        right->_data[count] = _children[i]->_data[count+MINIMUM+1];
    }

    int sub = (_children[i]->_childcount)/2;

    for(count = 0; count < sub; count++){
        left->_children[count] = _children[i]->_children[count];
        right->_children[count] = _children[i]->_children[count+sub];
    }

    if(sub > 0){
        left->_childcount = MINIMUM +1;
        right->_childcount = MINIMUM +1;
    }


    _children[_childcount] = new set<T>();
    for(count = _childcount; count > i; count--){
        _children[count] = _children[count-1];
    }
    _childcount++;

    _children[i] = left;
    _children[i+1] = right;


    //cout<<endl<<"EXCESS DONE"<<endl;

}


template <typename T>
ostream& set<T>::print(ostream &out, int levels){
    if (_childcount == 0){
        out<<string(levels,' ');
        out<<'[';
        for(int i = 0;i < _datacount; i++){
            out<<_data[i];
            if(i == _datacount -1){
                out<<']';
            }
            else{
                out<<',';
            }
        }
    }
    else{
        for(int i = _datacount; i >= 1; i--){
            _children[i]->print(out,levels+5)<<endl;
            out<<string(levels,' ')<<_data[i-1]<<endl;
        }
        _children[0]->print(out,levels + 5)<<endl;
    }
    return out;
}




#endif // SET_H





















