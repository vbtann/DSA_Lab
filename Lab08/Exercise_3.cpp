#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define enl '\n'
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)

using ll = long long;

struct Edge
{
    int u, v;
    ll w;
};

struct Node
{
    int v;
    ll w;
};

struct cmp
{
    bool operator()(const Edge &u, const Edge &v)
    {
        return u.w > v.w;
    }
};

vector<Edge> edges;
vector<vector<Node>> nodesList;
vector<ll> distance, trace;
ll nodeCnt;

vector<Edge> prim()
{
    vector<bool> visited(nodeCnt, false);
    int source_node = 0;
    visited[source_node] = 1;
    vector<Edge> mst_edges;

    priority_queue<Edge, vector<Edge>, cmp> nodeQu;

    for (Node n : nodesList[source_node])
    {
        nodeQu.push({source_node, n.v, n.w});
    }

    while (!nodeQu.empty() && mst_edges.size() < nodeCnt)
    {
        Edge cur = nodeQu.top();
        nodeQu.pop();

        int u = cur.u, v = cur.v;
        ll w = cur.w;

        if (visited[v])
        {
            continue;
        }

        mst_edges.pb(cur);

        visited[u] = 1;

        for (Node e : nodesList[v])
        {
            int next_v = e.v;
            ll next_w = e.w;

            if (!visited[next_v])
            {
                nodeQu.push({v, next_v, next_w});
            }
        }
    }

    return mst_edges;
}

void printList(vector<vector<Node>> v)
{
    FOR(i, 0, nodeCnt)
    {
        for (Node n : nodesList[i])
        {
            cout << i << ' ' << n.v << ' ' << n.w << enl;
        }
    }
}

int main(void)
{
    fstream in("graph.txt", ios::in);
    in >> nodeCnt;
    nodesList.resize(nodeCnt);
    FOR(i, 0, nodeCnt)
    {
        FOR(j, 0, nodeCnt)
        {
            int w;
            in >> w;
            if (w)
            {
                nodesList[i].pb({j, w});
            }
        }
    }

    // Debug
    // printList(nodesList);

    vector<Edge> mst_edges;

    mst_edges = prim();

    cout << "Edge   Weight" << enl;
    FOR(i, 0, mst_edges.size())
    {
        cout << mst_edges[i].u << " - " << mst_edges[i].v << "  " << mst_edges[i].w << enl;
    }

    return 0;
}