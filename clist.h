#pragma once

template <class T>
class CList2Node
{
public:
    T v;
    CList2Node *prev, *next;
    CList2Node() { prev = next = NULL; }
};

template <class T>
class CList2
{
private:
    CList2Node<T> *first, *last;

public:
    CList2Node<T> *cur;
    class iterator
    {
        CList2Node<T> *cur;
    public:
        iterator() { cur = NULL; }
        iterator(CList2Node<T> *cur) { this->cur = cur; }
        int operator!=(const iterator &b) { return cur != b.cur; }
        int operator==(const iterator &b) { return cur == b.cur; }
        void operator++() { if (cur) cur = cur->next; }
        void operator++(int) { if (cur) cur = cur->next; }
        const T& operator*() { return cur->v; }
    };
    CList2() { SetZero(); }
    void SetZero(void) {cur = first = last = NULL;}
    ~CList2() { Clean(); }
    void Clean(void) { GoToBegin(); while (DelCur() == 0); SetZero(); }
    CList2(const CList2 &b) { CopyOnly(b); }
    void CopyOnly(const CList2 &b) { Clean(); for (auto it = b.begin(); it != b.end(); ++it) AddAfter(*it), GoToNext(); }
    void GoToBegin(void) { cur = first; }
    void GoToEnd(void) { cur = last; }
    int GetCur(T &x) {if (IsEmpty()) return -1; x = cur->v; return 0;}
    int GoToNext(void) {if (IsEmpty()) return -1; if (cur->next == NULL) return -2; cur = cur->next; return 0;}
    int GoToPrev(void) {if (IsEmpty()) return -1; if (cur->prev == NULL) return -2; cur = cur->prev; return 0;}
    int IsEmpty(void) { return cur == NULL; }
    void AddAfter(const T &x);
    void AddBefore(const T &x);
    int DelCur(void);
    iterator begin() const { return iterator(first); }
    iterator end() const { return iterator(NULL); }
    CList2& operator=(const CList2 &src);
};

template <class T>
int CList2<T>::DelCur(void)
{
    if (IsEmpty())
        return -1;

    if (cur->prev)
        cur->prev->next = cur->next;
    else
        first = cur->next;

    if (cur->next)
        cur->next->prev = cur->prev;
    else
		{last = cur->prev;}

	CList2Node<T> *tmp = cur;
    if (cur->prev)
        cur = cur->prev;
    else
		{cur = cur->next;}
    delete tmp;
    return 0;
}

template <class T>
void CList2<T>::AddBefore(const T &x)
{
    CList2Node<T> *n = new CList2Node<T>;
    n->v = x;
    if (IsEmpty())
        cur = first = last = n;
    else {
        n->prev = cur->prev;
        n->next = cur;
        cur->prev = n;
        if (n->prev)
            n->prev->next = n;
        else
            first = n;
    }
}

template <class T>
void CList2<T>::AddAfter(const T &x)
{
    CList2Node<T> *n = new CList2Node<T>;
    n->prev = n->next = NULL;
    n->v = x;
    if (IsEmpty())
        cur = first = last = n;
    else {
        n->prev = cur;
        n->next = cur->next;
        cur->next = n;
        if (n->next)
            n->next->prev = n;
        else
            last = n;
    }
}

template <class T>
CList2<T>& CList2<T>::operator=(const CList2<T> &src)
{
    if (this == &src)
        return *this;
    CopyOnly(src);
    return *this;
}