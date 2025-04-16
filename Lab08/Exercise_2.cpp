#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define enl '\n'
#define FOR(i, a, b) for (int i = a; i < b; i++)

using ll = long long;

const ll INF = 20000000000000000LL;

ll nodeCnt;

struct Edge
{
    int u, v;
    ll w;
};

vector<Edge> vec;
vector<ll> dist, trace;
ll source_vertex;

void fordBellman(vector<Edge> &E, vector<ll> &D, vector<ll> &trace, ll S)
{
    D.resize(nodeCnt, INF);
    trace.resize(nodeCnt, -1);
    D[S] = 0;

    FOR(i, 1, nodeCnt)
    {
        for (Edge e : E)
        {
            int v = e.v;
            int u = e.u;
            ll w = e.w;

            if (D[u] != INF && D[u] + w < D[v])
            {
                D[v] = D[u] + w;
                trace[v] = u;
            }
        }
    }
}

void reverseVector(vector<ll> &v)
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

vector<ll> tracePath(vector<ll> &trace, ll S, ll u)
{
    if (trace[u] == -1 && S != u)
    {
        return vector<ll>(0);
    }

    vector<ll> path;
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
    dist.resize(nodeCnt, INF);
    trace.resize(nodeCnt, -1);

    FOR(i, 0, nodeCnt)
    {
        FOR(j, 0, nodeCnt)
        {
            ll w;
            in >> w;
            if (w != 0)
            {
                // cout << i << ' ' << j << ' ' << w << '\n';
                vec.pb({i, j, w});
            }
        }
    }
    in.close();

    // Debug
    // FOR(i, 0, vec.size())
    // {
    //     cout << vec[i].u << ' ' << vec[i].v << ' ' << vec[i].w << '\n';
    // }

    cout << "Enter source vertex: ";
    cin >> source_vertex;

    fordBellman(vec, dist, trace, source_vertex);
    vector<ll> path;

    FOR(i, 0, nodeCnt)
    {
        if (i != source_vertex)
        {
            path = tracePath(trace, source_vertex, i);
            if (path.size() > 0)
            {
                cout << "The shortest path from " << source_vertex << " to " << i << ": ";
                cout << path[0];
                FOR(i, 1, path.size())
                {
                    cout << " -> " << path[i];
                }
                cout << ".\n";
            }
            else
            {
                cout << "No valid path found!\n";
            }
        }
    }
    return 0;
}
