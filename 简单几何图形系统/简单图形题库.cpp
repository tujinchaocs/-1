#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "utils.h"
#include "shapes/shape.h"
#include "shapes/circle.h"
#include "shapes/rectangle.h"
#include "shapes/square.h"
#include "shapes/triangle.h"
#include "bank/question_bank.h"
using namespace std;

//=============================================================
// 主菜单
//=============================================================
void showMainMenu()
{
    cout << "\n==========================\n";
    cout << "      简单图形题库（面向对象版）\n";
    cout << "==========================\n";
    cout << "1. 自由练习：自选图形、输入数据、核对答案\n";
    cout << "2. 从题库选择单题练习\n";
    cout << "3. 练习全部题目并统计\n";
    cout << "4. 查看自己做过的题\n";
    cout << "5. 查看自己的错题\n";
    cout << "6. 向题库添加图形题目\n";
    cout << "7. 删除指定题目\n";
    cout << "8. 查看答题统计\n";
    cout << "9. 退出系统\n";
    cout << "==========================\n";
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    QuestionBank bank;
    if (!bank.loadFromFile(DATA_FILE) || bank.size() == 0)
        bank.loadDefault();

    cout << "欢迎使用简单图形题库系统！\n";

    while (true)
    {
        showMainMenu();
        int choice = getIntInput("请选择功能：");

        switch (choice)
        {
        case 1: // 自由练习：选题型→输数据→核对
            bank.practiceCustom();
            break;
        case 2: // 题库单题练习
        {
            bank.listAll();
            int idx = getIntInput("请选择题号（1-" + to_string(bank.size()) + "，0 返回菜单）：");
            if (idx == 0)
                break;
            bank.practiceAt(idx - 1);
            break;
        }
        case 3:
            bank.practice();
            break;
        case 4:
            bank.showRecords();
            break;
        case 5:
            bank.showWrongRecords();
            break;
        case 6:
            bank.addQuestionInteractive();
            break;
        case 7:
        {
            bank.listAll();
            int idx = getIntInput("请输入要删除的题号（0 返回菜单）：");
            if (idx == 0)
                break;
            if (bank.removeQuestion(idx - 1))
            {
                bank.saveToFile(DATA_FILE);
                cout << "已删除该题。\n";
            }
            else
            {
                cout << "题号无效，删除失败。\n";
            }
            break;
        }
        case 8:
            bank.statistics();
            break;
        case 9:
            bank.saveToFile(DATA_FILE);
            cout << "感谢使用，再见！\n";
            return 0;
        default:
            cout << "无效选项，请重新输入。\n";
            break;
        }
    }
    return 0;
}
