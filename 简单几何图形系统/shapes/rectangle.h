#pragma once
#include <sstream>
#include <iomanip>
#include "shape.h"
#include "../utils.h"
using namespace std;
class Rectangle : public Shape
{
protected:
    double length; // 封装为 protected，供派生类 Square 访问
    double width;

public:
    Rectangle(double l = 0, double w = 0)
        : Shape("长方形"), length(l), width(w) {}

    // 供派生类指定自己的名称
    Rectangle(const string &n, double l, double w)
        : Shape(n), length(l), width(w) {}

    double area() const override { return length * width; }
    double perimeter() const override { return 2 * (length + width); }

    void input() override
    {
        length = getDoubleInput("请输入长方形的长(cm)：");
        while (length <= 0)
            length = getDoubleInput("长必须为正数，请重新输入：");
        width = getDoubleInput("请输入长方形的宽(cm)：");
        while (width <= 0)
            width = getDoubleInput("宽必须为正数，请重新输入：");
    }

    string detail() const override
    {
        ostringstream os;
        os << "长 = " << fixed << setprecision(2) << length
           << " cm，宽 = " << width << " cm";
        return os.str();
    }

    Shape *clone() const override { return new Rectangle(*this); }

    string serialize() const override
    {
        ostringstream os;
        os << "Rectangle|" << setprecision(15) << length << "|" << width;
        return os.str();
    }

    string typeName() const override { return "长方形"; }
};
