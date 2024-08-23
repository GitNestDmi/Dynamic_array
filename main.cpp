#include <darray.h>

using namespace std;

int main()
{
    try {
        Darray a2(2,2 );

        Darray a3(a2 + a2);

        cout << "a1 ->" ;
        a2.show_arr();

        cout << "a3 ->" ;
        a3.show_arr();

    }
    catch (const Darray::DarrayException & ex) {
        cout << ex.what() <<" - " << ex.GetExcepType() << endl;

    }
    return 0;
}


//Надо добавить:
//Конструктор преобразования через массив int
