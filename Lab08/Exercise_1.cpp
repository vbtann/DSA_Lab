#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define enl '\n'
#define FOR(i, a, b) for (int i = a; i < b; i++)

const long long INF = (int)2000000000000000LL;

using ll = long long;
using ii = pair<ll, ll>;

struct Node
{
    int u;
    long long dist_u;
};

struct Edge
{
    int v;
    long long w;
};

struct cmp
{
    bool operator()(Node a, Node b)
    {
        return a.dist_u > b.dist_u;
    }
};

vector<vector<Edge>> vec;
vector<long long> dist, trace;
int source_vertex;
int nodeCnt;

void dijkstra(vector<vector<Edge>> &E, vector<long long> &D, vector<long long> &trace, int src)
{
    fill(D.begin(), D.end(), INF); // Use fill instead of resize
    fill(trace.begin(), trace.end(), -1);
    vector<bool> visited(nodeCnt, false);
    D[src] = 0;

    priority_queue<Node, vector<Node>, cmp> nodeQu;

    nodeQu.push({src, D[src]});

    while (!nodeQu.empty())
    {
        Node cur = nodeQu.top();
        nodeQu.pop();

        int cur_u = cur.u;
        if (visited[cur_u])
        {
            continue;
        }

        visited[cur_u] = 1;

        for (Edge e : E[cur_u])
        {
            int v = e.v;
            long long w = e.w;

            if (D[v] > D[cur_u] + w)
            {
                D[v] = D[cur_u] + w;
                nodeQu.push({v, D[v]});
                trace[v] = cur_u;
            }
        }
    }
}

void reverseVector(vector<long long> &v)
{
    int l = 0, r = v.size() - 1;
    while (l < r)
    {
        ll tmp = v[l];
        v[l] = v[r];
        v[r] = tmp;

        r--;
        l++;
    }
}

vector<long long> tracePath(vector<long long> &trace, int S, int u)
{
    if (u != S && trace[u] == -1)
        return vector<long long>(0);

    vector<long long> path;
    path.pb(u);

    while (trace[u] != -1)
    {
        u = trace[u];
        path.pb(u);
    }

    reverseVector(path);
    return path;
}

int main()
{

    fstream in("graph.txt", ios::in);
    in >> nodeCnt;

    vec.resize(nodeCnt);
    dist.resize(nodeCnt);
    trace.resize(nodeCnt);

    FOR(i, 0, nodeCnt)
    {
        FOR(j, 0, nodeCnt)
        {
            int w;
            in >> w;
            if (w != 0)
            {
                vec[i].pb({j, w});
            }
        }
    }
    in.close();

    // Debug
    // FOR(i, 0, nodeCnt)
    // {
    //     for (int j = 0; j < vec[i].size(); j++)
    //     {
    //         cerr << i << ' ' << vec[i][j].v << ' ' << vec[i][j].w << '\n';
    //     }
    // }

    cout << "Enter source vertex: ";
    cin >> source_vertex;

    dijkstra(vec, dist, trace, source_vertex);
    vector<long long> path;
    FOR(i, 0, nodeCnt)
    {
        if (i != source_vertex)
        {
            cout << "Shortest path from " << source_vertex << " to " << i << ": ";
            path = tracePath(trace, source_vertex, i);
            if (path.size() > 0)
            {
                cout << path[0];
                FOR(j, 1, path.size())
                {
                    cout << " -> " << path[j];
                }
                cout << ".\n";
            }
            else
            {
                cout << "No path exists.\n";
            }
        }
    }
    return 0;
}
