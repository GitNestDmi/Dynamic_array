#include "darray.h"

using namespace std;


Darray::Darray()
{
    cout <<"create () " << this << endl;
    init_array(lenght, start_lenght_array);
}
//-------------------------------------------------------------------------------------
Darray::Darray(int value, int size_lenght): lenght(size_lenght)
{
    cout <<"create(value,...) "<< this << endl;
    init_array(lenght, size_lenght * resize_factor);
    for (int i = 0; i < lenght; i++)
        data[i] = value;
}
//-------------------------------------------------------------------------------------
Darray::Darray(Darray&& other) noexcept : data(other.data),
    lenght(other.lenght), capacity(other.capacity)
{
    cout <<"move "<< &other << " -> "<< this<< endl;
    other.data = nullptr;
    other.lenght = 0;
    other.capacity = 0;
}
//-------------------------------------------------------------------------------------
Darray::Darray(const Darray& other): lenght(other.lenght),
    capacity(other.capacity)
{
    cout <<"copy "<< &other << " -> "<< this<< endl;
    data = new int [static_cast<unsigned int>(capacity)];
    memcpy(reinterpret_cast<char*>(data), reinterpret_cast<char*>(other.data),
           static_cast<unsigned int>(lenght)*sizeof(int));
}
//-------------------------------------------------------------------------------------
Darray::~Darray()
{
    cout <<"delete "<< this << endl;
    delete [] data;
}
//-------------------------------------------------------------------------------------
//    Darray::Darray(const int * dataOther) : lenght(1), capacity( )
//    {
//        cout << "constructor 1" << endl;
//        //data = new int[capacity];
//    }
//-------------------------------------------------------------------------------------
void Darray::init_array(int size_lenght, int size_capacity)
{

    if(size_lenght < 0 || size_capacity < 0)
        throw DarrayException("The attemp to get a negative "
                              "array size has been suspended",
                              DarrayException::out_of_min_size);

    if(size_capacity >= start_lenght_array)
    {
        capacity = size_capacity;

        if(capacity > max_lenght_array){
            if(size_lenght > max_lenght_array)
                throw DarrayException("The attemp to get an array larger"
                                      " than the allowed size has been suspended",
                                      DarrayException::out_of_max_size);
            else
                capacity = max_lenght_array;
        }
    }
    else
        capacity = start_lenght_array;

    data = new int [static_cast<uint>(capacity)];
}
//-------------------------------------------------------------------------------------
void Darray::resize_array(int size_new)
{
    if(size_new > max_lenght_array)
        throw DarrayException("The attemp to get an array larger"
                              " than the allowed size has been suspended",
                              DarrayException::out_of_max_size);

    if(size_new <= capacity )
        return;

    if(capacity == 0)
        capacity = start_lenght_array;

    while (capacity < size_new) {
        capacity *= resize_factor;
        if(capacity > max_lenght_array){
            capacity = max_lenght_array;
            break;
        }
    }

    int* tmp_ptr = new int [static_cast<uint>(capacity)];

    if(data != nullptr)
        memcpy(reinterpret_cast<char*>(tmp_ptr), reinterpret_cast<char*>(data),
               static_cast<uint>(lenght)*sizeof(int));

    delete [] data;
    data = tmp_ptr;
}
//-------------------------------------------------------------------------------------
const Darray& Darray::operator=(const Darray& other)
{
    lenght = other.lenght;
    capacity = other.capacity;
    delete [] data;
    data = new int [static_cast<uint>(capacity)];
    memcpy(reinterpret_cast<char*>(data), reinterpret_cast<char*>(other.data),
           static_cast<uint>(lenght)*sizeof(int));
    return *this;
}
//-------------------------------------------------------------------------------------
Darray& Darray::operator=(Darray&& other) noexcept
{
    int* tmp = data;
    data = other.data;
    other.data = tmp;
    lenght = other.lenght;
    other.lenght = 0;
    capacity = other.capacity;
    other.capacity = 0;
    return *this;
}
//-------------------------------------------------------------------------------------
const Darray& Darray::operator+=(const Darray& other)
{
    lenght += other.lenght;
    if(lenght >= capacity)
        resize_array(lenght);

    memcpy(reinterpret_cast<char*>(data) + (static_cast<uint>(lenght - other.lenght)*sizeof(int)),
           reinterpret_cast<char*>(other.data), static_cast<uint>(other.lenght)*sizeof(int));

    return *this;
}
//-------------------------------------------------------------------------------------
Darray operator+(Darray left, const Darray& right)
{// уже лучше, но может быть лишнее выделение памяти при left.len+right.len > left.capacity
    cout << "operator+  " << &left <<endl;
    left += right;
    return  left;
}
//-------------------------------------------------------------------------------------
int Darray::at(int index) const
{
    if(index > lenght || index < 0)
        throw DarrayException("The attemp to go outside the"
                              " array has been suspended",
                              DarrayException::out_of_range);
    return data[index];
}
//-------------------------------------------------------------------------------------
const Darray& Darray::append(const Darray& other)
{
    return *this += other;
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
        throw DarrayException("The attemp to go outside the"
                              " array has been suspended",
                              DarrayException::out_of_range);
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
Darray::DarrayException::~DarrayException(){}
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
        throw DarrayException("The attemp to go outside the"
                              " array has been suspended",
                              DarrayException::out_of_range);
    return current->data[index];
}
//-------------------------------------------------------------------------------------
