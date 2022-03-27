// Chapter 20, Exercise 07: find the lexicographical last string in an unsorted vector<string>.

#include "std_lib_facilities.h"

template <typename Iterator>
Iterator high(Iterator first, Iterator last)
{
    Iterator high = first;
    for (Iterator p = first; p != last; p++)
        if (*high < *p)
            high = p;
    return high;
}

//----------------------------------------------------------------------

int main()
try
{
    vector<string> vs;
    ifstream ifs{"forgotten.txt"};
    string s;
    while (ifs >> s)
        vs.push_back(s);
    auto p = high(vs.begin(), vs.end());
    cout << (p != vs.end() ? *p : "Not found!") << endl;
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
