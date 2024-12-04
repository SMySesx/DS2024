#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

// 图的邻接矩阵表示
class Graph {
public:
    Graph(int numVertices);

    // 添加边
    void addEdge(int src, int dest, int weight = 1);

    // 广度优先搜索
    void BFS(int startVertex);

    // 深度优先搜索
    void DFS(int startVertex);

    // Dijkstra算法求最短路径
    void dijkstra(int startVertex);

    // Prim算法求最小支撑树
    void prim();

private:
    int numVertices;
    vector<vector<int> > adjMatrix;
};

Graph::Graph(int numVertices) : numVertices(numVertices),adjMatrix(numVertices, vector<int>(numVertices, 0)) {}

void Graph::addEdge(int src, int dest, int weight) {
    adjMatrix[src][dest] = weight;
    adjMatrix[dest][src] = weight; // 如果是无向图，需要双向添加边
}

// 广度优先搜索实现
void Graph::BFS(int startVertex) {
    vector<bool> visited(numVertices, false);
    queue<int> queue;

    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();
        cout << currentVertex << " ";

        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[currentVertex][i]!= 0 &&!visited[i]) {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
    cout << endl;
}

// 深度优先搜索实现
void Graph::DFS(int startVertex) {
    vector<bool> visited(numVertices, false);
    stack<int> stack;

    visited[startVertex] = true;
    stack.push(startVertex);

    while (!stack.empty()) {
        int currentVertex = stack.top();
        stack.pop();
        cout << currentVertex << " ";

        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[currentVertex][i]!= 0 &&!visited[i]) {
                visited[i] = true;
                stack.push(i);
            }
        }
    }
    cout << endl;
}

// Dijkstra算法实现
void Graph::dijkstra(int startVertex) {
    vector<int> dist(numVertices, numeric_limits<int>::max());
    vector<bool> visited(numVertices, false);

    dist[startVertex] = 0;

    for (int count = 0; count < numVertices - 1; ++count) {
        int u = -1;
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        visited[u] = true;

        for (int v = 0; v < numVertices; ++v) {
            if (adjMatrix[u][v]!= 0 &&!visited[v] &&
                dist[u]!= numeric_limits<int>::max() &&
                dist[u] + adjMatrix[u][v] < dist[v])
                dist[v] = dist[u] + adjMatrix[u][v];
        }
    }

    // 输出最短路径结果
    cout << "顶点\t距离源点的最短距离" << endl;
    for (int i = 0; i < numVertices; ++i) {
        cout << i << "\t\t" << dist[i] << endl;
    }
}

// Prim算法实现
void Graph::prim() {
    vector<int> key(numVertices, numeric_limits<int>::max());
    vector<int> parent(numVertices, -1);
    vector<bool> visited(numVertices, false);

    key[0] = 0;

    for (int count = 0; count < numVertices - 1; ++count) {
        int u = -1;
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i] && (u == -1 || key[i] < key[u]) )
                u = i;
        }

        visited[u] = true;

        for (int v = 0; v < numVertices; ++v) {
            if (adjMatrix[u][v]!= 0 &&!visited[v] &&
                adjMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = adjMatrix[u][v];
            }
        }
    }

    // 输出最小支撑树的边信息
    cout << "边\t权重" << endl;
    for (int i = 1; i < numVertices; ++i) {
        cout << parent[i] << " - " << i << "\t" << adjMatrix[i][parent[i]] << endl;
    }
}

int main() {
    Graph g(5);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    cout << "广度优先搜索结果: ";
    g.BFS(0);

    cout << "深度优先搜索结果: ";
    g.DFS(0);

    cout << "Dijkstra算法求最短路径结果: " << endl;
    g.dijkstra(0);

    cout << "Prim算法求最小支撑树结果: " << endl;
    g.prim();

    return 0;
}