#include <stdio.h>
#include <iostream>
#include <string.h>
#include <list>
#include <string>
#include <vector>
using namespace std;
#define ll long long
#define maxn 100100
int top; // init top is 1
int head[maxn];
int tmp[maxn];
int vis[maxn],father[maxn];
ll ans[maxn];
class node
{
public:
    int cost,father,val,dis,d;
    list<pair<int,int> >st;
    list<pair<int,int> >en;
    void init(int i)
    {
        father=i;val=0;
        st.clear();en.clear();
    }
    void debug()
    {
        printf("cost=%d father=%d val=%d dis=%d d=%d\n",cost,father,val,dis,d);
    }
}a[maxn];
class nodee
{
public:
    int h,val,next;
}que[maxn<<1];
void add(int x,int y,int z)
{
    que[top].h=y,que[top].val=z,que[top].next=head[x];head[x]=top++;
    que[top].h=x,que[top].val=z,que[top].next=head[y];head[y]=top++;
}
int fint(int jj)
{
    return father[jj]==jj?father[jj]:father[jj]=fint(father[jj]);
}
void get(int v)
{
    for(list<pair<int,int> >::iterator j=a[v].st.begin();j!=a[v].st.end();)
    {
        if(ans[j->second]!=-1) {j=a[v].st.erase(j);continue;}
        int jj=j->first;
        
        if(vis[jj])
        {
            int fa=fint(jj);
            int k=jj;
            ll left=0;
            int pri=a[k].cost;
            while(k!=fa)
            {
                left+=(ll)pri*(ll)a[k].d;
                k=a[k].father;
                pri=min(pri,a[k].cost);
            }
            int p=0;
            int vv=v;
            tmp[p++]=vv;
            while(vv!=k)
            {
                tmp[p++]=a[vv].father;
                vv=a[vv].father;
            }
            for(int ii=p-1;ii>0;ii--)
            {
                pri=min(pri,a[tmp[ii]].cost);
                left+=(ll)pri*(ll)a[tmp[ii-1]].d;
            }
            ans[j->second]=left;
            j=a[v].st.erase(j);
        }
        else j++;
    }
    for(list<pair<int,int> >::iterator j=a[v].en.begin();j!=a[v].en.end();)
    {
        if(ans[j->second]!=-1) {j=a[v].en.erase(j);continue;}
        int jj=j->first;
        if(vis[jj])
        {
            int k=jj;
            int left=0;
            int p=0;
            int fa=fint(jj);
            tmp[p++]=k;
            while(k!=fa)
            {
                tmp[p++]=a[k].father;
                k=a[k].father;
            }
            int vv=v;
            int pri=a[vv].cost;
            while(vv!=k)
            {
                left+=(ll)a[vv].d*(ll)pri;
                vv=a[vv].father;
                pri=min(pri,a[vv].cost);
            }
            for(int r=p-2;r>=0;r--)
            {
                left+=(ll)a[tmp[r]].d*(ll)pri;
                pri=min(a[tmp[r]].cost,pri);
            }
            ans[j->second]=left;
            j=a[v].en.erase(j);
        }
        else j++;
    }

}
void dfs(int x,int d,int dis)
{
    a[x].dis=dis;
    a[x].d=d;
    father[x]=x;
    for(int i=head[x];i;i=que[i].next)
    {
        int v=que[i].h;
        if(v==a[x].father) continue;
        a[v].father=x;
        dfs(v,que[i].val,que[i].val+dis);
        father[v]=x;
        vis[v]=1;
        get(v);
    }
    vis[x]=1;
    get(x);
}
void lca(int x)
{
    
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        memset(head,0,sizeof(head));
        top=1;
        int x,y,z;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i].cost);
            a[i].init(i);
            father[i]=i;
        }
        for(int i=1;i<n;i++)
        {
            cin>>x>>y>>z;
            add(x,y,z);
        }
        for(int i=0;i<m;i++)
        {
            cin>>x>>y;
            a[x].en.push_back(make_pair(y,i));
            a[y].st.push_back(make_pair(x,i));
        }
        memset(vis,0,sizeof(vis));
        memset(ans,-1,sizeof(ans));
        lca(1);
        dfs(1,0,0);
        for(int i=0;i<m;i++)
        {
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}
//光落在你脸上
//可爱一如往常
//你的一寸一寸
//填满欲望
//城市啊有点脏
//路人行色匆忙
//孤单 脆弱 不安
//都是平常
//你低头不说一句
//你朝着灰色走去
//你住进混沌深海
//你开始无望等待
//你低头不说一句
//你朝着灰色走去
//你住进混沌深海
//你开始无望等待
//
//快乐缺点勇气
//浪漫缺点诗意
//沉默一句一句
//都是谜题
//都清醒都独立
//妄想都没痕迹
//我们一声不吭
//慢慢窒息
//你低头不说一句
//你朝着灰色走去
//你住进混沌深海
//你开始无望等待
//你低头不说一句
//你朝着灰色走去
//你住进混沌深海
//你开始无望等待