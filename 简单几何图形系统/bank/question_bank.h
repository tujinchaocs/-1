#pragma once
#include <vector>
#include <string>
#include "../shapes/shape.h"
using namespace std;

class QuestionBank
{
private:
    vector<Shape *> questions; // 组合关系：题库拥有这些图形对象
    int answeredCount;         // 累计答题数
    int correctCount;          // 累计答对题数

    // 一条做题记录（类图之外，为保存练习历史而设计的私有嵌套结构）
    struct Record
    {
        int id;
        string typeName;
        string question;
        double userAnswer;
        double correctAnswer;
        bool correct;
        string timestamp;
    };
    vector<Record> records;
    int nextRecordId;

    void clearShapes() // 释放所持有的全部图形
    {
        for (Shape *s : questions)
            delete s;
        questions.clear();
    }

    static Shape *parseShape(const string &line); // 文本反序列化工厂
    static Shape *createShapeByMenu(int t);       // 按菜单编号创建图形
    bool answerOne(const Shape *s, bool askArea); // 一次作答、判分、记录

public:
    QuestionBank() : answeredCount(0), correctCount(0), nextRecordId(1) {}
    ~QuestionBank() { clearShapes(); }

    // 深拷贝：依赖每个图形的 clone() 完成多态复制
    QuestionBank(const QuestionBank &other)
    {
        answeredCount = other.answeredCount;
        correctCount = other.correctCount;
        nextRecordId = other.nextRecordId;
        records = other.records;
        for (Shape *s : other.questions)
            questions.push_back(s->clone());
    }

    QuestionBank &operator=(const QuestionBank &other)
    {
        if (this == &other)
            return *this;
        clearShapes();
        answeredCount = other.answeredCount;
        correctCount = other.correctCount;
        nextRecordId = other.nextRecordId;
        records = other.records;
        for (Shape *s : other.questions)
            questions.push_back(s->clone());
        return *this;
    }

    void addQuestion(Shape *s) { questions.push_back(s); } // 接管所有权
    bool removeQuestion(int index);
    void listAll() const;
    void practiceCustom();         // 自由练习：选择题型→输入数据→核对答案
    void practiceAt(int index);    // 练习题库中单题
    void practice();               // 练习全部题目
    void addQuestionInteractive(); // 交互式添加题目到题库
    void statistics() const;
    void showRecords() const;
    void showWrongRecords() const;
    bool saveToFile(const string &path);
    bool loadFromFile(const string &path);
    int size() const { return static_cast<int>(questions.size()); }
    void loadDefault();
};