// Chapter 20, Exercise 05: Define >> and << for vector.

#include "std_lib_facilities.h"

template <typename T>
istream &operator>>(istream &is, vector<T> &v)
{
    char ch;
    is >> ch;
    if (ch != '{')
        error("Vector must start with { and end with }");
    T temp;
    while (is)
    {
        is >> ch;
        if (ch == '}')
            break;
        is.unget();
        is >> temp;
        if (is)
            v.push_back(temp);
        else
            error("Wrong input data!");
    }
    return is;
}

//--------------------------------------------------------------------

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    int n = v.size();
    if (n == 0)
        return os;
    cout << "{ ";
    for (int i = 0; i < n; i++)
    {
        cout << v[i];
        if (i < n - 1)
            cout << ", ";
    }
    cout << " }\n";
    return os;
}

//--------------------------------------------------------------------

int main()
try
{
    
    vector<int> mv;
    cout << "Input vector of integers: ";
    cin >> mv;
    cout << mv;

    vector<double> md;
    cout << "Input vector of real numbers: ";
    cin >> md;
    cout << md;

    vector<string> ms;
    cout << "Input vector of strings: ";
    cin >> ms;
    cout << ms;
}
catch (Range_error &re)
{
    cerr << "Bad index: " << re.index << "\n";
}
catch (const std::exception &e)
{
    cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Some kind of exception\n";
    return 2;
}
