#include <iostream>

#include "buf.h"
#include "Autotest.h"
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

