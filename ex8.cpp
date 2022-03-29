// Chapter 20, Exercise 08: define a function that counts the number of characters in a Document.

#include "std_lib_facilities.h"

using Line = vector<char>;

class Text_iterator
{
    list<Line>::iterator ln;
    Line::iterator pos;

public:
    Text_iterator(list<Line>::iterator ll, Line::iterator pp) : ln{ll}, pos{pp} {}
    char &operator*() { return *pos; }
    Text_iterator &operator++();
    bool operator==(const Text_iterator &other) const { return ln == other.ln && pos == other.pos; }
    bool operator!=(const Text_iterator &other) const { return !(*this == other); }
    list<Line>::iterator get_ln() { return ln; }
    Line::iterator get_pos() { return pos; }
};

//----------------------------------------------------------------------

Text_iterator &Text_iterator::operator++()
{
    ++pos;
    if (pos == ln->end())
    {
        ++ln;
        pos = ln->begin();
    }
    return *this;
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

struct Document
{
    list<Line> line;
    Document() { line.push_back(Line{}); }

    Text_iterator begin() { return Text_iterator{line.begin(), line.begin()->begin()}; }
    Text_iterator end();
};

//----------------------------------------------------------------------

Text_iterator Document::end()
{
    list<Line>::iterator last = line.end();
    --last; // we know that the document is not empty
    return Text_iterator(last, last->end());
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

istream &operator>>(istream &is, Document &d)
{
    for (char ch; is.get(ch);)
    {
        d.line.back().push_back(ch);
        if (ch == '\n')
            d.line.push_back(Line{});
    }
    if (d.line.back().size())
        d.line.push_back(Line{});
    return is;
}

//----------------------------------------------------------------------

void erase_line(Document &d, int n)
{
    if (n < 1 || d.line.size() <= n)
        return;
    auto p = d.line.begin();
    advance(p, n - 1);
    d.line.erase(p);
}

//----------------------------------------------------------------------

template <typename Iter, typename T>
Iter find(Iter first, Iter last, const T &val)
{
    for (Iter p = first; p != last; ++p)
        if (*p == val)
            return p;
    return last;
}

//----------------------------------------------------------------------

bool match(Text_iterator first, Text_iterator last, const string &s)
{
    if (s.empty())
        error("match(): empty string!");
    for (auto ps = s.begin(); first != last && ps != s.end(); ++first, ++ps)
        if (*first != *ps)
            return false;
    return true;
}

//----------------------------------------------------------------------

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string &s)
{
    if (s.size() == 0)
        return last;
    char first_char = s[0];
    while (true)
    {
        auto p = ::find(first, last, first_char);
        if (p == last || match(p, last, s))
            return p;
        first = ++p;
    }
}

//----------------------------------------------------------------------

int get_n_count(const string &s)
// returns the number of lines
{
    int n_count = 0;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '\n')
            ++n_count;
    return n_count;
}

//----------------------------------------------------------------------

Text_iterator find_and_replace(Document &d, Text_iterator first, Text_iterator last, const string &oldstr, const string &newstr)
// returns an iterator pointing to the position after the replaced text
{
    Text_iterator ti = find_txt(first, last, oldstr);
    if (ti == last) // if the text is not found
        return last;

    string s;
    list<Line>::iterator ln = ti.get_ln(), ln2;
    Line::iterator li = ln->begin();
    int index = ti.get_pos() - li; // index where the first character starts
    for (int i = 0; i < index; i++)
        s.push_back(*li++); // copying the first part of the string where the replacement occurs
    s += newstr;

    int n_count_old = get_n_count(oldstr);
    int n_count_new = get_n_count(newstr) + 1;

    int delta; // distance between the end of a line and the of the replaced line
    if (n_count_old > 0)
    {
        for (int i = 0; i < n_count_old; i++)
            ln = d.line.erase(ln); // if we delete a line from beginning to end
        delta = ln->size() - (oldstr.size() - oldstr.rfind("\n") - 1);
    }
    else // if we replace only one line (n_count_old == 0)
        delta = ln->size() - (index + oldstr.size());

    li = ln->end();
    advance(li, -delta);
    while (li != ln->end())
        s.push_back(*li++); // copying the last part of the string where the replacement occurs
    ln = d.line.erase(ln);

    for (int i = 0, k = 0; i < n_count_new; i++) // insert updated lines; the loop is executed at least once
        for (vector<char> v; k < s.size(); k++)
        {
            if (s[k] == '\n')
            {
                v.push_back(s[k++]);
                ln2 = d.line.insert(ln, v);
                break;
            }
            v.push_back(s[k]);
        }

    li = ln2->end();
    advance(li, -delta);
    return Text_iterator{ln2, li};
}

int find_and_replace_all(Document &d, Text_iterator first, Text_iterator last, const string &oldstr, const string &newstr)
{
    Text_iterator p = find_and_replace(d, first, last, oldstr, newstr);
    int count = 0;
    for (; p != last; count++)
        p = find_and_replace(d, p, last, oldstr, newstr);
    return count;
}

//----------------------------------------------------------------------

int count_characters(Document &d)
{
    int count = 0;
    for (auto p = d.begin(); p != d.end(); ++p)
        count++;
    return count;
}

//----------------------------------------------------------------------

void print(Document &d)
{
    for (Text_iterator p = d.begin(); p != d.end(); ++p)
        cout << *p;
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------

int main()
try
{
    Document d;
    ifstream ifs{"forgotten.txt"};
    ifs >> d;
    if (!ifs)
        error("Cannot open file");
    int count = count_characters(d);
    cout << count << endl;
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
