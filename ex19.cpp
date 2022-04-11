// Chapter 20, Exercise 19: define a range-checked iterator for list (a bidirectional iterator)

#include "std_lib_facilities.h"

template <typename Elem>
class list_iterator_rc
{
    typename list<Elem>::iterator curr, first, last;

public:
    using iterator = typename list<Elem>::iterator;
    list_iterator_rc(iterator c, iterator f, iterator l)
        : curr{c}, first{f}, last{l}
    {
    }
    Elem &operator*() { return *curr; }
    const Elem &operator*() const { return *curr; }
    Elem *operator->() { return &(*curr); }

    list_iterator_rc &operator++()
    {
        ++curr;
        if (curr == last)
            error("the current iterator is past the last element!");
        return *this;
    }
    list_iterator_rc &operator--()
    {
        if (curr == first)
            error("the current iterator is before the first element!");
        --curr;
        return *this;
    }
};

//----------------------------------------------------------------------
struct A
{
    A(int i1, int i2) : a{i1}, b{i2} {}
    int a;
    int b;
};
//----------------------------------------------------------------------

int main()
try
{
    list<int> lst{1, 2, 3, 4};
    list_iterator_rc<int> lirc{lst.begin(), lst.begin(), lst.end()};
    //--lirc; // exception
    for (int i = 0; i < lst.size() - 1; ++i, ++lirc)
        cout << *lirc << " ";
    cout << *lirc << "\n";
    //++lirc; // exception

    A a1(0, 1);
    A a2(11, 22);
    list<A> la;
    la.push_back(a1);
    la.push_back(a2);

    list_iterator_rc<A> lirca{la.begin(), la.begin(), la.end()};
    ++lirca;
    cout << lirca->a << ", " << lirca->b << endl;
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
