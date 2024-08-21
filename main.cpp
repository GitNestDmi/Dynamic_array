#include <darray.h>



int main()
{
    try {
        Darray a(10, 1);
        Darray b(10, 2);
        Darray c(10, 3);

        a += 44;

        cout << "a -> "; a.show_arr();
        cout << "b -> "; b.show_arr();
        cout << "c -> "; c.show_arr();


    }
    catch (const Darray::MyException & ex) {
        cout << ex.what() <<" - " << ex.GetExcepType() << endl;

    }
    return 0;
}


//Надо добавить:
//Конструктор перемещения
//Оператор присваивания перемещением
//Конструктор преобразования через массив int
//Оператор суммы с семантикой перемещения ??
