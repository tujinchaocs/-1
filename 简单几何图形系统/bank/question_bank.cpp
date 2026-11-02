#include "question_bank.h"
#include "../shapes/circle.h"
#include "../shapes/rectangle.h"
#include "../shapes/square.h"
#include "../shapes/triangle.h"
#include "../utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
using namespace std;
Shape *QuestionBank::createShapeByMenu(int t)
{
    if (t == 1)
        return new Circle();
    if (t == 2)
        return new Rectangle();
    if (t == 3)
        return new Triangle();
    if (t == 4)
        return new Square();
    return nullptr;
}

//----------------- 反序列化：根据文本还原出对应图形 -----------------
Shape *QuestionBank::parseShape(const string &line)
{
    stringstream ss(line);
    string type;
    getline(ss, type, '|');
    try
    {
        auto nextNum = [&]()
        {
            string v;
            getline(ss, v, '|');
            return stod(v);
        };
        if (type == "Circle")
            return new Circle(nextNum());
        if (type == "Rectangle")
        {
            double l = nextNum(), w = nextNum();
            return new Rectangle(l, w);
        }
        if (type == "Square")
            return new Square(nextNum());
        if (type == "Triangle")
        {
            double a = nextNum(), b = nextNum(), c = nextNum();
            return new Triangle(a, b, c);
        }
    }
    catch (const exception &)
    {
        return nullptr;
    }
    return nullptr;
}

//----------------- 自由练习：用户选题型、输数据、核对答案 -----------------
void QuestionBank::practiceCustom()
{
    cout << "\n----- 自由练习：自选图形并输入数据，核对答案 -----\n";
    int t = getIntInput("请选择图形类型（1.圆  2.长方形  3.三角形  4.正方形，0 返回菜单）：");
    if (t == 0)
        return;

    Shape *s = createShapeByMenu(t);
    if (!s)
    {
        cout << "图形类型无效。\n";
        return;
    }

    s->input(); // 多态输入该图形的数据
    s->show();

    int m = getIntInput("请选择要计算的内容（1.面积  2.周长，0 返回菜单）：");
    if (m == 0)
    {
        delete s;
        return;
    }
    if (m != 1 && m != 2)
    {
        cout << "选项无效。\n";
        delete s;
        return;
    }

    bool askArea = (m == 1);
    answerOne(s, askArea); // 输入答案、核对、记录
    delete s;              // 临时图形用完即释放（不计入题库）
}

//----------------- 交互式添加题目到题库 -----------------
void QuestionBank::addQuestionInteractive()
{
    int t = getIntInput("请选择图形类型（1.圆  2.长方形  3.三角形  4.正方形）：");
    Shape *s = createShapeByMenu(t);
    if (!s)
    {
        cout << "图形类型无效。\n";
        return;
    }
    s->input(); // 多态输入
    addQuestion(s);
    saveToFile(DATA_FILE);
    cout << "题目添加成功！\n";
}

//----------------- 作答一道题：多态求面积/周长、判分、记录 -----------------
bool QuestionBank::answerOne(const Shape *s, bool askArea)
{
    double correct = askArea ? s->area() : s->perimeter(); // 多态计算正确答案

    ostringstream q;
    q << s->typeName() << "（" << s->detail() << "），求"
      << (askArea ? "面积" : "周长");
    cout << "题目：" << q.str() << "\n";

    double userAnswer = getDoubleInput(
        string("请输入你的答案（单位：") + (askArea ? "平方厘米" : "厘米") + "）：");
    bool ok = fabs(userAnswer - correct) <= EPSILON; // 核对答案

    ++answeredCount;
    if (ok)
        ++correctCount;

    Record r;
    r.id = nextRecordId++;
    r.typeName = s->typeName();
    r.question = q.str();
    r.userAnswer = userAnswer;
    r.correctAnswer = correct;
    r.correct = ok;
    r.timestamp = getCurrentTime();
    records.push_back(r);

    cout << fixed << setprecision(2);
    cout << "本题结果：" << (ok ? "正确" : "错误") << "\n";
    cout << "你的答案：" << userAnswer << "\n";
    cout << "正确答案：" << correct << "\n";
    cout << "----------------------------------------\n";

    saveToFile(DATA_FILE);
    return ok;
}

bool QuestionBank::removeQuestion(int index)
{
    if (index < 0 || index >= size())
        return false;
    delete questions[index];
    questions.erase(questions.begin() + index);
    return true;
}

void QuestionBank::listAll() const
{
    cout << "\n当前题库（共 " << size() << " 题）：\n";
    for (int i = 0; i < size(); ++i)
    {
        cout << i + 1 << ". ";
        questions[i]->show(); // 多态展示
    }
    cout << "\n";
}

void QuestionBank::practiceAt(int index)
{
    if (index < 0 || index >= size())
    {
        cout << "题号无效，请重新选择。\n";
        return;
    }
    bool askArea = (rand() % 2 == 0); // 随机考查面积或周长
    answerOne(questions[index], askArea);
}

void QuestionBank::practice()
{
    if (questions.empty())
    {
        cout << "\n题库为空，暂无题目可练。\n";
        return;
    }

    int correctBefore = correctCount;
    int total = size();
    cout << "\n===== 开始全部练习（共 " << total << " 题）=====\n";
    for (int i = 0; i < total; ++i)
    {
        cout << "第 " << i + 1 << " 题：";
        bool askArea = (rand() % 2 == 0);
        answerOne(questions[i], askArea);
    }

    int thisCorrect = correctCount - correctBefore;
    double rate = (total == 0) ? 0.0 : (thisCorrect * 100.0 / total);
    cout << "\n本次练习统计：\n";
    cout << "总题数：" << total << "\n";
    cout << "正确题数：" << thisCorrect << "\n";
    cout << "错误题数：" << total - thisCorrect << "\n";
    cout << "正确率：" << fixed << setprecision(2) << rate << "%\n";
    cout << "===== 练习结束 =====\n";
}

void QuestionBank::statistics() const
{
    int wrong = answeredCount - correctCount;
    double rate = (answeredCount == 0) ? 0.0 : (correctCount * 100.0 / answeredCount);
    cout << "\n=== 答题统计 ===\n";
    cout << "题库题目总数：" << size() << "\n";
    cout << "累计答题数：" << answeredCount << "\n";
    cout << "答对：" << correctCount << " 道\n";
    cout << "答错：" << wrong << " 道\n";
    cout << "总正确率：" << fixed << setprecision(2) << rate << "%\n";
}

void QuestionBank::showRecords() const
{
    if (records.empty())
    {
        cout << "\n目前还没有做题记录。\n";
        return;
    }
    cout << "\n=== 所有做题记录 ===\n";
    for (const Record &r : records)
    {
        cout << "编号：" << r.id
             << " | 题型：" << r.typeName
             << " | 结果：" << (r.correct ? "正确" : "错误")
             << " | 你的答案：" << fixed << setprecision(2) << r.userAnswer
             << " | 正确答案：" << r.correctAnswer
             << " | 时间：" << r.timestamp << "\n";
    }
}

void QuestionBank::showWrongRecords() const
{
    bool found = false;
    cout << "\n=== 错题记录 ===\n";
    for (const Record &r : records)
    {
        if (!r.correct)
        {
            found = true;
            cout << "编号：" << r.id
                 << " | 题型：" << r.typeName
                 << " | 题目：" << r.question
                 << " | 你的答案：" << fixed << setprecision(2) << r.userAnswer
                 << " | 正确答案：" << r.correctAnswer
                 << " | 时间：" << r.timestamp << "\n";
        }
    }
    if (!found)
        cout << "还没有错题，继续保持良好表现！\n";
}

bool QuestionBank::saveToFile(const string &path)
{
    ofstream out(path, ios::out | ios::trunc);
    if (!out)
    {
        cout << "保存失败：无法打开记录文件。\n";
        return false;
    }

    out << "[STAT]\n"
        << answeredCount << " " << correctCount << " " << nextRecordId << "\n";
    out << "[SHAPE]\n";
    for (const Shape *s : questions)
        out << s->serialize() << "\n"; // 多态序列化
    out << "[RECORD]\n";
    for (const Record &r : records)
    {
        out << r.id << "|"
            << r.typeName << "|"
            << r.question << "|"
            << setprecision(15) << r.userAnswer << "|"
            << r.correctAnswer << "|"
            << (r.correct ? 1 : 0) << "|"
            << r.timestamp << "\n";
    }
    out.close();
    return true;
}

bool QuestionBank::loadFromFile(const string &path)
{
    ifstream in(path);
    if (!in)
        return false;

    clearShapes();
    records.clear();
    answeredCount = 0;
    correctCount = 0;
    nextRecordId = 1;

    string line, section;
    while (getline(in, line))
    {
        if (line.empty())
            continue;
        if (line == "[STAT]" || line == "[SHAPE]" || line == "[RECORD]")
        {
            section = line;
            continue;
        }

        try
        {
            if (section == "[STAT]")
            {
                stringstream ss(line);
                ss >> answeredCount >> correctCount >> nextRecordId;
            }
            else if (section == "[SHAPE]")
            {
                Shape *s = parseShape(line); // 工厂还原
                if (s)
                    questions.push_back(s);
                else
                    cout << "警告：检测到一条损坏的题目，已自动跳过。\n";
            }
            else if (section == "[RECORD]")
            {
                stringstream ss(line);
                string id, type, q, ua, ca, ok, ts;
                getline(ss, id, '|');
                getline(ss, type, '|');
                getline(ss, q, '|');
                getline(ss, ua, '|');
                getline(ss, ca, '|');
                getline(ss, ok, '|');
                getline(ss, ts, '|');

                Record r;
                r.id = stoi(id);
                r.typeName = type;
                r.question = q;
                r.userAnswer = stod(ua);
                r.correctAnswer = stod(ca);
                r.correct = (stoi(ok) == 1);
                r.timestamp = ts;
                records.push_back(r);
                nextRecordId = max(nextRecordId, r.id + 1);
            }
        }
        catch (const exception &)
        {
            cout << "警告：检测到一条损坏的记录，已自动跳过。\n";
            continue;
        }
    }
    in.close();
    return true;
}

void QuestionBank::loadDefault()
{
    addQuestion(new Circle(4));         // 圆，半径 4
    addQuestion(new Rectangle(8, 3));   // 长方形，长 8 宽 3
    addQuestion(new Triangle(6, 6, 6)); // 等边三角形，边长 6
    addQuestion(new Square(5));         // 正方形，边长 5
    addQuestion(new Circle(3));         // 圆，半径 3
    addQuestion(new Triangle(3, 4, 5)); // 直角三角形 3-4-5
    addQuestion(new Rectangle(7, 5));   // 长方形，长 7 宽 5
    addQuestion(new Square(6));         // 正方形，边长 6
}
