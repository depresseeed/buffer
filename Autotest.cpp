#include "Autotest.h"

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
    S1.Replace("1230498012980", 0, S1.Len() - 1);
    S1 = S;
    S.Copy(copy);
    S1.Copy(copy1);
    if (strcmp(copy, copy1) != 0)
        return -1;
    return 0;
}