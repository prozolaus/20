// Chapter 20, Exercise 17: define an ownership_vector that holds pointers to objects like
// pvector, but provides a mechanism for the user to decide which objects are
// owned by the vector, i.e., which objects are deleted by the destructor. Hint:
// Chapter 13

#include "std_lib_facilities.h"

// holds pointers to objects; if the object is a pointer, it will be deleted
// when the destructor is invoked; if it is a reference, it won't
template <class Elem>
class ownership_vector
{
    vector<Elem *> elems;
    vector<Elem *> owned;

public:
    using size_type = unsigned long;

    ownership_vector() : owned() {}
    ownership_vector(Elem *d) { push_back(d); }
    ownership_vector(Elem &d) { push_back(d); }

    ~ownership_vector();

    Elem *operator[](size_type n) { return elems[n]; }
    const Elem *const operator[](size_type n) const { return elems[n]; }

    void push_back(Elem *d)
    {
        elems.push_back(d);
        owned.push_back(d);
    }
    void push_back(Elem &d) { elems.push_back(&d); }

    size_type size() const { return elems.size(); }
};

//------------------------------------------------------------------------------

template <class Elem>
ownership_vector<Elem>::~ownership_vector()
{
    for (int i = 0; i < owned.size(); ++i)
    {
        cout << "Deleting " << *owned[i] << "\n";
        delete owned[i];
    }
}

//----------------------------------------------------------------------

void f(int &i1, int &i2, int &i3)
{
    ownership_vector<int> osv(i1);
    // fill with pointers and references in turn
    osv.push_back(new int(2));
    osv.push_back(i2);
    osv.push_back(new int(4));
    osv.push_back(i3);
    osv.push_back(new int(6));

    for (int i = 0; i < osv.size(); ++i)
        cout << *osv[i] << ", ";
    cout << endl;
    // destructor called here: should destroy 2, 4 and 6
}

//----------------------------------------------------------------------

int main()
try
{
    vector<int> v{1, 3, 5};
    f(v[0], v[1], v[2]);
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
