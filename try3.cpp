#include "std_lib_facilities.h"

void show_cmp(int r)
{
    if (r < 0)
        cout << "<";
    else if (r == 0)
        cout << "==";
    else
        cout << ">";
    cout << " mas" << endl;
}

void farr(const int *ar, const int n)
{
    const int count = 5, mas[] = {1, 2, 3, 4, 5};
    cout << "ar size == " << n << endl;

    cout << "ar == {";
    for (int i = 0; i < n; i++)
        cout << ar[i] << ((i == n - 1) ? "}\n" : ", ");

    int r = 0, nn = (count < n) ? count : n;
    for (int i = 0; i < nn && !r; i++)
    {
        if (mas[i] < ar[i])
            r = 1;
        else if (mas[i] > ar[i])
            r = -1;
    }
    if (!r && count != n)
        r = (nn == count) ? 1 : -1;

    cout << "ar ";
    show_cmp(r);

    char copyarr[n];
    for (int i = 0; i < n; i++)
        copyarr[i] = ar[i];
}

// for vector and list
template <class T>
void fcont(const T &vl)
{
    const int count = 5, mas[] = {1, 2, 3, 4, 5};
    int n = vl.size();
    cout << "vl size == " << n << endl;

    int i = 0;
    cout << "vl == {";
    for (auto p = vl.begin(); p != vl.end(); p++, i++)
        cout << *p << ((i == n - 1) ? "}\n" : ", ");

    int r = 0, nn = (count < n) ? count : n;
    auto p = vl.begin();
    for (int i = 0; i < nn && !r; i++, p++)
    {
        if (mas[i] < *p)
            r = 1;
        else if (mas[i] > *p)
            r = -1;
    }
    if (!r && count != n)
        r = (nn == count) ? 1 : -1;

    cout << "vl ";
    show_cmp(r);

    T copyvl{vl};
}

int main()
try
{
    int arr[] = {1, 2, 3, 4, 5};
    farr(arr, sizeof(arr) / sizeof(*arr));
    vector<int> vi{1, 2, 3, 4, 5};
    fcont(vi);
    list<int> li{1, 2, 3, 4, 5};
    fcont(li);
}
catch (exception &e)
{
    cerr << "exception: " << e.what() << endl;
}
catch (...)
{
    cerr << "exception\n";
}
