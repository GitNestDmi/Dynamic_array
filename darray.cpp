#include "darray.h"



Darray::Darray() : lenght(0)
{
    cout << "Darray()" << endl;
    init_array(lenght, start_lenght_array);
}
//-------------------------------------------------------------------------------------
Darray::Darray(const Darray& other): lenght(other.lenght), capacity(other.capacity)
{
    cout << "Darray(const Darray& other)" << endl;
    data = new int [static_cast<unsigned int>(capacity)];
    memcpy(reinterpret_cast<char*>(data), reinterpret_cast<char*>(other.data),
           static_cast<unsigned int>(lenght)*sizeof(int));
}
//-------------------------------------------------------------------------------------
Darray::Darray(int value) : lenght(1)
{                                       // Нужен explecit ?
    cout << "Darray(int value)" << endl;
    init_array(lenght, start_lenght_array);
    data[0] = value;
}
//-------------------------------------------------------------------------------------
Darray::Darray(int size_lenght, int value): lenght(size_lenght)
{
    cout << "Darray(int size_lenght, int value)" << endl;
    init_array(lenght, size_lenght * resize_factor);
    for (int i = 0; i < lenght; i++)
        data[i] = value;
}
//-------------------------------------------------------------------------------------
//    Darray::Darray(const int * dataOther) : lenght(1), capacity(start_lenght_array)
//    {
//        cout << "constructor 1" << endl;
//        //data = new int[capacity];
//    }
//-------------------------------------------------------------------------------------
void Darray::init_array(int size_lenght, int size_capacity)
{

    if(lenght < 0)
        throw MyException("The attemp to get a negative "
                          "array size has been suspended",
                          MyException::out_of_min_size);

    capacity = size_capacity;
    if(capacity > max_lenght_array){
        if(size_lenght > max_lenght_array)
            throw MyException("The attemp to get an array larger"
                              " than the allowed size has been suspended",
                              MyException::out_of_max_size);
        else
            capacity = max_lenght_array;
    }


    data = new int [static_cast<uint>(capacity)];
}
//-------------------------------------------------------------------------------------
void Darray::resize_array(int size_new)
{
    if(size_new > max_lenght_array)
        throw MyException("The attemp to get an array larger"
                          " than the allowed size has been suspended",
                          MyException::out_of_max_size);

    if(size_new <= capacity )
        return;

    while (capacity < size_new) {
        capacity *= resize_factor;
        if(capacity > max_lenght_array){
            capacity = max_lenght_array;
            break;
        }
    }

    int* tmp_ptr = new int [static_cast<uint>(capacity)];
    memcpy(reinterpret_cast<char*>(tmp_ptr), reinterpret_cast<char*>(data),
           static_cast<uint>(lenght)*sizeof(int));
    delete [] data;
    data = tmp_ptr;
}
//-------------------------------------------------------------------------------------
const Darray& Darray::operator=(const Darray& other)
{
    cout << "operator=" << endl;
    lenght = other.lenght;
    capacity = other.capacity;
    delete [] data;
    data = new int [static_cast<uint>(capacity)];
    memcpy(reinterpret_cast<char*>(data), reinterpret_cast<char*>(other.data),
           static_cast<uint>(lenght)*sizeof(int));
    return *this;
}
//-------------------------------------------------------------------------------------
const Darray& Darray::operator+=(const Darray& other)
{
    cout << "operator+=" << endl;
    lenght += other.lenght;
    if(lenght >= capacity)
        resize_array(lenght);

    memcpy(reinterpret_cast<char*>(data) + (static_cast<uint>(lenght - other.lenght)*sizeof(int)),
           reinterpret_cast<char*>(other.data), static_cast<uint>(other.lenght)*sizeof(int));

    return *this;
}
//-------------------------------------------------------------------------------------
const Darray& Darray::append(const Darray& other)
{
    cout << "append " << endl;
    return *this += other;
}
//-------------------------------------------------------------------------------------
//const Darray& Darray::operator+(const Darray& other) // Нужно возвращать rvalue
//{

//    Darray tmp_obj(*this);
//    tmp_obj.append(other);


////    memcpy(reinterpret_cast<char*>(tmp_obj.data), reinterpret_cast<char*>(data),
////           static_cast<uint>(lenght)*sizeof(int));

////    memcpy(reinterpret_cast<char*>(tmp_obj.data) + (static_cast<uint>(lenght)*sizeof(int)),
////           reinterpret_cast<char*>(other.data), static_cast<uint>(other.lenght)*sizeof(int));

//    return tmp_obj;
//}
//-------------------------------------------------------------------------------------
int Darray::at(int index) const
{
    if(index > lenght || index < 0)
        throw MyException("The attemp to go outside the"
                          " array has been suspended",
                          MyException::out_of_range);
    return data[index];
}
//-------------------------------------------------------------------------------------
void Darray::push_back(int value)
{
    if(lenght >= capacity)
        resize_array(lenght * resize_factor);
    data[lenght++] = value;
}
//-------------------------------------------------------------------------------------
int Darray::pop_back()
{
    if(lenght <= 0)
        throw MyException("The attemp to go outside the"
                          " array has been suspended",
                          MyException::out_of_range);
    return data[lenght--];
}
//-------------------------------------------------------------------------------------
void Darray::show_arr(const char* sep) const
{
    for (int i = 0; i < lenght; i++)
        cout << data[i] << sep;
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
Darray::MyException::~MyException(){}
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
        throw MyException("The attemp to go outside the"
                          " array has been suspended",
                          MyException::out_of_range);
    return current->data[index];
}
//-------------------------------------------------------------------------------------
