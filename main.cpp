#include <iostream>

#include "buf.h"

using namespace std;

int autotest();

int main()
{
    if (autotest()) {
        cout << "Autotest failed" << endl;
        return 0;
    }
    else
        cout << "Autotest passed" << endl;
    ifstream file("1.txt", ios::in);
    StrBuf S, S1;
    file >> S;
    cout << "String: " << S << endl;
    S.Cat("12345");
    cout << "Concatenate: " << S << endl;
    S1 = S;
    cout << "Assign: " << S1 << endl;
    StrBuf S2(S1);
    cout << "Constructor: " << S2 << endl;
    S.Insert("zxczxczxc", 3);
    cout << "Insert: " << S << endl;
    cout << "Length: " << S.Len() << endl;
    char *copy1 = new char[S.Len()+1];
    char *copy2 = new char[S.Len()+1];
    S.Copy(copy1);
    cout << "Copy: " << copy1 << endl;
    S.Copy(copy2, 4, 10);
    cout << "Copy substring: " << copy2 << endl;
    cout << "5-th symbol: " << S[5] << endl;
    S[5] = '?';
    cout << "5-th symbol = ?: " << S[5] << endl;
    cout << "Find ?: " << S.Find('?') << endl;
    cout << "Find !: " << S.Find('!') << endl;
    cout << "Find \"123\": " << S.Find("123") << endl;
    cout << "Find \"132\": " << S.Find("132") << endl;
    S.Replace("1111111", 0, 8);
    cout << "Replace: " << S << endl;
    S.Cut(5);
    cout << "Cut: " << S << endl;
    file.close();
    delete[] copy1, delete[] copy2;
    return 0;
}

int autotest()
{
    char copy[512], copy1[512];
    StrBuf S;
    S.Cat("abcd1234");
    S.Copy(copy);
    if (strcmp(copy, "abcd1234") != 0)
        return -1;
    S.Insert("zxc", 2);
    S.Copy(copy);
    if (strcmp(copy, "abzxccd1234") != 0)
        return -1;
    if (S.Len() != 11)
        return -1;
    S.Copy(copy, 4, 10);
    if (strcmp(copy, "ccd1234") != 0)
        return -1;
    if (S[5] != 'c')
        return -1;
    S[5] = 'y';
    if (S[5] != 'y')
        return -1;
    cout << S.Find('y') << endl;
    if (S.Find('y') != 5)
        return -1;
    if (S.Find('!') != -1)
        return -1;
    if (S.Find("123") != 7)
        return -1;
    if (S.Find("132") != -1)
        return -1;
    S.Replace("12345", 3, 5);
    S.Copy(copy);
    if (strcmp(copy, "abz12345d1234") != 0)
        return -1;
    S.Cut(4);
    S.Copy(copy);
    if (strcmp(copy, "abz1") != 0)
        return -1;
    StrBuf S1(S);
    S.Copy(copy);
    S1.Copy(copy1);
    if (strcmp(copy, copy1) != 0)
        return -1;
    S1.Replace("1230498012980", 0, S1.Len()-1);
    S1 = S;
    S.Copy(copy);
    S1.Copy(copy1);
    if (strcmp(copy, copy1) != 0)
        return -1;
    return 0;
}
