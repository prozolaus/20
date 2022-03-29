#include "std_lib_facilities.h"

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

//----------------------------------------------------------------------

void copy_list_to_vector(const list<int> &l, vector<double> &v)
{
    v.clear();
    for (list<int>::const_iterator i = l.begin(); i != l.end(); i++)
        v.push_back(*i);
}

//----------------------------------------------------------------------

int main()
try
{
    list<int> li{3, 1, 5, 2, 4};
    vector<double> vd{1.1, 2.2};
    copy_list_to_vector(li, vd);
    sort(vd.begin(),vd.end());
    print(vd.begin(),vd.end());
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
