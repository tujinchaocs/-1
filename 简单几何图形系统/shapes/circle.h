#pragma once
#include <sstream>
#include <iomanip>
#include "shape.h"
#include "../utils.h"
using namespace std;

class Circle : public Shape
{
private:
    double radius; // 封装：半径，外部不可直接访问

public:
    Circle(double r = 0) : Shape("圆"), radius(r) {}

    double area() const override { return PI * radius * radius; }
    double perimeter() const override { return 2 * PI * radius; }

    void input() override
    {
        radius = getDoubleInput("请输入圆的半径(cm)：");
        while (radius <= 0)
            radius = getDoubleInput("半径必须为正数，请重新输入：");
    }

    string detail() const override
    {
        ostringstream os;
        os << "半径 = " << fixed << setprecision(2) << radius << " cm";
        return os.str();
    }

    Shape *clone() const override { return new Circle(*this); }

    string serialize() const override
    {
        ostringstream os;
        os << "Circle|" << setprecision(15) << radius;
        return os.str();
    }

    string typeName() const override { return "圆"; }
};
