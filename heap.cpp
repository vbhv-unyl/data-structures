/*
        author : vbhv-unyl

        Title : Modular Heap Data Structure

        Description : This a modular class, designed to implement min and max heap
        at the same time. The constructor of the class has two parameters :-
        1. An array a - Heap will be built initially on this array.
        2. A flag variable - If true you will get a min heap and max heap otherwise.

        By default the value of the flag is false and you'll create a max heap.
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

template<typename T> class Heap {
private:
    ll sz;
    bool flag;
    vector<T> heap;

    void heapify_up(ll i) {
        ll idx = i;
        while(idx > 0) {
            ll parent = (idx - 1) >> 1;
            if(!flag) {
                if(heap[parent] < heap[idx]) {
                    swap(heap[parent], heap[idx]);
                    idx = parent;
                }
                else break;
            }
            else {
                if(heap[parent] > heap[idx]) {
                    swap(heap[parent], heap[idx]);
                    idx = parent;
                }
                else break;
            }
        }
    }

    void heapify_down() {
        ll i = 0;
        swap(heap[0], heap.back());
        heap.pop_back();
        sz--;

        ll prev = i;
        while(1) {
            ll left = -1, right = -1;
            if((i << 1) + 1 < sz) left = (i << 1) + 1;
            if((i << 1) + 2 < sz) right = (i << 1) + 2;
            if(left == -1 && right == -1) break;

            if(left != -1 && right != -1) {
                ll val = heap[i], idx = i;

                if(!flag) {
                    if(heap[left] > val) val = heap[left], idx = left;
                        
                    if(heap[right] > val) val = heap[right], idx = right;
                }
                else {
                    if(heap[left] < val) val = heap[left], idx = left;  
                        
                    if(heap[right] < val) val = heap[right], idx = right;
                    
                }

                swap(heap[i], heap[idx]);
                i = idx;

            }
            else if(left != -1) {
                ll idx = i;
                if(!flag) {
                    if(heap[left] > heap[idx]) idx = left;
                }
                else {
                    if(heap[left] < heap[idx]) idx = left;
                }

                swap(heap[i], heap[idx]);
                i = idx;
            }
            else if(right != -1){
                ll idx = i;
                if(!flag) {
                    if(heap[right] > heap[idx]) idx = right;
                }
                else {
                    if(heap[right] < heap[idx]) idx = right;
                }

                swap(heap[i], heap[idx]);
                i = idx;
            }

            if(i == prev) break;
            prev = i;
        }
    }

    void build() {
        for(ll i = (sz >> 1); i < sz; i++) heapify_up(i);
    }

public:
    Heap(vector<T> &a, bool flag = false) {
        this->flag = flag;
        this->heap = a;
        this->sz = heap.size();
        build();
    }

    void push(ll x) {
        if(heap.empty()) {
            heap.push_back(x);
        }
        else {
            heap.push_back(x);
            ll idx = sz;
            ++sz;
            heapify_up(idx);
        }
    }

    void pop() { heapify_down(); }

    ll get() {
        if(heap.empty()) return ((flag) ? INT_MIN : INT_MAX);
        return heap[0];
    }
};

void tests()
{   
    ll n;
    cin >> n;
    vi a(n);
    for(auto &x: a) cin >> x;

    /*
        Array a = {4, 9, 3, 10, 5}
        You will get 10 as the top of heap and 3, when you create min heap
    */

    /* 
        maxheap by default

        For a minheap, do this : Heap<ll> heap(a, 1);
    */

    Heap<ll> heap(a);
    heap.push(1);
    heap.pop();
    cout << heap.get();
}

signed main()
{
    int tt = 1;
    while(tt--)
      tests();
    return 0;
}