#include "a_star.h"
#include "ui_a_star.h"
#include "dfslog.h"
#include "pboard.h"
#include "mainwindow.h"
#include<qmessagebox.h>
typedef  long long ll;
using namespace  std;
extern int p_mode;
extern Pboard *pb;
extern MainWindow *w;
extern A_star *as;
A_star::A_star(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::A_star)
{
    ui->setupUi(this);
    this->setParent(w);
     this->move(0,350);
    ui->last_button->setEnabled(0);
    ui->next_button->setEnabled(0);
}
vector<ll>mp;
A_star::~A_star()
{
    delete ui;
}
const ll dx[]={-1,0,0,1},dy[]={0,-1,1,0};//转移数组；
void  sswap(int &a,int &b)
{
    int t=a;
     a=b;
     b=t;
}
void A_star::rand_map()
{
    mp.clear();
    int n=rand()%100+5;
    int t=4;
    int init[] ={
         1,2,3,
         8,0,4,
         7,6,5
    };

    while(n--)
    {

        int op=rand()%4;
        if(op==0)
        {
            if(t>=3)
              {swap(init[t],init[t-3]);t-=3;}
        }
        else if(op==1)
            {
             if(t<6)
                {swap(init[t],init[t+3]);t+=3;}
            }
        else if(op==2)
        {
            if(t%3!=0)
               {swap(init[t],init[t-1]);t-=1;}
        }
        else
        {
            if(t%3!=2)
               {swap(init[t],init[t+1]);t+=1;}
        }
       //  cout<<n<<" "<<t<<endl;
    }
    ll tmp=0;
    for(int i =0;i<9;i++)
        tmp=tmp*10+init[i];
    mp.push_back(tmp);

}

map<ll,ll> astar_last;
vector<ll> astar_solv;
void  A_star::bfs()
{

    ll n=mp[0];
    astar_last.clear();
    queue<ll> q;
    q.push(n);
  //  cout<<n<<endl;
    map<ll,ll> m;

    m[n]=0;
    astar_last[n]=-1;
    while(!q.empty())
    {
        ll u=q.front(); //初始状态入队列
       //   cout<<u<<endl;
        mp.push_back(u);
        int c[3][3],f=0,g=0,n=u;q.pop();
        if(u==123804765)break;
        for(ll i=2;i>=0;i--)
            for(ll j=2;j>=0;j--)
            {
                c[i][j]=n%10,n/=10;
                if(!c[i][j])f=i,g=j;
            }
        for(ll i=0;i<4;i++)
        {
            ll nx=f+dx[i],ny=g+dy[i],ns=0;
            if(nx<0||ny<0||nx>2||ny>2)continue; //越界就不执行
            swap(c[nx][ny],c[f][g]);
            for(ll i=0;i<3;i++)
                for(ll j=0;j<3;j++)ns=ns*10+c[i][j];//矩阵转数列
            if(!m.count(ns))
            {
                m[ns]=m[u]+1;//map去重的同时顺便统计到达这个状态所需的步数
                astar_last[ns]=u;
                q.push(ns);
            }
            swap(c[nx][ny],c[f][g]);//状态复原
        }
    }
     ll tmp=123804765;
     astar_solv.clear();
     while(tmp!=-1)
     {
         cout<<tmp<<endl;
        astar_solv.push_back(tmp);
        tmp=astar_last[tmp];
     }
     cout<<"tmp"<<endl;
     reverse(astar_solv.begin(),astar_solv.end());
     cout<<"size"<<mp.size()<<" "<<astar_solv.size()<<endl;
}

int a[5][5],k,judge;
int ans[4][4]=
{{0,0,0,0},
 {0,1,2,3},
 {0,8,0,4},
 {0,7,6,5}};
int check()
{
    for(int i=1;i<=3;++i)
    for(int j=1;j<=3;++j)
    if(ans[i][j]!=a[i][j])return 0;
    return 1;
}

int test(int step)
{
    int cnt=0;
    for(int i=1;i<=3;++i)
    for(int j=1;j<=3;++j)
    if(ans[i][j]!=a[i][j]){ if(++cnt+step>k) return 0;}
    return 1;
}
ll maptonum()
{
    ll tmp=0;
    for(int i =1;i<=3;i++)
        for(int j =1;j<=3;j++)
    {
        tmp=tmp*10+a[i][j];
    }
    return tmp;
}

void _A_star(int step,int x,int y,int pre)
{
    cout<<"come "<<maptonum()<<endl;
    mp.push_back(maptonum());
   // if(step==3) getchar();
    if(step==k){if(check())judge=1; return;}//达到当前限制的最大深度
    if(judge) return;
    for(int i=0;i<4;++i)
    {

        int nx=x+dx[i],ny=y+dy[i];
        if(nx<1||nx>3||ny<1||ny>3||pre+i==3) continue;//加入了上述最优性剪枝
        ll last=maptonum();
        std::swap(a[x][y],a[nx][ny]);
        if(astar_last.count(maptonum())==0)
                     astar_last[maptonum()]=last;
        if(test(step)&&!judge) _A_star(step+1,nx,ny,i);//A*估价合法再向下搜索
        std::swap(a[x][y],a[nx][ny]);
    }
}
void A_star::a_star()
{
    astar_last.clear();
    astar_solv.clear();
    int x,y;
    ll tmpn=mp[0];
    astar_last[tmpn]=-1;
    for(int i=8;i>=0;i--)
       {
            a[i/3+1][i%3+1]=tmpn%10;
            if(tmpn%10==0)x=i/3+1,y=i%3+1;
            tmpn/=10;
       }
     tmpn=mp[0];
     cout<<tmpn<<" "<<maptonum()<<endl;
     if(check()){;return ;}//特判不用移动
     k=0;
     judge=0;
     while(++k)//枚举最大深度
       {
          cout<<"k:"<<k<<endl;

         mp.clear();

         astar_last.clear();
         astar_last[tmpn]=-1;

         //mp.push_back(tmpn);
           _A_star(0,x,y,-1);
           if(judge){break;}
       }
     cout<<mp.size()<<" "<<astar_last.size()<<endl;
     ll tmp=123804765;
     astar_solv.clear();
     while(tmp!=-1)
     {
         cout<<tmp<<endl;
        astar_solv.push_back(tmp);
        tmp=astar_last[tmp];
     }
     cout<<"tmp"<<endl;
     reverse(astar_solv.begin(),astar_solv.end());
}

extern int can_paint;
int astar_time;
int max_time;
void A_star::on_rand_button_clicked()
{
    ui->last_button->setEnabled(0);
    can_paint=1;
    astar_time=0;

    cout<<"x1"<<endl;
    rand_map();
    cout<<"x2"<<endl;
    if(p_mode==4)
    {
        bfs();
    }
    else if(p_mode==5)
    {
        a_star();
    }
    else return;
    if(ui->checkBox->checkState())
    {
        max_time=astar_solv.size();
    }
    else max_time=mp.size();
    cout<<"x3"<<endl;
    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
    pb->show();
    ui->next_button->setEnabled(1);
}

void A_star::on_next_button_clicked()
{
    cout<<astar_time<<" "<<max_time<<endl;
    if(astar_time>=max_time-1)
    {
        QString tmp;

            tmp=tr("已成功找到目标状态\n");
        QMessageBox::about(this,tr("搜索结果"),tmp);
                ui->next_button->setEnabled(0);
        return ;
    }
    ++astar_time;
    can_paint=1;

    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
    pb->show();
    ui->last_button->setEnabled(1);
}

void A_star::on_last_button_clicked()
{
    if(astar_time<=0)
    {

        QMessageBox::about(this,tr("搜索结果"),tr("不能后退了"));
         ui->last_button->setEnabled(0);

        return ;
    }
    --astar_time;
    can_paint=1;
    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
    pb->show();
     ui->next_button->setEnabled(1);
}

void A_star::on_checkBox_stateChanged(int arg1)
{
    astar_time=0;
    if(arg1)
    {
        max_time=astar_solv.size();
    }
    else max_time=mp.size();
    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
    pb->show();
    ui->next_button->setEnabled(1);
    ui->last_button->setEnabled(0);
}

void A_star::on_pushButton_3_clicked()
{
    astar_time=max_time-2;
    on_next_button_clicked();
}
