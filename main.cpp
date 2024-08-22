#include <darray.h>

using namespace std;


int main()
{
    try {
        Darray a1;
        Darray a3 = a1 + static_cast<Darray>(6);

        a1.show_arr();
        a3.show_arr();

    }
    catch (const Darray::MyException & ex) {
        cout << ex.what() <<" - " << ex.GetExcepType() << endl;

    }
    return 0;
}


//Надо добавить:
//Конструктор преобразования через массив int
