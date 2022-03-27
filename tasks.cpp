#include "std_lib_facilities.h"

template <typename Iter1, typename Iter2>
Iter2 my_copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
    for (; f1 != e1;)
        *f2++ = *f1++;
    return f2;
}

template <typename Iter>
void print(Iter start, Iter end)
{
    for (Iter p = start; p != end;)
    {
        cout << *p;
        if (++p != end)
            cout << ", ";
    }
    cout << endl;
}

template <typename Iter, typename Cont>
void print_pos(Iter p, const Cont &c)
{
    if (p == c.end())
        cout << "Not found!" << endl;
    else
        cout << p - c.begin() << endl;
}

int main()
try
{
    const int n = 10;
    int mas[n]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> l{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int mas2[n];
    for (int i = 0; i < n; i++)
        mas2[i] = mas[i];
    vector<int> v2{v};
    list<int> l2{l};

    for (int i = 0; i < n; i++)
        mas[i] += 2;
    for (int &i : v)
        i += 3;
    for (int &i : l)
        i += 5;

    // print(mas, mas + n);
    // print(v.begin(), v.end());
    // print(l.begin(), l.end());

    // my_copy(mas, mas + n, v2.begin());
    // my_copy(l.begin(), l.end(), mas2);

    // print(mas2, mas2 + n);
    // print(v2.begin(), v2.end());

    vector<int>::iterator p = find(v.begin(), v.end(), 3);
    print_pos(p, v);
    p = find(v2.begin(), v2.end(), 27);
    print_pos(p, v2);
}
catch (const std::exception &e)
{
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Some kind of exception\n";
    return 2;
}
