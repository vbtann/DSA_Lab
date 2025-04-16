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

struct Node
{
    int v;
    ll w;
};

struct Edge
{
    int u, v;
    ll w;
};

struct cmp
{
    bool operator()(const Edge &u, const Edge &v)
    {
        return u.w > v.w;
    }
};

ll nodeCnt;

vector<Edge> edges;

struct DSU
{
    vector<ll> parent;
    void init(ll n)
    {
        parent.resize(n + 1);
        FOR(i, 0, n)
        {
            parent[i] = i;
        }
    }

    ll find(ll x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        else
        {
            return x = find(parent[x]);
        }
    }

    bool join(ll u, ll v)
    {
        ll u_par = find(u), v_par = find(v);

        if (u_par == v_par)
        {
            return 0;
        }
        else
        {
            parent[v_par] = u_par;
            return 1;
        }
    }

} dsu;

void quickSort(vector<Edge> &e, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int p = e[l + (r - l) / 2].w;
    int i = l, j = r;
    while (i <= j)
    {
        while (e[i].w < p)
        {
            i++;
        }

        while (e[j].w > p)
        {
            j--;
        }
        if (i <= j)
        {
            Edge tmp = e[i];
            e[i] = e[j];
            e[j] = tmp;
            i++;
            j--;
        }
    }
    if (i < r)
    {
        quickSort(e, i, r);
    }
    if (l < j)
    {
        quickSort(e, l, j);
    }
}

vector<Edge> kruskal()
{
    vector<Edge> path;

    quickSort(edges, 0, edges.size() - 1);

    cout << "DEBUG\n";
    for (Edge e : edges)
    {
        cout << e.u << ' ' << e.v << ' ' << e.w << enl;
    }
    cout << "DEBUG\n";

    dsu.init(nodeCnt);

    for (Edge edge : edges)
    {
        if (dsu.join(edge.u, edge.v))
        {
            path.pb(edge);

            if (path.size() == nodeCnt - 1)
            {
                break;
            }
        }
    }

    return path;
}

int main(void)
{

    fstream in("graph.txt", ios::in);
    in >> nodeCnt;

    FOR(i, 0, nodeCnt)
    {
        FOR(j, 0, nodeCnt)
        {
            ll w;
            in >> w;
            if (w)
            {
                edges.pb({i, j, w});
            }
        }
    }
    in.close();

    vector<Edge> mst;
    mst = kruskal();

    cout << "Edge   Weight\n";
    for (Edge e : mst)
    {
        cout << e.u << " - " << e.v << "    " << e.w << enl;
    }

    return 0;
}