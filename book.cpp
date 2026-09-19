#include <iostream>
#include <string>
using namespace std;
class book
{
private:
    string name;
    string author;
    string id;
    string publisher;
    double price;
    bool state;

public:
    book() : name(""), author(""), id(""), publisher(""), price(0), state(false) {}

    book(string n, string a, string i, string p, double pr, bool s)
        : name(n), author(a), id(i), publisher(p), price(pr), state(s) {}

    double getprice()
    {
        return price;
    }

    void setvalue(string n, string a, string i, string p, double pr, bool s)
    {
        name = n;
        author = a;
        id = i;
        publisher = p;
        price = pr;
        state = s;
    }
    void print()
    {
        cout << "name:" << name << endl;
        cout << "author:" << author << endl;
        cout << "id:" << id << endl;
        cout << "publisher:" << publisher << endl;
        cout << "price:" << price << endl;
        cout << "state:" << state << endl;
    }
};
book b1;
int main()
{
    // 设置书本属性
    b1.setvalue("C++程序设计", "张三", "978-7-111-12345-6", "机械工业出版社", 59.8, true);
    // 打印书本信息
    b1.print();
    return 0;
}