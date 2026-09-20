#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <ctime>
using namespace std;

const double EPSILON = 1e-2;
const string RECORD_FILE = "geometry_record.txt";

struct Problem
{
    int id;
    string title;
    string question;
    double answer;
};

struct PracticeRecord
{
    int id;
    string title;
    string question;
    double userAnswer;
    double correctAnswer;
    bool correct;
    string timestamp;
};

vector<PracticeRecord> records;

string getCurrentTime()
{
    time_t now = time(nullptr);
    tm *local = localtime(&now);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local);
    return string(buffer);
}

int getIntInput(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            return value;
        }
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
        {
            return value;
        }
        cin.clear();
        string ignored;
        getline(cin, ignored);
        cout << "输入有误，请重新输入。\n";
    }
}

vector<Problem> buildProblems()
{
    vector<Problem> problems;

    problems.push_back({1, "正方形", "正方形边长为 5 cm，求周长。", 20.0});
    problems.push_back({2, "长方形", "长方形长 8 cm，宽 3 cm，求面积。", 24.0});
    problems.push_back({3, "圆", "圆的半径为 4 cm，求面积。", 50.27});
    problems.push_back({4, "三角形", "等边三角形边长为 6 cm，求周长。", 18.0});
    problems.push_back({5, "梯形", "梯形上底 4 cm，下底 8 cm，高 3 cm，求面积。", 18.0});
    problems.push_back({6, "平行四边形", "平行四边形底 7 cm，高 5 cm，求面积。", 35.0});
    problems.push_back({7, "圆", "圆的半径为 3 cm，求周长。", 18.85});
    problems.push_back({8, "菱形", "菱形两条对角线分别为 6 cm 和 8 cm，求面积。", 24.0});

    return problems;
}

int getNextRecordId()
{
    int maxId = 0;
    for (const auto &item : records)
    {
        if (item.id > maxId)
        {
            maxId = item.id;
        }
    }
    return maxId + 1;
}

void saveRecords()
{
    ofstream out(RECORD_FILE, ios::out | ios::trunc);
    if (!out)
    {
        cout << "保存失败：无法打开记录文件。\n";
        return;
    }

    for (const auto &item : records)
    {
        out << item.id << "|"
            << item.title << "|"
            << item.question << "|"
            << item.userAnswer << "|"
            << item.correctAnswer << "|"
            << (item.correct ? 1 : 0) << "|"
            << item.timestamp << "\n";
    }

    out.close();
}

void loadRecords()
{
    ifstream in(RECORD_FILE);
    if (!in)
    {
        return;
    }

    records.clear();
    string line;
    while (getline(in, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string idStr, title, question, userAnswerStr, correctAnswerStr, correctStr, timestamp;
        getline(ss, idStr, '|');
        getline(ss, title, '|');
        getline(ss, question, '|');
        getline(ss, userAnswerStr, '|');
        getline(ss, correctAnswerStr, '|');
        getline(ss, correctStr, '|');
        getline(ss, timestamp, '|');

        PracticeRecord record;
        record.id = stoi(idStr);
        record.title = title;
        record.question = question;
        record.userAnswer = stod(userAnswerStr);
        record.correctAnswer = stod(correctAnswerStr);
        record.correct = (stoi(correctStr) == 1);
        record.timestamp = timestamp;
        records.push_back(record);
    }
    in.close();
}

void addRecord(const Problem &problem, double userAnswer, bool correct)
{
    PracticeRecord record;
    record.id = getNextRecordId();
    record.title = problem.title;
    record.question = problem.question;
    record.userAnswer = userAnswer;
    record.correctAnswer = problem.answer;
    record.correct = correct;
    record.timestamp = getCurrentTime();
    records.push_back(record);
    saveRecords();
}

void printProblemList(const vector<Problem> &problems)
{
    cout << "\n当前题库：\n";
    for (size_t i = 0; i < problems.size(); ++i)
    {
        cout << i + 1 << ". " << problems[i].question << "\n";
    }
    cout << "\n";
}

void showAllRecords()
{
    if (records.empty())
    {
        cout << "\n目前还没有做题记录。\n";
        return;
    }

    cout << "\n=== 所有做题记录 ===\n";
    for (const auto &item : records)
    {
        cout << "编号：" << item.id
             << " | 题型：" << item.title
             << " | 结果：" << (item.correct ? "正确" : "错误")
             << " | 你的答案：" << fixed << setprecision(2) << item.userAnswer
             << " | 正确答案：" << item.correctAnswer
             << " | 时间：" << item.timestamp << "\n";
    }
}

void showWrongRecords()
{
    bool found = false;
    cout << "\n=== 错题记录 ===\n";

    for (const auto &item : records)
    {
        if (!item.correct)
        {
            found = true;
            cout << "编号：" << item.id
                 << " | 题型：" << item.title
                 << " | 题目：" << item.question
                 << " | 你的答案：" << fixed << setprecision(2) << item.userAnswer
                 << " | 正确答案：" << item.correctAnswer
                 << " | 时间：" << item.timestamp << "\n";
        }
    }

    if (!found)
    {
        cout << "还没有错题，继续保持良好表现！\n";
    }
}

void practiceSingleQuestion()
{
    vector<Problem> problems = buildProblems();
    int choice = 0;

    while (true)
    {
        printProblemList(problems);
        choice = getIntInput("请选择要练习的题号（1-8，0 返回菜单）：");
        if (choice == 0)
        {
            return;
        }
        if (choice < 1 || choice > static_cast<int>(problems.size()))
        {
            cout << "题号输入有误，请重新选择。\n";
            continue;
        }

        const Problem &problem = problems[choice - 1];
        double userAnswer = getDoubleInput("题目：" + problem.question + "\n请输入答案：");
        bool correct = fabs(userAnswer - problem.answer) <= EPSILON;
        addRecord(problem, userAnswer, correct);

        cout << fixed << setprecision(2);
        cout << "\n本题结果：" << (correct ? "正确" : "错误") << "\n";
        cout << "你的答案：" << userAnswer << "\n";
        cout << "正确答案：" << problem.answer << "\n";
        cout << "----------------------------------------\n";
        break;
    }
}

void practiceAllQuestions()
{
    vector<Problem> problems = buildProblems();
    int correctCount = 0;

    cout << "\n===== 开始全题练习 =====\n";
    for (size_t i = 0; i < problems.size(); ++i)
    {
        const Problem &problem = problems[i];
        double userAnswer = getDoubleInput("第 " + to_string(i + 1) + " 题：" + problem.question + "\n请输入答案：");
        bool correct = fabs(userAnswer - problem.answer) <= EPSILON;
        addRecord(problem, userAnswer, correct);

        if (correct)
        {
            correctCount++;
        }

        cout << fixed << setprecision(2);
        cout << "本题：" << (correct ? "正确" : "错误") << "，正确答案为 " << problem.answer << "\n";
        cout << "----------------------------------------\n";
    }

    int total = static_cast<int>(problems.size());
    double rate = (total == 0) ? 0.0 : (correctCount * 100.0 / total);
    cout << "\n本次练习统计：\n";
    cout << "总题数：" << total << "\n";
    cout << "正确题数：" << correctCount << "\n";
    cout << "错误题数：" << total - correctCount << "\n";
    cout << "正确率：" << fixed << setprecision(2) << rate << "%\n";
    cout << "===== 练习结束 =====\n";
}

void showMainMenu()
{
    cout << "\n==========================\n";
    cout << "      简单图形题库\n";
    cout << "==========================\n";
    cout << "1. 练习单题并即时反馈\n";
    cout << "2. 练习全部题目并统计\n";
    cout << "3. 查看自己做过的题\n";
    cout << "4. 查看自己的错题\n";
    cout << "5. 退出系统\n";
    cout << "==========================\n";
}

int main()
{
    loadRecords();
    cout << "欢迎使用简单图形题库系统！\n";

    while (true)
    {
        showMainMenu();
        int choice = getIntInput("请选择功能：");

        switch (choice)
        {
        case 1:
            practiceSingleQuestion();
            break;
        case 2:
            practiceAllQuestions();
            break;
        case 3:
            showAllRecords();
            break;
        case 4:
            showWrongRecords();
            break;
        case 5:
            cout << "感谢使用，再见！\n";
            return 0;
        default:
            cout << "无效选项，请重新输入。\n";
            break;
        }
    }

    return 0;
}
