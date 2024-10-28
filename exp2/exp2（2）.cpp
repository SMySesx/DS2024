#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// 计算最大矩形面积
int largestArea(vector<int>& heights) {
    stack<int> s;
    int maxArea = 0; // 最大面积
    int n = heights.size(); // 柱子的数量

    // 遍历每个柱子
    for (int i = 0; i <= n; ++i) {
        // 当栈不为空且当前柱子的高度大于栈顶柱子的高度时，计算面积
        while (!s.empty() && (i == n || heights[s.top()] > heights[i])) {
            int h = heights[s.top()]; // 取出栈顶柱子的高度
            s.pop(); // 弹出栈顶柱子的索引

            // 计算面积，宽度是当前索引与栈顶索引的差
            int w = s.empty() ? i : i - s.top() - 1;
            maxArea = max(maxArea, h * w);
        }
        // 当前柱子索引入栈
        s.push(i);
    }

    return maxArea;
}

// 随机生成数据并测试
void test() {
    for (int i = 0; i < 10; ++i) {
        int n = rand() % 10 + 1; // 随机生成柱子数量
        vector<int> heights(n);
        for (int j = 0; j < n; ++j) {
            heights[j] = rand() % 10+1; // 随机生成柱子高度
        }
        cout << "Test " << i + 1 << ": ";
        cout << "Heights = [";
        for (int j = 0; j < n; ++j) {
            cout << heights[j] << (j < n - 1 ? ", " : "");
        }
        cout << "], Max Area = " << largestArea(heights) << endl;
    }
}

int main() {
    test(); 
    return 0;
}