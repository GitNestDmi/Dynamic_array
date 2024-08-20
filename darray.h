#ifndef DARRAY_H
#define DARRAY_H


#include <iostream>
#include <cstring>
using namespace std;


class Darray{
    enum{
        start_lenght_array  = 2,
        resize_factor = 2,
        max_lenght_array = 30,
        value_error = 123456789
    };

    enum type_assign{equate_operat, plus_operat, minus_operat, mult_operat, div_operat, rem_operat};

    class Item{
        Darray* current = nullptr;
        int index = -1;
        int assign_operator(int right, type_assign type);

    public:
        Item(Darray* obj, int indx): current(obj), index(indx){}
        int operator=(int right);
        int operator+=(int right);
        int operator-=(int right);
        int operator*=(int right);
        int operator/=(int right);
        int operator%=(int right);
        operator int() const ;
    };

    int *data = nullptr;
    int lenght = 0;
    int capacity = 0;

    void resize_array(int size_new);

public:
    //    Darray(const int * dataOther) ;
    Darray();
    Darray(int size, int value = 0);
    Darray(const Darray& other);
    ~Darray() { delete [] data; }

    const Darray& operator=(const Darray& other);
    const Darray& operator+=(const Darray& other);
    Item operator[](int index){ return Item(this, index); }

    int size() const { return lenght; }
    int capacity_ar() const { return capacity; }
    const int* get_data() const { return data; }
    int at(int element) const ;
    void push_back(int value = 0);
    int pop_back();
    void show_arr()const;
};

#endif // DARRAY_H
