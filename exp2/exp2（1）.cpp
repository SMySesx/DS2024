#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>
#include<stdexcept>
using namespace std;

// 实现栈数据结构
template <typename T>
class Stack {
private:
    stack<T> data;
public:
    void push(T value) {
        data.push(value); // 入栈
    }

    T pop() {
        if (data.empty()) throw runtime_error("栈为空！");
        T value = data.top();
        data.pop();
        return value; // 出栈
    }

    T top() {
        if (data.empty()) throw runtime_error("栈为空！");
        return data.top(); // 获取栈顶元素
    }

    bool empty() {
        return data.empty(); // 栈空检查
    }
};

class Calculator {
private:
    Stack<double> values; // 存储操作数的栈
    Stack<char> ops; // 存储操作符的栈

    // 获取运算符优先级
    int getPriority(char op) {
        switch (op) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            default:
                return 0;
        }
    }

    // 应用操作符到操作数上
    void applyOp(char op) {
        double b = values.pop();
        double a = values.pop();
        if (op == '/' && b == 0) throw runtime_error("除数不可为零！");
        switch (op) {
            case '+':
                values.push(a + b);
                break;
            case '-':
                values.push(a - b);
                break;
            case '*':
                values.push(a * b);
                break;
            case '/':
                values.push(a / b);
                break;
        }
    }

public:
    // 表达式的求值
    double evaluate(const string& expression) {
        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];

            if (isspace(c)) {
                continue; // 忽略空格
            }

            if (isdigit(c)) {
                double value = 0;
                while (i < expression.length() && isdigit(expression[i])) {
                    value = value * 10 + (expression[i] - '0');
                    i++;
                }
                values.push(value); // 将数字入栈
            } else if (c == '(') {
                ops.push(c); // 左括号入栈
            } else if (c == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    applyOp(ops.pop()); // 处理括号内的运算
                }
                if (!ops.empty() && ops.top() == '(') {
                    ops.pop(); // 匹配左括号并出栈
                } else {
                    throw runtime_error("括号不匹配！"); 
                }
            } else {
                while (!ops.empty() && getPriority(ops.top()) >= getPriority(c)) {
                    applyOp(ops.pop()); // 处理优先级高的运算
                }
                ops.push(c); // 操作符入栈
            }
        }

        while (!ops.empty()) {
            if (ops.top() == '(') throw runtime_error("括号不匹配！");
            applyOp(ops.pop()); // 处理剩余的运算
        }

        if (values.empty()) throw runtime_error("表达式无效！");
        return values.pop(); // 返回最终结果
    }
};

int main() {
    Calculator calc;
    string expression = "12 + 3 * 2 / ( 14 - 7 )";
    try {
        cout << "Result: " << calc.evaluate(expression) << endl; // 计算并输出结果
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl; // 捕获并输出错误信息
    }
    return 0;
}