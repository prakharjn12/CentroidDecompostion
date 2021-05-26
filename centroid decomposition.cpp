      // takes vec as input and gives vec2 as centroid decomposed output
#include<iostream>             
#include<vector>   
#include<bits/stdc++.h>
#define mod 1000000007
#define pi 3.14159265358979
#define  PRE(x,p) cout<<setprecision(x)<<p; 
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define endl "\n"
#define high INT_MAX
#define low INT_MIN
#define ll long long int

using namespace std;


void showa(ll a[],ll n){ for(ll i=1;i<=n;i++) cout<<a[i]<<' ';  cout<<endl;  }
void showv(vector<ll>v){ for(ll i=0;i<v.size();i++) cout<<v[i]<<' '; cout<<endl;}
vector<ll>vec[200005],vec2[200005];
struct CentroidDecomposition {

    vector<set<int>> tree; // it's not vector<vector<int>>!
    vector<int> dad;
    vector<int> sub;
   

    CentroidDecomposition(vector<set<int>> &tree) : tree(tree) {
        int n = tree.size();
        dad.resize(n);
        sub.resize(n);
        build(0, -1);
        
        for(int i=0;i<dad.size();i++)
        {
              if(i+1==dad[i]) continue;
              vec2[i+1].pb(dad[i]);
              vec2[dad[i]].pb(i+1);
        }
    }

    void build(int u, int p) {
        int n = dfs(u, p); // find the size of each subtree
        int centroid = dfs(u, p, n); // find the centroid
        if (p == -1) p = centroid; // dad of root is the root itself
        dad[centroid] = p+1;
        vector<int>to;
        for (auto v : tree[centroid])
        to.pb(v);
        
        for(int i=0;i<to.size();i++)
          {
                  tree[centroid].erase(to[i]), // remove the edge to disconnect
            tree[to[i]].erase(centroid), // the component from the tree
            build(to[i], centroid); 
                
          }
    
    }

    int dfs(int u, int p) {
        sub[u] = 1;

        for (auto v : tree[u])
            if (v != p) sub[u] += dfs(v, u);

        return sub[u];
    }

    int dfs(int u, int p, int n) {
        for (auto v : tree[u])
            if (v != p and sub[v] > n/2) return dfs(v, u, n);

        return u;
    }

    int operator[](int i) {
        return dad[i];
    }
};



void dfs(ll u, ll p)
{
    ll j,v;
    for(j=0;j<vec2[u].size();j++)
    {
        v=vec2[u][j];
        if(v==p) continue;
        cout<<u<<' '<<v<<endl;
        dfs(v,u);
    }

}
void solve() 
{ 
   ll n,i;
   cin>>n;
   for(i=0;i<n;i++)
   {
       vec[i].clear();
       vec2[i].clear();
   }

   for(i=1;i<n;i++)
   {
       ll u,v;
       cin>>u>>v;
       u--;
       v--;
       vec[u].pb(v);
       vec[v].pb(u);
   }
      vector<set<int>>tr;
      tr.resize(n);
  
   for(i=0;i<n;i++)
   {
    for(int j=0;j<vec[i].size();j++)
    {
        tr[i].insert(vec[i][j]);
        tr[vec[i][j]].insert(i);
    }
   }
    CentroidDecomposition cd(tr);
dfs(1,0);

}
int main()
{
 #ifndef ONLINE_JUDGE
 freopen("input.txt", "r", stdin);
 freopen("output.txt", "w", stdout);
 #endif
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);

ll t=1;
cin>>t;
for(ll test=1;test<=t;test++)
{
    // cout<<"CASE #"<<test<<": ";
    solve();
}

return 0;
}
