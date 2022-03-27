#include "std_lib_facilities.h"

void mystrcmp(const string &str1, const string &str2)
{
    cout << str1 << " ";
    if (str1 < str2)
        cout << "<";
    else if (str1 == str2)
        cout << "==";
    else
        cout << ">";
    cout << " " << str2 << endl << endl;
}

void farr(const char *ar)
{
    const char *str1 = "Hello", *str2 = "Howdy";

    cout << "ar size == " << strlen(ar) << endl;

    if (strcmp(ar, str1) == 0)
        cout << "ar == " << str1 << endl;

    mystrcmp(ar, str2);

    char copystr[strlen(ar)];
    strcpy(copystr, ar);
}

// for string, vector and list
template <class T>
void fcont(const T &cont)
{
    const string str1 = "Hello", str2 = "Howdy";
    string str3;

    cout << "cont size == " << cont.size() << endl;

    if (str1.size() == cont.size())
        for (auto p = cont.begin(); p != cont.end(); p++)
            str3 += *p;

    if (str3 == str1)
        cout << "cont == " << str1 << endl;

    mystrcmp(str3, str2);

    T copycont{cont};
}

int main()
try
{
    char arr[6] = "Hello";
    farr(arr);
    
    string s = "Hello";
    fcont(s);
    vector<char> vch{'H', 'e', 'l', 'l', 'o'};
    fcont(vch);
    list<char> lch{'H', 'e', 'l', 'l', 'o'};
    fcont(lch);
}
catch (exception &e)
{
    cerr << "exception: " << e.what() << endl;
}
catch (...)
{
    cerr << "exception\n";
}
