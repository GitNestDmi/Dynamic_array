#ifndef DARRAY_H
#define DARRAY_H

#include <iostream>

typedef unsigned int uint;



class Darray{
    enum{
        start_lenght_array  = 2,
        resize_factor = 2,
        max_lenght_array = 30,
        value_error = 123456789
    };
    
    enum type_assign{equate_operat, plus_operat, minus_operat,
                     mult_operat, div_operat, rem_operat};

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

    void init_array(int size_lenght, int size_capacity);
    void resize_array(int size_new);

    
public:
    //    Darray(const int * dataOther) ;
    Darray();
    explicit Darray(int value);
    Darray(int size_lenght, int value);
    Darray(const Darray& other);
    Darray(Darray&& other);
    ~Darray();

    Item operator[](int index){ return Item(this, index); }

    const Darray& operator=(const Darray& other);
    const Darray& operator+=(const Darray& other);
    Darray& operator=(Darray&& other);
    Darray operator+(const Darray& other);

    const Darray& append(const Darray& other);
    const int* get_data() const { return data; }
    int size() const { return lenght; }
    int capacity_ar() const { return capacity; }
    int at(int index) const ;
    int pop_back();
    void push_back(int value = 0);
    void show_arr(const char* sep = " ") const;

    struct MyException : public std::range_error
    {
        enum exept_type{ out_of_max_size, out_of_min_size, out_of_range};

        MyException(const char* msg, exept_type type):
            range_error(msg) {this->ex_type = type;}
        ~MyException();
        exept_type GetExcepType()const {return ex_type;}

    private:
        exept_type ex_type;
    };
};

#endif // DARRAY_H
