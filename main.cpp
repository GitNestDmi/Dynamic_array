#include <darray.h>



int main()
{
    Darray a(5, 0);
    a.show_arr();
    a[0] = 36;
    a[1] = a[1]+ 4;
    a[2] -= 2;
    a[3] *= 2;
    a[10] /= 2;
    a.show_arr();
    Darray b(5, 45);
    a += b;

    a.show_arr();
    return 0;
}
