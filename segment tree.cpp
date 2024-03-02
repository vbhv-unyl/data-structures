/*
        author : vbhv-unyl

        Title : Segment Tree

        Description : Implmentation of segment tree data structure, this can do range 
        min query and point update in O(log n).
*/

#include <bits/stdc++.h>
#include<chrono>
#include<random>
using namespace std;
using namespace chrono;

#define     ll              long long
#define     vi              vector<ll>
#define     pi              pair<ll, ll>
#define     vii             vector<pi>
#define     vvi             vector<vi>
#define     mpi             map<ll, ll>
#define     all(x)          (x).begin(), (x).end()
#define     rall(x)         (x).rbegin(), (x).rend()
#define     popcnt(x)       __builtin_popcount(x)
#define     eb(x)           emplace_back(x)
#define     ff              first
#define     ss              second
#define     speed           cin.tie(NULL)->sync_with_stdio(false)
#define     rep(i, a, b)    for (ll i = (ll)a; i < (ll)b; i++)
#define     reb(i, a, b)    for (ll i = (ll)a; i >= (ll)b; i--)
mt19937     generator (std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e5 + 2, MOD = 1e9 + 7;
const ll INF = 9e18;

ll getNumber(ll l, ll r) {
return uniform_int_distribution<ll>(l, r)(generator);
}

template<typename T> class segment_tree{
private:
    vector<T> tree;
    ll sz;

    void build(ll node, ll L, ll R, vi &a){
        if(L == R){
            tree[node] = a[L];
            return;
        }

        ll M = (L + R) / 2;
        build(2 * node + 1, L, M, a);
        build(2 * node + 2, M + 1, R, a);
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }

    ll query(ll node, ll l, ll r, ll L, ll R){
        if(l <= L && R <= r){
            return tree[node];
        }

        if(r < L || l > R){
            return INT_MAX;
        }

        ll M = (L + R) / 2;
        return min(query(2 * node + 1, l, r, L, M), query(2 * node + 2, l, r, M + 1, R));
    }

    void update(ll node, ll idx, ll val, ll L, ll R){
        if(L == R){
            tree[node] = val;
            return;
        }

        ll M = (L + R) / 2;
        if(idx <= M) {
            update(2 * node + 1, idx, val, L, M);
        }
        else {
            update(2 * node + 2, idx, val, M + 1, R);
        }

        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }

public:
    segment_tree(ll n = 0){
        this->sz = n;
        tree.resize(4 * n);
    }

    void build(vi &a){
        build(0, 0, this->sz - 1, a);
    }
    
    ll query(ll l, ll r){
        return query(0, l, r, 0, this->sz - 1);
    }

    void update(ll idx, ll val){
        update(0, idx, val, 0, this->sz - 1);
    }
};

void tests()
{
    ll n, q;
    cin >> n;
    vi a(n);
    rep(i,0,n) cin >> a[i];

    segment_tree<ll> tree(n);
    tree.build(a);

    tree.update(0, 1);
    tree.update(1, 2);
    tree.update(3, 5);

    cin >> q;
    while(q--){
        ll l, r;
        cin >> l >> r;
        cout << tree.query(l, r) << '\n';
    }
}

signed main()
{
    speed;
    int tt = 1;
    while(tt--)
        tests();
    return 0;
}