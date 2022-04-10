// Chapter 20, Exercise 18: define a range-checked iterator for vector (a random-access iterator)

#include "std_lib_facilities.h"

template <typename T>
struct my_allocator
{
    T *allocate(int n);
    void deallocate(T *p) { free(p); }
    void construct(T *p, const T &v) { new (p) T(v); }
    void destroy(T *p) { p->~T(); }
};

template <typename T>
T *my_allocator<T>::allocate(int n)
{
    T *p = static_cast<T *>(malloc(n * sizeof(T)));
    if (!p)
        error("No memory for allocating");
    return p;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

template <typename T, typename A = my_allocator<T>>
class my_vector
{
    A alloc;
    int sz;
    T *elem;
    int space;

public:
    using iterator = T *;
    class iterator_rc;

    my_vector() : sz{0}, elem{nullptr}, space{0} {}
    explicit my_vector(int n);
    my_vector(initializer_list<T> lst);

    my_vector(const my_vector &);            // copy constructor
    my_vector &operator=(const my_vector &); // copy assignment

    my_vector(my_vector &&);            // move constructor
    my_vector &operator=(my_vector &&); // move assignment

    ~my_vector();

    T &operator[](int n) { return elem[n]; }
    const T &operator[](int n) const { return elem[n]; }

    T &at(int n);
    const T &at(int n) const; // checked access

    int size() const { return sz; }
    int capacity() const { return space; }

    void reserve(int newalloc);
    void push_back(const T &val);
    void push_front(const T &val);
    void resize(int newsize, T val = T());

    iterator begin() { return elem; }
    iterator end() { return elem + sz; }
};
//--------------------------------------------------------------------

template <typename T, typename A>
class my_vector<T, A>::iterator_rc
{
    iterator curr, first, last;

public:
    iterator_rc(iterator c, iterator f, iterator l) : curr{c}, first{f}, last{l} {}

    T &operator*() { return *curr; }
    const T &operator*() const { return *curr; }

    iterator_rc &operator++()
    {
        if (curr == last - 1)
            throw Range_error(last - first);
        ++curr;
        return *this;
    }
    iterator_rc &operator--()
    {
        if (curr == first)
            throw Range_error(-1);
        --curr;
        return *this;
    }
    iterator_rc &operator+=(int n)
    {
        if (n >= last - curr)
            throw Range_error(curr + n - first);
        curr += n;
        return *this;
    }
    iterator_rc &operator-=(int n)
    {
        if (n > curr - first)
            throw Range_error(curr - n - first);
        curr -= n;
        return *this;
    }

    bool operator==(iterator_rc const &other) const { return curr == other.curr; }
    bool operator!=(iterator_rc const &other) const { return !(*this == other); }
};

//--------------------------------------------------------------------

template <typename T, typename A>
my_vector<T, A>::my_vector(int n)
    : sz{n}, elem{alloc.allocate(n)}, space{n}
{
    for (int i = 0; i < sz; i++)
        alloc.construct(&elem[i], T());
}
//--------------------------------------------------------------------

template <typename T, typename A>
my_vector<T, A>::my_vector(initializer_list<T> lst)
    : sz{(int)lst.size()}, elem{alloc.allocate(sz)}, space{sz}
{
    T *ptr = elem;
    for (const T &p : lst)
        alloc.construct(ptr++, p);
}

//--------------------------------------------------------------------

template <typename T, typename A>
my_vector<T, A>::my_vector(const my_vector &origin)
    : sz{origin.sz}, elem{alloc.allocate(sz)}, space{origin.space}
{
    for (int i = 0; i < sz; i++)
        alloc.construct(&elem[i], origin.elem[i]);
}
//--------------------------------------------------------------------

template <typename T, typename A>
my_vector<T, A> &my_vector<T, A>::operator=(const my_vector &origin)
{
    if (this == &origin) // self-assignment, no work needed
        return *this;

    if (origin.sz <= space) // enough space, no need for new allocation
    {
        for (int i = 0; i < origin.sz; i++)
            alloc.construct(&elem[i], origin.elem[i]);
        sz = origin.sz;
        return *this;
    }

    T *p = alloc.allocate(origin.sz);   // allocate new space
    for (int i = 0; i < origin.sz; i++) // copy new elements
        alloc.construct(&p[i], origin.elem[i]);

    for (int i = 0; i < sz; i++) // destroy old objects
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem); // deallocate old space

    space = sz = origin.sz;
    elem = p;
    return *this;
}
//--------------------------------------------------------------------

template <typename T, typename A>
my_vector<T, A>::~my_vector()
{
    for (int i = 0; i < sz; i++) // destroy objects
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem); // deallocate space
}
//--------------------------------------------------------------------

template <typename T, typename A>
T &my_vector<T, A>::at(int n)
{
    if (n < 0 || n >= sz)
        throw Range_error(n);
    return elem[n];
}
//--------------------------------------------------------------------

template <typename T, typename A>
const T &my_vector<T, A>::at(int n) const
{
    if (n < 0 || n >= sz)
        throw Range_error(n);
    return elem[n];
}
//--------------------------------------------------------------------

template <typename T, typename A>
void my_vector<T, A>::reserve(int newalloc)
{
    if (newalloc <= space)
        return;
    T *p = alloc.allocate(newalloc);
    for (int i = 0; i < sz; i++)
        alloc.construct(&p[i], elem[i]);
    for (int i = 0; i < sz; i++)
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem);
    elem = p;
    space = newalloc;
}
//--------------------------------------------------------------------

template <typename T, typename A>
void my_vector<T, A>::push_back(const T &val)
{
    if (space == 0)
        reserve(8);
    else if (sz == space)
        reserve(2 * sz);
    alloc.construct(&elem[sz], val);
    sz++;
}
//--------------------------------------------------------------------

template <typename T, typename A>
void my_vector<T, A>::push_front(const T &val)
{
    if (space == 0)
        reserve(8);
    else if (sz == space)
        reserve(2 * sz);
    for (int i = sz; i > 0; i--)
        alloc.construct(&elem[i], elem[i - 1]);
    alloc.construct(&elem[0], val);
    sz++;
}
//--------------------------------------------------------------------

template <typename T, typename A>
void my_vector<T, A>::resize(int newsize, T val)
{
    if (newsize < 0)
        throw Range_error(newsize);
    reserve(newsize);
    // create
    for (int i = sz; i < newsize; i++)
        alloc.construct(&elem[i], val);
    // destroy
    for (int i = newsize; i < sz; i++)
        alloc.destroy(&elem[i]);
    sz = newsize;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------

// vector diagnostics
template <typename T>
void diag_vec(const my_vector<T> &v, const string &description)
{
    cout << description << "\n";
    cout << "\tsize: " << v.size() << "\n";
    cout << "\tcapacity: " << v.capacity() << "\n\t";
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << ' ';
    cout << "\n";
}
//--------------------------------------------------------------------

int main()
try
{
    my_vector<int> mv{1, 2, 3, 4};
    my_vector<int>::iterator_rc it{mv.begin(), mv.begin(), mv.end()};
    //--it; // range error
    it += 2;
    cout << *it << endl;
    it += 2; // range error
}
catch (const std::exception &e)
{
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Some kind of exception\n";
    return 2;
}
