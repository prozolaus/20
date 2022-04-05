// Chapter 20, Exercise 14: define a singly-linked list, my_slist, in the style of
// std::list; determine operations that can be eliminated because there are no back pointers.

#include "std_lib_facilities.h"

template <typename Elem>
struct Link
{
    Link(const Elem &v = Elem(), Link<Elem> *s = nullptr) : val{v}, succ{s} {}
    Link<Elem> *succ;
    Elem val;
};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

template <typename Elem>
class my_slist
{
    Link<Elem> *first;
    Link<Elem> *last;
    int sz;

public:
    class iterator;

    my_slist() : first{nullptr}, last{first}, sz{0} {}
    ~my_slist();

    iterator begin() { return iterator{first}; }
    iterator end() { return nullptr; }

    iterator insert_after(iterator p, const Elem &v);
    iterator erase_after(iterator p);

    int size() const { return sz; }
    void push_front(const Elem &v);
    void pop_front();

    Elem &front();
};

//----------------------------------------------------------------------
//----------------------------------------------------------------------

template <typename Elem>
my_slist<Elem>::~my_slist()
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
void my_slist<Elem>::pop_front()
{
    if (first == last)
        error("pop_front(): The list is empty!");
    Link<Elem> *temp = first;
    first = first->succ;
    delete temp;
    sz--;
}

//----------------------------------------------------------------------

template <typename Elem>
Elem &my_slist<Elem>::front()
{
    if (first == last)
        error("front(): The list is empty!");
    return first->val;
}

//----------------------------------------------------------------------

template <typename Elem>
typename my_slist<Elem>::iterator my_slist<Elem>::erase_after(iterator p)
{
    if (p == end())
    {
        if (first == last)
            error("erase_after(): The list is empty!");
        error("erase_after(): It is nothing to erase after the last link!");
    }
    Link<Elem> *curr = p.get_link();
    ++p;
    Link<Elem> *link_to_erase = p.get_link();
    if (sz == 1 || link_to_erase == last)
        error("Cannot erase the last link!");
    ++p;
    Link<Elem> *next = p.get_link();
    curr->succ = next;
    delete link_to_erase;
    sz--;
    return iterator{next};
}

//----------------------------------------------------------------------

template <typename Elem>
typename my_slist<Elem>::iterator my_slist<Elem>::insert_after(iterator p, const Elem &v)
{
    if (p == end())
        error("insert() cannot add a link after the last element!");
    Link<Elem> *curr = p.get_link();
    ++p;
    Link<Elem> *curr2 = p.get_link();
    Link<Elem> *le = new Link<Elem>{v, curr2};
    curr->succ = le;
    sz++;
    return iterator{le};
}

//----------------------------------------------------------------------

template <typename Elem>
void my_slist<Elem>::push_front(const Elem &v)
{
    first = new Link<Elem>{v, first};
    sz++;
}

//----------------------------------------------------------------------

template <typename Elem>
class my_slist<Elem>::iterator
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
    my_slist<int> lst;
    for (int x; cin >> x;)
        lst.push_front(x);
    lst.pop_front();
    auto l = lst.insert_after(lst.begin(), 99);
    lst.erase_after(l);
    my_slist<int>::iterator p = high(lst.begin(), lst.end());
    cout << (p != lst.end() ? "The largest value is " + to_string(*p) : "Not found!") << endl;
    print(lst.begin(), lst.end());
    cout << "the front element: " << lst.front() << endl;
    cout << "list size: " << lst.size() << endl;
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
