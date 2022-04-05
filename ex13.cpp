// Chapter 20, Exercise 13: modify exercise 12 to use 0 to represent the one past the last element (end()) instead of allocating a real Link

#include "std_lib_facilities.h"

template <typename Elem>
struct Link
{
    Link(const Elem &v = Elem(), Link<Elem> *p = nullptr, Link<Elem> *s = nullptr) : val{v}, prev{p}, succ{s} {}
    Link<Elem> *prev;
    Link<Elem> *succ;
    Elem val;
};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

template <typename Elem>
class mylist
{
    Link<Elem> *first;
    Link<Elem> *last;
    int sz;

public:
    class iterator;

    mylist() : first{nullptr}, last{first}, sz{0} {}
    ~mylist();

    iterator begin() { return iterator{first}; }
    iterator end() { return nullptr; }

    iterator insert(iterator p, const Elem &v);
    iterator erase(iterator p);

    void push_back(const Elem &v);
    void push_front(const Elem &v);
    void pop_front();
    void pop_back();

    Elem &front();
    Elem &back();
};

//----------------------------------------------------------------------

template <typename Elem>
mylist<Elem>::~mylist()
{
    cout << "Destructor:\n";
    for (auto i = begin(); i != end();)
    {
        Link<Elem> *le = i.get_link();
        ++i;
        delete le;
        cout << "deleted a link\n";
    }
}

//----------------------------------------------------------------------

template <typename Elem>
void mylist<Elem>::push_front(const Elem &v)
{
    Link<Elem> *temp = new Link<Elem>{v, nullptr, first};
    if (first == last)
        first = temp;
    else
    {
        first->prev = temp;
        first = temp;
    }
    sz++;
}

//----------------------------------------------------------------------

template <typename Elem>
void mylist<Elem>::push_back(const Elem &v)
{
    if (first == last)
        first = new Link<Elem>{v, nullptr, last};
    else
    {
        Link<Elem> *p = first;
        for (int i = 0; i < sz - 1; i++)
            p = p->succ;
        Link<Elem> *temp = new Link<Elem>{v, p, last};
        p->succ = temp;
    }
    sz++;
}

//----------------------------------------------------------------------

template <typename Elem>
class mylist<Elem>::iterator
{
    Link<Elem> *curr;

public:
    iterator(Link<Elem> *p) : curr{p} {}
    Link<Elem> *get_link() { return curr; }
    iterator &operator++()
    {
        curr = curr->succ;
        return *this;
    }
    iterator &operator--()
    {
        curr = curr->prev;
        return *this;
    }
    Elem &operator*() { return curr->val; }
    bool operator==(const iterator &b) const { return curr == b.curr; }
    bool operator!=(const iterator &b) const { return curr != b.curr; }
};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

template <typename Iterator>
Iterator high(Iterator first, Iterator last)
{
    Iterator high = first;
    for (Iterator p = first; p != last; ++p)
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

//----------------------------------------------------------------------
//----------------------------------------------------------------------

int main()
try
{
    mylist<int> lst;
    for (int x; cin >> x;)
        lst.push_front(x);
    mylist<int>::iterator p = high(lst.begin(), lst.end());
    cout << (p != lst.end() ? "The largest value is " + to_string(*p) : "Not found!") << endl;
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
