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

    mylist() : first{new Link<Elem>()}, last{first}, sz{0} {}

    iterator begin() { return iterator{first}; }
    iterator end() { return iterator{last}; }

    iterator insert(iterator p, const Elem &v);
    iterator erase(iterator p);

    int size() const { return sz; }
    void push_back(const Elem &v);
    void push_front(const Elem &v);
    void pop_front() { erase(begin()); }
    void pop_back();

    Elem &front() { return first->val; }
    Elem &back();
};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

template <typename Elem>
void mylist<Elem>::pop_back()
{
    if (first == last)
        return;
    auto i = end();
    --i;
    erase(i);
}

//----------------------------------------------------------------------

template <typename Elem>
typename mylist<Elem>::iterator mylist<Elem>::erase(iterator p)
{
    if (first == last || p == end())
        return p;
    Link<Elem> *curr = p.get_link();
    if (curr->prev)
    {
        curr->prev->succ = curr->succ;
        curr->succ->prev = curr->prev;
    }
    else
    {
        curr->succ->prev = nullptr;
        first = curr->succ;
    }
    ++p;
    delete curr;
    sz--;
    return p;
}

//----------------------------------------------------------------------

template <typename Elem>
typename mylist<Elem>::iterator mylist<Elem>::insert(iterator p, const Elem &v)
{
    if (p == end())
        error("insert() cannot add a link after the last element!");
    if (first == last || p == begin())
    {
        push_front(v);
        return begin();
    }
    Link<Elem> *curr = p.get_link();
    Link<Elem> *le = new Link<Elem>{v, curr->prev, curr};
    curr->prev->succ = le;
    curr->prev = le;
    --p;
    sz++;
    return p;
}

//----------------------------------------------------------------------

template <typename Elem>
void mylist<Elem>::push_front(const Elem &v)
{
    Link<Elem> *temp = new Link<Elem>{v, nullptr, first};
    first->prev = temp;
    first = temp;
    sz++;
}

//----------------------------------------------------------------------

template <typename Elem>
void mylist<Elem>::push_back(const Elem &v)
{
    if (first == last)
    {
        first = new Link<Elem>{v, nullptr, last};
        last->prev = first;
    }
    else
    {
        Link<Elem> *p = new Link<Elem>{v, last->prev, last};
        last->prev->succ = p;
        last->prev = p;
    }
    sz++;
}

//----------------------------------------------------------------------

template <typename Elem>
Elem &mylist<Elem>::back()
{
    if (first == last)
        return first->val;
    return last->prev->val;
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
    print(lst.begin(), lst.end());
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
