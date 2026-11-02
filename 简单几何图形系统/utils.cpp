#include "utils.h"
using namespace std;
string getCurrentTime()
{
    time_t now = time(nullptr); // 取系统当前时间
    tm local;
#if defined(_WIN32) // 兼容
    localtime_s(&local, &now);
#endif
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local); // 答题时间
    return string(buffer);
}

int getIntInput(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
            return value;
        cin.clear();
        string ignored;
        getline(cin, ignored);
        cout << "输入有误，请重新输入。\n";
    }
}

double getDoubleInput(const string &prompt)
{
    double value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
            return value;
        cin.clear();
        string ignored;
        getline(cin, ignored);
        cout << "输入有误，请重新输入。\n";
    }
}