#include "std_lib_facilities.h"


void my_copy(int *f1, int *e1, int *f2)
{
    for (; f1 != e1;)
        *f2++ = *f1++;
}

void print(int *start, int *end)
{
    for (int *p = start; p != end;)
    {
        cout << *p;
        if (++p != end)
            cout << ", ";
    }
    cout << endl;
}

int main()
try
{
    const int n = 3;
    int mas[n] = {7, 3, 1988};
    print(mas, mas + n);
    int dest[n];
    my_copy(mas, mas + n, dest);
    print(dest, dest + n);
}
catch (exception &e)
{
    cerr << "exception: " << e.what() << endl;
}
catch (...)
{
    cerr << "exception\n";
}
