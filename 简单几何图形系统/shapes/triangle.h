#pragma once
#include <sstream>
#include <iomanip>
#include "shape.h"
#include "../utils.h"
using namespace std;
class Triangle : public Shape
{
private:
    double a, b, c; // 封装：三条边长

public:
    Triangle(double x = 0, double y = 0, double z = 0)
        : Shape("三角形"), a(x), b(y), c(z) {}

    double area() const override
    {
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c)); // 海伦公式
    }

    double perimeter() const override { return a + b + c; }

    void input() override
    {
        while (true)
        {
            a = getDoubleInput("请输入三角形第 1 条边(cm)：");
            b = getDoubleInput("请输入三角形第 2 条边(cm)：");
            c = getDoubleInput("请输入三角形第 3 条边(cm)：");
            if (a > 0 && b > 0 && c > 0 &&
                a + b > c && a + c > b && b + c > a)
                break;
            cout << "这三条边不能构成三角形，请重新输入。\n";
        }
    }

    string detail() const override
    {
        ostringstream os;
        os << "三边长分别为 " << fixed << setprecision(2)
           << a << "、" << b << "、" << c << " cm";
        return os.str();
    }

    Shape *clone() const override { return new Triangle(*this); }

    string serialize() const override
    {
        ostringstream os;
        os << "Triangle|" << setprecision(15) << a << "|" << b << "|" << c;
        return os.str();
    }

    string typeName() const override { return "三角形"; }
};