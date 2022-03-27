// Chapter 20, Exercise 04: Find and fix the errors in the Jack-and-Jill example
// from 20.3.1 by using STL techniques.

#include "std_lib_facilities.h"

double *get_from_jack(int *count)
{
    string filename{"jack.txt"};
    ifstream ifs{filename};
    if (!ifs)
        error("Cannot open a file", filename);
    int n = 5, i = 0;
    double *data = new double[n];
    while (ifs >> data[i++])
        if (i == n)
        {
            double *data2 = new double[2 * n];
            for (int i = 0; i < n; i++)
                data2[i] = data[i];
            delete[] data;
            data = data2;
            n *= 2;
        }
    *count = i - 1;
    return data;
}

vector<double> *get_from_jill()
{
    string filename{"jill.txt"};
    ifstream ifs{filename};
    if (!ifs)
        error("Cannot open a file", filename);
    vector<double> *v = new vector<double>;
    double d;
    while (ifs >> d)
        v->push_back(d);
    return v;
}

template <typename Iterator>
Iterator high(Iterator first, Iterator last)
{
    Iterator high = first;
    for (Iterator p = first; p != last; p++)
        if (*high < *p)
            high = p;
    return high;
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

void fct()
{
    int jack_count = 0;
    double *jack_data = get_from_jack(&jack_count);
    if (!jack_count)
        error("Jack's data is empty!");
    print(jack_data, jack_data + jack_count);
    double *jack_high = high(jack_data, jack_data + jack_count);
    cout << "Jack's max: " << *jack_high << endl;

    vector<double> *jill_data = get_from_jill();
    vector<double> &v = *jill_data;
    if (v.begin() == v.end())
        error("Jill's data is empty!");
    print(&v[0], &v[0] + v.size());
    double *jill_high = high(&v[0], &v[0] + v.size());
    cout << "Jill's max: " << *jill_high << endl;

    delete[] jack_data;
    delete jill_data;
}

int main()
try
{
    fct();
}
catch (exception &e)
{
    cerr << "exception: " << e.what() << endl;
}
catch (...)
{
    cerr << "exception\n";
}
