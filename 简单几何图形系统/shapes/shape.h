#pragma once
#include <iostream>
#include <string>
using namespace std;
// 抽象基类 Shape：封装公共属性 name，统一规定图形的操作接口
class Shape
{
protected:
    string name; // 图形名称（封装：仅允许派生类访问）

public:
    Shape(const string &n = "图形") : name(n) {}
    virtual ~Shape() {} // 虚析构：保证 delete 基类指针时正确析构派生对象

    virtual double area() const = 0;      // 求面积（纯虚函数）
    virtual double perimeter() const = 0; // 求周长（纯虚函数）
    virtual void input() = 0;             // 输入图形参数
    virtual string detail() const = 0;    // 图形参数的文字描述（供 show 与记录复用）

    virtual void show() const // 展示图形（模板方法：通过 detail 多态显示）
    {
        cout << "【" << name << "】" << detail() << "\n";
    }

    virtual Shape *clone() const = 0;     // 虚拷贝构造：多态地复制一个自身
    virtual string serialize() const = 0; // 序列化为文本，便于持久化
    virtual string typeName() const = 0;  // 返回图形类型名
    string getName() const { return name; }
};
