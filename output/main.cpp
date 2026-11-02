#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std;

// 顺序循环队列类
class CirQueue
{
private:
    long long *data; // 存储数组
    int front;       // 队头指针
    int rear;        // 队尾指针
    int capacity;    // 最大容量
    int count;       // 当前元素个数

public:
    // 构造函数
    CirQueue(int maxSize)
    {
        capacity = maxSize;
        data = new long long[capacity];
        front = 0;
        rear = 0;
        count = 0;
    }

    // 析构函数
    ~CirQueue()
    {
        delete[] data;
    }

    // 入队
    bool enqueue(long long x)
    {
        if (isFull())
        {
            return false;
        }
        data[rear] = x;
        rear = (rear + 1) % capacity;
        count++;
        return true;
    }

    // 出队
    bool dequeue()
    {
        if (isEmpty())
        {
            return false;
        }
        front = (front + 1) % capacity;
        count--;
        return true;
    }

    // 获取队头元素
    long long getFront()
    {
        if (isEmpty())
        {
            cerr << "队列为空，无法获取队头" << endl;
            return -1;
        }
        return data[front];
    }

    // 判空
    bool isEmpty()
    {
        return count == 0;
    }

    // 判满
    bool isFull()
    {
        return count == capacity;
    }

    // 获取当前元素个数
    int getSize()
    {
        return count;
    }
};

// 基于循环队列生成杨辉三角（仅计算，不打印，用于性能测试）
void generateYangHui(int n)
{
    if (n <= 0)
        return;

    CirQueue q(n + 1); // 容量设为n+1，预留一位避免边界问题
    q.enqueue(1);      // 第一行元素

    for (int i = 1; i <= n; i++)
    {
        long long pre = 0;
        for (int j = 1; j <= i; j++)
        {
            long long curr = q.getFront();
            q.dequeue();
            // 计算下一行元素并入队
            q.enqueue(pre + curr);
            pre = curr;
        }
        // 每行末尾的1入队
        q.enqueue(1);
    }
}

// 打印杨辉三角（功能验证用）
void printYangHui(int n)
{
    if (n <= 0)
        return;

    CirQueue q(n + 1);
    q.enqueue(1);

    for (int i = 1; i <= n; i++)
    {
        // 输出前置空格，形成三角形状
        for (int k = 0; k < n - i; k++)
        {
            cout << "  ";
        }

        long long pre = 0;
        for (int j = 1; j <= i; j++)
        {
            long long curr = q.getFront();
            q.dequeue();
            cout << setw(4) << curr;
            q.enqueue(pre + curr);
            pre = curr;
        }
        q.enqueue(1);
        cout << endl;
    }
}

int main()
{
    // 功能测试：打印10行杨辉三角
    cout << "10行杨辉三角" << endl;
    printYangHui(10);
    cout << endl;
    return 0;
}
