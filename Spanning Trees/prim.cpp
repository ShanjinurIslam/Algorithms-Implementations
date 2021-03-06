#include <bits/stdc++.h>

using namespace std;

stack<int> s;

class Graph
{
private:
    vector<pair<int, int>> *adj;
    vector<pair<int, int>> *tree;
    int **map;
    bool has_cycle;
    int *num_path;
    int N;
    bool directed;

public:
    Graph(int N, bool directed = false)
    {
        this->N = N;
        adj = new vector<pair<int, int>>[N];
        tree = new vector<pair<int, int>>[N];
        this->directed = directed;
        num_path = new int[N];
        map = new int *[N];
        for (int i = 0; i < N; i++)
        {
            map[i] = new int[N];
        }
    }

    void add_edge(int a, int b, int w)
    {
        a = --a;
        b = --b;
        if (directed)
        {
            adj[a].push_back({b, w});
            map[a][b] = w;
        }
        else
        {
            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
            map[a][b] = w;
            map[b][a] = w;
        }
    }

    void printGraph()
    {
        for (int i = 0; i < this->N; i++)
        {
            cout << i << ": ";
            for (int j = 0; j < adj[i].size(); j++)
            {
                cout << "(" << adj[i][j].first << "," << adj[i][j].second << ")"
                     << " ";
            }
            cout << "\n";
        }
    }

    void dijkstra(int starting_node)
    {
        // jodi visited baire dao tahole starting node true set kore diba na naile loop e dhukbe na
        int distances[N];
        bool visited[N];
        for (int i = 0; i < N; i++)
        {
            distances[i] = INT_MAX;
            visited[i] = false;
        }
        distances[starting_node] = 0;
        priority_queue<tuple<int, int, int>> queue;
        queue.push({0, starting_node, starting_node});

        while (!queue.empty()) // O(n + mlogm )
        {
            tuple<int, int, int> p = queue.top();
            queue.pop();
            int w, a, s;
            tie(w, a, s) = p;

            if (visited[s])
                continue;
            else
                visited[s] = true;
            if (s != starting_node)
            {
                tree[a].push_back({s, map[a][s]});
            }
            for (auto u : adj[s])
            {
                int b = u.first;
                int w = u.second;
                if (distances[s] + w < distances[b])
                {
                    distances[b] = distances[s] + w;
                    queue.push({-distances[b], s, b});
                }
            }
        }

        cout << "Output Tree: " << endl;

        for (int i = 0; i < N; i++)
        {
            cout << (i + 1) << " : ";
            for (auto u : tree[i])
            {
                int b, w;
                tie(b, w) = u;
                printf("(%d,%d) ", b + 1, w);
            }
            cout << endl;
        }
    }

    ~Graph()
    {
        delete[] adj;
    }
};

int main()
{
    Graph graph(5);
    graph.add_edge(1, 2, 3);
    graph.add_edge(1, 3, 5);
    graph.add_edge(2, 3, 2);
    graph.add_edge(3, 4, 2);
    graph.add_edge(2, 4, 4);
    graph.add_edge(2, 5, 8);
    graph.add_edge(4, 5, 1);
    graph.dijkstra(0);
    return 0;
}
