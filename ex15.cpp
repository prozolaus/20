// Chapter 20, Exercise 15: define a pvector to be like a vector of pointers
// except that it contains pointer to objects and its destructor deletes each object

#include "std_lib_facilities.h"

template <class Elem>
class pvector
{
    vector<Elem *> elems;

public:
    using size_type = unsigned long;
    using iterator = typename vector<Elem *>::iterator;
    using const_iterator = typename vector<Elem *>::const_iterator;

    iterator begin() { return elems.begin(); }
    const_iterator begin() const { return elems.begin(); }
    iterator end() { return elems.end(); }
    const_iterator end() const { return elems.end(); }

    pvector() : elems() {}
    explicit pvector(size_type n);
    ~pvector();

    size_type size() const { return elems.size(); }
    void push_back(const Elem &x);
    void push_back(Elem *x);
    Elem *operator[](size_type i) { return elems[i]; }
    const Elem *operator[](size_type i) const { return elems[i]; }
};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

template <class Elem>
pvector<Elem>::pvector(size_type n)
    : elems(n)
{
    for (size_type i = 0; i < n; i++)
        elems[i] = new Elem();
}

//----------------------------------------------------------------------

template <class Elem>
void pvector<Elem>::push_back(Elem *x)
{
    if (x == nullptr)
        error("push_back(): nullptr");
    elems.push_back(x);
}

//----------------------------------------------------------------------

template <class Elem>
void pvector<Elem>::push_back(const Elem &x)
{
    Elem *e = new Elem(x);
    elems.push_back(e);
}

//----------------------------------------------------------------------

template <class Elem>
pvector<Elem>::~pvector()
{
    cout << "Destructor:\n";
    if (size() > 0)
        cout << "deleted elements: ";
    for (size_type i = 0; i < size(); i++)
    {
        delete elems[i];
        cout << i << (i < size() - 1 ? ", " : "\n");
    }
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

template <typename Iter>
void print(Iter start, Iter end)
{
    for (Iter p = start; p != end;)
    {
        cout << **p;
        if (++p != end)
            cout << ", ";
    }
    cout << endl;
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

int main()
try
{
    const int n = 10;
    pvector<int> pv(n);
    for (int i = 0; i < n; i++)
        *pv[i] = n - i;
    *pv[0] = 14;
    int *ptr = new int{55};
    pv.push_back(ptr);
    pv.push_back(99);
    print(pv.begin(), pv.end());
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
