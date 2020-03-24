#include "ui_dfslog.h"
#include "dfslog.h"
#include "pboard.h"
#include "mainwindow.h"
#include<qmessagebox.h>
#include<QString>
#include <QElapsedTimer>
extern int p_mode;
extern   int can_paint;
extern dfslog * dl;
extern Pboard *pb;
extern MainWindow *w;
vector<int> g[MAXN];
int vis[MAXN][MAXN];
int n,m;
int val[MAXN];
dfslog::dfslog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dfslog)
{
    ui->setupUi(this);
    memset(vis,0,sizeof vis);
    this->setParent(w);
     this->move(0,350);
    ui->last_Button->setEnabled(0);
    ui->next_Button->setEnabled(0);
}
void dfslog::rand_map()
{
    memset(vis,0,sizeof vis);
    for(int i =0;i<MAXN;i++) g[i].clear();
    n =rand()%10+2;
    if(n<6)
    m = (rand()%n+1)*(n-1)/2;
    if(p_mode==3||p_mode==4) m=(rand()%2+1)*n;
    else m=(rand()%3+1)*n;
   int tmp=m;
   int rtime=0;
   while(tmp--)
   {
        int a=rand()%n;
        int b=rand()%n;
        rtime=0;
        while(a==b||vis[a][b])
        {
            rtime++;
            if(rtime>1000&&a!=b) {m--;break;}
            b=rand()%n;

        }
        if(rtime>1000) continue;
       vis[a][b]=1;
       g[a].push_back(b);
       g[b].push_back(a);
   }
   if(p_mode==3)
       for(int i=0;i<n;i++) val[i]=rand()%(n*n)+2;
   for(int i =0;i<n;i++)
       sort(g[i].begin(),g[i].end());

}
bool  closed[MAXN];
int dfstime=0;
int dfs_close[MAXN*MAXN];
bool _dfs(int x,int r)
{
    if(x==r)
    {
        return 1;
    }
    for(int i =0;i<g[x].size();i++)
    {
        if(closed[g[x][i]]) continue;
        closed[g[x][i]]=1;
        dfs_close[++dfstime]=g[x][i];
        if(_dfs(g[x][i],r)) return 1;
         dfs_close[++dfstime]=x;
    }
    return 0;
}
int b_time=0;
void dfslog::dfs(int s, int r)
{
    memset(closed,0,sizeof closed);
    closed[s]=1;
    dfstime=0;
    dfs_close[dfstime]=s;
    _dfs(s,r);
}
int bfs_last[MAXN];
void dfslog::bfs(int s, int r)
{
    memset(closed,0,sizeof closed);
    memset(bfs_last,-1,sizeof bfs_last);
    queue<int>q;
    closed[s]=1;
    q.push(s);
    dfstime=-1;
    while(q.size())
    {
        int x=q.front();q.pop();
        dfs_close[++dfstime]=x;

        if(x==r) return;
        for(int i =0;i<g[x].size();i++)
        {
             if(closed[g[x][i]]) continue;
             bfs_last[g[x][i]]=x;
             q.push(g[x][i]);
             closed[g[x][i]]=1;
           /* if(g[x][i]==r)
            {
                 dfs_close[++dfstime]=g[x][i];
                 return ;
            }*/
        }
    }
    return ;
}
struct node
{
    int x;
    int dis;
    friend bool operator <(node a,node b)
    {
        return a.dis>b.dis;
    }
    node(int a=0,int b=0)
    {
        x=a;dis=b;
    }
};

void dfslog::pri_bfs(int s, int r)
{
    memset(closed,0,sizeof closed);
    memset(bfs_last,-1,sizeof bfs_last);
    priority_queue<node>q;
    closed[s]=1;
    q.push(node(s,0));
    dfstime=-1;
    while(q.size())
    {
        node v=q.top();q.pop();
        int x=v.x;
        dfs_close[++dfstime]=x;

        if(x==r) return;
        for(int i =0;i<g[x].size();i++)
        {
             if(closed[g[x][i]]) continue;
             bfs_last[g[x][i]]=x;
             q.push(node(g[x][i],val[g[x][i]]+v.dis));
             closed[g[x][i]]=1;
           /* if(g[x][i]==r)
            {
                 dfs_close[++dfstime]=g[x][i];
                 return ;
            }*/
        }
    }
    return ;
}
dfslog::~dfslog()
{
    delete ui;
}

void dfslog::on_next_Button_clicked()
{
    if(b_time>=dfstime)
    {
        QString tmp;
        if(dfs_close[dfstime]==n-1)// 判断是否找到
        {
            tmp=tr("已成功找到目标点\n");
        }
        else tmp=tr("无法找到目标点\n");
        QMessageBox::about(this,tr("搜索结果"),tmp);
        return ;
    }
    ++b_time;
    can_paint=1;

    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
    pb->show();
    if(b_time==dfstime)
            ui->next_Button->setEnabled(0);
    ui->last_Button->setEnabled(1);

}

void dfslog::on_rand_Button_clicked()
{
    ui->last_Button->setEnabled(0);
    cout<<"x1"<<endl;
    b_time=0;
    can_paint=1;
    cout<<"x2"<<endl;
    rand_map();
    cout<<"x3"<<endl;
    if(pb!=NULL) {delete pb;pb=NULL;}
    cout<<"x4"<<endl;
    if(p_mode==1)
    dfs(0,n-1);
    else if(p_mode==2)
        bfs(0,n-1);
    else if(p_mode==3)
           pri_bfs(0,n-1);
     else return;
     cout<<"x5"<<endl;
    pb=new Pboard;
    pb->show();
    cout<<"x6"<<endl;
    ui->next_Button->setEnabled(1);
}
bool dfslog::is_circle()
{
    return ui->check_circle->isChecked();
}
void dfslog::on_check_circle_stateChanged(int arg1)
{
   // cout<<arg1<<endl;
    if(can_paint&&dfstime)
    {
        if(pb!=NULL) {delete pb;pb=NULL;}
        pb=new Pboard;
        pb->show();
    }
}

void delay_3(int msec)
{
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<msec);
}
void dfslog::on_pushButton_3_clicked()
{
       b_time=dfstime-1;
       on_next_Button_clicked();
}



void dfslog::on_last_Button_clicked()
{
    if(b_time<=1)
    {

        QMessageBox::about(this,tr("搜索结果"),tr("不能后退了"));
        if(b_time==1)
                ui->last_Button->setEnabled(0);
        ui->next_Button->setEnabled(1);
        return ;
    }
    --b_time;
    can_paint=1;
    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
    pb->show();
    if(b_time==1)
            ui->last_Button->setEnabled(0);
    ui->next_Button->setEnabled(1);

}
