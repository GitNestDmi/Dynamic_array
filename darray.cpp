#include "darray.h"




Darray::Darray() : lenght(0), capacity(start_lenght_array)
{
    data =new int [static_cast<unsigned int>(capacity)];
}
//-------------------------------------------------------------------------------------
Darray::Darray(int size, int value): lenght(size), capacity(size* resize_factor)
{   // надо решить проблему с неявным преобразованием  параметров
    data = new int [static_cast<unsigned int>(capacity)];
    for (int i = 0; i < lenght; i++)
        data[i] = value;
}
//-------------------------------------------------------------------------------------
Darray::Darray(const Darray& other): lenght(other.lenght), capacity(other.capacity)
{
    data = new int [static_cast<unsigned int>(capacity)];
    memcpy(reinterpret_cast<char*>(data), reinterpret_cast<char*>(other.data),
           static_cast<unsigned int>(lenght)*sizeof(int));
}
//-------------------------------------------------------------------------------------
//    Darray::Darray(const int * dataOther) : lenght(1), capacity(start_lenght_array)
//    {
//        cout << "constructor 1" << endl;
//        //data = new int[capacity];
//    }
//-------------------------------------------------------------------------------------
void Darray::resize_array(int size_new){
    if(size_new <= capacity)
        return;
    while (capacity < size_new) {
        capacity *= resize_factor;
        if(capacity >= max_lenght_array){
            capacity = max_lenght_array;
            break;
        }
    }
    int * tmp_ptr = new int [static_cast<unsigned int>(capacity)];
    memcpy(reinterpret_cast<char*>(tmp_ptr), reinterpret_cast<char*>(data),
           static_cast<unsigned int>(lenght)*sizeof(int));
    delete [] data;
    data = tmp_ptr;
    cout << lenght << " - " << capacity << endl;
}
//-------------------------------------------------------------------------------------
const Darray& Darray::operator=(const Darray& other){
    cout << "operator = "<< endl;
    lenght = other.lenght;
    capacity = other.capacity;
    delete [] data;
    data = new int [static_cast<unsigned int>(capacity)];
    memcpy(reinterpret_cast<char*>(data), reinterpret_cast<char*>(other.data),
           static_cast<unsigned int>(lenght)*sizeof(int));
    return *this;
}
//-------------------------------------------------------------------------------------
const Darray& Darray::operator+=(const Darray& other){
    cout << "operator += "<< endl;
    for (int i = 0; i < other.size(); i++) {
        push_back(other.data[i]);
    }
    return *this;
}
//-------------------------------------------------------------------------------------
int Darray::at(int element) const {
    if(element <= capacity) return data[element];
    else return value_error;
}
//-------------------------------------------------------------------------------------
void Darray::push_back(int value){
    if(lenght >= capacity)
        resize_array(capacity * resize_factor);
    data[lenght++] = value;
}
//-------------------------------------------------------------------------------------
int Darray::pop_back(){
    if(lenght > 0)
        return data[lenght--];
    else
        return value_error;
}
//-------------------------------------------------------------------------------------
void Darray::show_arr()const {
    for (int i = 0; i < lenght; i++)
        cout << data[i] << " ";
    cout<< endl;
}
//-------------------------------------------------------------------------------------
int Darray::Item::assign_operator(int right, type_assign type){
    if(index >= current->lenght || index < 0)
        return right;

    switch (type) {
    case equate_operat:
        current->data[index] = right;    break;
    case plus_operat:
        current->data[index] += right;    break;
       case minus_operat:
        current->data[index] -= right;    break;
    case mult_operat:
        current->data[index] *= right;    break;
    case div_operat:
        current->data[index] /= right;    break;
    case rem_operat:
        current->data[index] %= right;    break;
    }

    return current->data[index];
}
//-------------------------------------------------------------------------------------
int Darray::Item::operator=(int right)
{
    return assign_operator(right, equate_operat);
}
//-------------------------------------------------------------------------------------
int Darray::Item::operator+=(int right)
{
    return assign_operator(right, plus_operat);
}
//-------------------------------------------------------------------------------------
int Darray::Item::operator-=(int right)
{
    return assign_operator(right, minus_operat);
}
//-------------------------------------------------------------------------------------
int Darray::Item::operator*=(int right)
{
    return assign_operator(right, mult_operat);
}
//-------------------------------------------------------------------------------------
int Darray::Item::operator/=(int right)
{
    return assign_operator(right, div_operat);
}
//-------------------------------------------------------------------------------------
int Darray::Item::operator%=(int right)
{
    return assign_operator(right, rem_operat);
}
//-------------------------------------------------------------------------------------
Darray::Item::operator int() const
{
    if(index >= current->lenght || index < 0)
        return value_error;
    return current->data[index];
}
//-------------------------------------------------------------------------------------
