#include <iostream>
#include <fstream>
#include <cstring>
#include "clist.h"

#define BUFSIZE 4

class StrBuf;

class MyStr
{
private:
    char s[BUFSIZE+1];
public:
    MyStr() {s[0] = '\0';}
    MyStr(const char *src) { strncpy(s, src, BUFSIZE); s[BUFSIZE] = '\0'; }
    MyStr &operator=(const MyStr &src);
    char& operator[](const size_t index) { return s[index]; }
    friend std::ostream& operator<<(std::ostream &out, const MyStr &str) { out << str.s; return out; }
    friend StrBuf;
};

MyStr& MyStr::operator=(const MyStr &src)
{
    if (this == &src)
        return *this;
    strncpy(s, src.s, BUFSIZE);
    s[BUFSIZE] = '\0';
    return *this;
}

class StrBuf
{
private:
    size_t N, remainder;
    CList2<MyStr> buf;
public:
    StrBuf() { N = remainder = 0; }
    StrBuf(const char *str);
    StrBuf(const StrBuf &src);
    void Clean() { N = remainder = 0; buf.Clean(); }
    void Cat(const char *str);
    size_t Len() { return N * BUFSIZE - remainder; }
    int Cut(size_t new_size);
    void Copy(char *dest);
    int Copy(char *dest, size_t begin, size_t end);
    int Find(const char c);
    int Find(const char *substr);
    int Insert(const char *src, size_t pos);
    int Replace(const char *src, size_t begin, size_t end);
    CList2<MyStr>::iterator begin() { return buf.begin(); }
    CList2<MyStr>::iterator end() { return buf.end(); }
    char &operator[](const size_t index);
    StrBuf &operator=(const StrBuf &src);
    friend std::ostream& operator<<(std::ostream &out, StrBuf &S) {
        for (const auto &x : S)
            out << x << " ";
        return out;
    }
    friend std::ifstream& operator>>(std::ifstream &in, StrBuf &S) {
        S.Clean();
        char s[BUFSIZE+1] = {'\0'};
        while (!in.eof()) {
            in.read(s, BUFSIZE);
            S.Cat(s);
            memset(s, '\0', BUFSIZE+1);
        }
        return in;
    }
};

StrBuf::StrBuf(const char *src)
{
    N = (strlen(src)) / BUFSIZE + (strlen(src) % BUFSIZE ? 1 : 0);
    for (size_t i = 0; i < N; i++)
        buf.AddAfter(MyStr(src + i*BUFSIZE)), buf.GoToNext();
    remainder = BUFSIZE - strlen(src + (N-1)*BUFSIZE);
}
StrBuf::StrBuf(const StrBuf &src)
{
    N = src.N;
    remainder = src.remainder;
    buf = src.buf;
}

void StrBuf::Cat(const char *src)
{
    buf.GoToEnd();
    if (remainder) {
        MyStr a;
        buf.GetCur(a);
        strncat(a.s, src, remainder);
        a.s[BUFSIZE] = '\0';
        buf.AddBefore(a);
        buf.DelCur();
        if (strlen(src) <= remainder) {
            remainder = BUFSIZE - strlen(a.s);
            return;
        }
    }

    size_t n = strlen(src+remainder) / BUFSIZE + (strlen(src+remainder) % BUFSIZE ? 1 : 0);
    if (!n)
        return;
    for (size_t i = 0; i < n; i++)
        buf.AddAfter(MyStr(src+remainder + i*BUFSIZE)), buf.GoToNext();
    N += n;
    remainder = BUFSIZE - strlen(src+remainder + (n-1)*BUFSIZE);
}

int StrBuf::Cut(size_t new_len)
{
    size_t old_len = Len();
    if (old_len < new_len)
        return -1;

    MyStr a;
    size_t i,
    n = (new_len / BUFSIZE) + (new_len % BUFSIZE ? 1 : 0),
    r = BUFSIZE - ((new_len % BUFSIZE) ? new_len % BUFSIZE : BUFSIZE);
    buf.GoToBegin();
    for (i = 1; i <= n; ++i)
        buf.GoToNext();
    for (; i <= N; ++i)
        buf.DelCur(), buf.GoToNext();
    N = n, remainder = r;
    
    buf.GetCur(a);
    a[BUFSIZE-r] = '\0';
    buf.AddBefore(a);
    buf.DelCur();
    return 0;
}

char& StrBuf::operator[](const size_t index)
{
    size_t n = index / BUFSIZE;
    buf.GoToBegin();
    for (size_t i = 0; i < n; ++i)
        buf.GoToNext();
    return buf.cur->v[index % BUFSIZE];
}

void StrBuf::Copy(char *dest)
{
    dest[0] = '\0';
    for (const auto &s : buf)
        strcat(dest, s.s);
    
}

int StrBuf::Copy(char *dest, size_t begin, size_t end)
{
    if (begin > end)
        return -1;
    size_t len = end - begin + 1, i;
    MyStr a;
    dest[0] = '\0';
    buf.GoToBegin();
    for (i = 0; i < begin / BUFSIZE; ++i)
        buf.GoToNext();
    buf.GetCur(a);
    if (end / BUFSIZE == begin / BUFSIZE) {
        strncpy(dest, a.s + begin%BUFSIZE, len);
        dest[len] = '\0';
    }
    else {
        strcpy(dest, a.s + begin%BUFSIZE);
        for (++i, buf.GoToNext(); i < end / BUFSIZE; ++i) {
            buf.GetCur(a);
            strcat(dest, a.s);
            buf.GoToNext();
        }
        buf.GetCur(a);
        strncat(dest, a.s, end%BUFSIZE+1);
    }
    return 0;
}

int StrBuf::Find(const char c)
{
    MyStr a;
    buf.GoToBegin();
    for (size_t i = 0; i < N; ++i) {
        buf.GetCur(a);
        char *p = strchr(a.s, c);
        if (p != NULL)
            return i*BUFSIZE + (p - a.s);
        buf.GoToNext();
    }
    return -1;
}

int StrBuf::Find(const char *substr)
{
    for (size_t i = 0; i <= Len() - strlen(substr); ++i)
        for (size_t j = 0; j < strlen(substr); ++j) {
            if ((*this)[i+j] != substr[j])
                break;
            else if (j == strlen(substr)-1)
                return i;
        }
    return -1;
}

int StrBuf::Insert(const char *src, size_t pos)
{
    if (pos > Len())
        return -1;
    else if (pos == Len()) {
        Cat(src);
        return 0;
    }

    char *tmp = new char[Len() - pos + 1];
    tmp[0] = '\0';
    Copy(tmp, pos, Len()-1);
    Cut(pos);
    Cat(src);
    Cat(tmp);
    delete[] tmp;
    return 0;
}

int StrBuf::Replace(const char *src, size_t begin, size_t end)
{
    if (begin > end)
        return -1;
    if (end >= Len())
        return -2;
    char *tmp = new char[Len() - end];
    tmp[0] = '\0';
    Copy(tmp, end+1, Len()-1);
    Cut(begin);
    Cat(src);
    Cat(tmp);
    delete[] tmp;
    return 0;
}

StrBuf& StrBuf::operator=(const StrBuf &src)
{
    if (this == &src)
        return *this;
    N = src.N;
    remainder = src.remainder;
    buf = src.buf;
    return *this;
}