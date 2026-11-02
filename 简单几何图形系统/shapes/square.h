#pragma once
#include <sstream>
#include <iomanip>
#include "rectangle.h"
#include "../utils.h"
using namespace std;
class Square : public Rectangle
{
public:
    Square(double side = 0) : Rectangle("正方形", side, side) {}

    // 正方形是长=宽的长方形，面积/周长公式直接复用父类（继承复用）
    double area() const override { return Rectangle::area(); }
    double perimeter() const override { return Rectangle::perimeter(); }

    void input() override
    {
        double side = getDoubleInput("请输入正方形的边长(cm)：");
        while (side <= 0)
            side = getDoubleInput("边长必须为正数，请重新输入：");
        length = width = side; // 访问父类 protected 成员
    }

    string detail() const override
    {
        ostringstream os;
        os << "边长 = " << fixed << setprecision(2) << length << " cm";
        return os.str();
    }

    Shape *clone() const override { return new Square(*this); }

    string serialize() const override
    {
        ostringstream os;
        os << "Square|" << setprecision(15) << length;
        return os.str();
    }

    string typeName() const override { return "正方形"; }
};