#include "std_lib_facilities.h"


template<typename Iter>
void advance(Iter &p, int n)
{
    while (n > 0)
    {
        p++;
        n--;        
    }
    while (n < 0)
    {
        p--;
        n++;        
    }
}

int main()
try
{

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
