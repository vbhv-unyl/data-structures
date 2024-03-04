/*
        author : vbhv-unyl

        Title : Square Root Decomposition

        Description : Implmentation of square root decomposition data structure, this can do range 
        sum query and range update in O(√n), while point update in O(1).
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
#define     pb(x)           push_back(x)
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

template<typename T> class sqrt_decompose {
private:
    ll sz;
    vector<T> a, b;

    ll getSize(ll n) {
        ll l = 0, r = 1e9;
        while(r > l + 1) {
            ll m = (l + r) >> 1;
            if(m * m > n) {
                r = m;
            }
            else {
                l = m;
            }
        } 
        return r;
    }

    void build(vector<T> &a) {
        ll n = a.size();
        for(int i = 0; i < n; i++) {
            b[i / sz] += a[i];
        }  
    }

    ll query(ll l, ll r, ll x) {
        ll L = l / sz, R = r / sz, n = a.size(), tot = 0;

        if(L == R) {
            for(int i = l; i <= r; i++) tot += a[i];
            return tot;
        }

        for(int i = L + 1; i < R; i++) {
            tot += b[i];
        }

        tot = tot + a[l] + a[r];
        while(l < n - 1 && (l / sz) == (l + 1) / sz) tot += a[++l];
        while(r > 0 && (r / sz) == ((r - 1) / sz)) tot += a[--r];

        return tot;
    }

    void update(ll idx, ll val, ll d) {
        a[idx] = val;
        b[idx / sz] += d;
    }

public:
    sqrt_decompose(ll n) {
        cout << getSize(n) << '\n';
    }

    sqrt_decompose(vector<T> &a) {
        this->a = a;
        sz = getSize(a.size());
        this->b.resize(sz, 0);
        build(a);
    }

    ll query(ll l, ll r) {
        return query(l, r, 0);
    }

    void update(ll idx, ll val) {
        update(idx, val, val - a[idx]);
    }
};

void tests()
{   
    ll n;
    cin >> n;
    vi a(n);
    rep(i,0,n) cin >> a[i];

    sqrt_decompose<ll> sq(a);

    cout << sq.query(1, 3) << '\n' << '\n';
    sq.update(2, 100);
    cout << sq.query(1,2) << '\n' << '\n';
}

signed main()
{
    speed;
    int tt = 1;
    while(tt--)
      tests();
    return 0;
}