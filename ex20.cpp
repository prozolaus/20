// Chapter 20, Exercise 20: compare vector and list by timing how long it takes
// to insert N random ints into a vector/list such that the container is always
// sorted. For which N is the list faster than the vector?

#include "std_lib_facilities.h"

//----------------------------------------------------------------------

template <typename T>
void insert_and_sort(T &container, int n)
{
    int r = rand() % n;
    typename T::iterator it = container.begin();
    for (; it != container.end() && (*it <= r); ++it)
        ;
    container.insert(it, r);
}

int main()
try
{
    vector<int> vec;
    for (int i = 5; i < 200; i += 5)
        vec.push_back(i);

    const int reps = 20;
    for (vector<int>::iterator p = vec.begin(); p != vec.end(); ++p)
    {
        double vtime, ltime;
        for (int i = 0; i < reps; i++)
        {
            vector<int> v;
            list<int> l;

            clock_t vt1 = clock();
            for (int i = 1; i < *p; i++)
                insert_and_sort(v, i);
            clock_t vt2 = clock();
            vtime += double(vt2 - vt1) / CLOCKS_PER_SEC;

            clock_t lt1 = clock();
            for (int i = 1; i < *p; i++)
                insert_and_sort(l, i);
            clock_t lt2 = clock();
            ltime += double(lt2 - lt1) / CLOCKS_PER_SEC;
        }
        vtime = vtime / reps;
        ltime = ltime / reps;

        cout << "n = " << *p << endl;
        cout << "Vector time, s: " << vtime << endl;
        cout << "List time, s: " << ltime << endl;
        cout << "Difference, s: " << ltime - vtime << endl;
        cout << "Difference, %: " << 100 * (ltime - vtime) / vtime << endl;
        cout << endl;
    }
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
