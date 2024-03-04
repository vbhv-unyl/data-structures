/*
        author : vbhv-unyl

        Title : Trie

        Description : Implmentation of trie data structure, this can store strings
        as prefix of each other supporting insert, search and delete operations.

        Time Complexity :

        insert : O(m)
        search : O(m)
        delete : O(m)

        m is length of the string
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

struct node{
    bool isWord;
    node *child[26];
};

node* newNode(){
    node *root = new node();
    root->isWord = false;
    rep(i,0,26) root->child[i] = NULL;
    return root;
}

class trie {
private:  
    node* root;

    ll count(node* n) {
        ll cnt;
        for(int i = 0; i < 26; i++) cnt += !(n->child[i]);
        return cnt;
    }

    void Insert(string in, bool f){
        node* root = this->root;
        ll n = in.size();
        rep(i,0,n){
            if(!root->child[in[i] - 'a']) 
                root->child[in[i] - 'a'] = newNode();

            root = root->child[in[i] - 'a'];
        }
        root->isWord = true;
    }

    bool Search(string in, bool f){
        node* root = this->root;
        ll n = in.size();
        rep(i,0,n){
            if(!root->child[in[i] - 'a'])
                return false;

            root = root->child[in[i] - 'a'];
        }

        return root->isWord;
    }

    node* Delete(node* root, string in, int i, int n) {
        if(i == n - 1) {
            if(root->isWord && count(root)) {
                root->isWord = false;
                return root;
            }
            else if(root->isWord) {
                delete root;
                return NULL;
            }
            else return root;
        }

        root->child[in[i+1] - 'a'] = Delete(root->child[in[i+1] - 'a'], in, i + 1, n);
        if(!root->isWord && !count(root)) {
            delete root;
            return NULL;
        }
        else {
            return root;
        }
    }

public:
    trie() {
        this->root = newNode();
        this->root->isWord = true;
    }

    void Insert(string in) {
        Insert(in, 1);
    }

    bool Search(string in) {
        return Search(in, 1);
    }

    void Delete(string in) {
        if(!Search(in)) return;
        this->root->child[in[0] - 'a'] = Delete(this->root->child[in[0] - 'a'], in, 0, in.size());
    }
};

void tests()
{
    trie t;
    t.Insert("aab");
    t.Insert("aabc");
    t.Insert("aabcd");
    t.Insert("abcd");

    cout << t.Search("aa") << '\n';

    t.Delete("aabcd");
    cout << t.Search("aabc") << '\n';
}

signed main()
{
    speed;
    int tt = 1;
    while (tt--)
        tests();
    return 0;
}