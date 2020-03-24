#include "pboard.h"
#include "ui_pboard.h"
#include "dfslog.h"
#include "pboard.h"
#include "mainwindow.h"
#include "chess.h"
#include<QVector>
typedef  long long ll;
extern int p_mode;
extern   int can_paint;
extern dfslog * dl;
extern Pboard *pb;
extern MainWindow *w;
extern chess *cs;
extern vector<int> g[MAXN];
extern int vis[MAXN][MAXN];
extern int n,m;
#define PI 3.14159265
const int h=300;
Pboard::Pboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pboard)
{
    ui->setupUi(this);
    this->setParent(w);
    this->move(350,0);
}

Pboard::~Pboard()
{
    delete ui;
}
QVector<QPointF>dv;
int flag=0;
extern int dfstime;
extern int dfs_close[MAXN*MAXN];
extern int b_time;
bool painted[MAXN];
double f_abs(double x)
{
    return x>0?x:-x;
}
extern int bfs_last[MAXN];
extern int val[MAXN];
extern vector<ll>astar_solv;
extern vector<ll>mp;
extern int astar_time;
extern int max_time;
extern int cb_time;
extern vector<ll> cmp;
extern int ch[25][25];
void Pboard::paintEvent(QPaintEvent *)
{
    memset(painted,0,sizeof painted);
    QPainter painter(this);
    QPen pen; //画笔
    pen.setColor("black");
    QBrush brush(QColor(255, 255, 255)); //画刷
    pen.setWidth(2);
    painter.setPen(pen); //添加画笔
    painter.setBrush(brush); //添加画刷
    // painter.drawEllipse(0,0, 20, 20);
   //  painter.drawEllipse(0,750, 20, 20);
   //    painter.drawEllipse(750,750, 20, 20);
   //       painter.drawEllipse(750,0, 20, 20);
    if(can_paint)
        {
        if(p_mode==1||p_mode==2||p_mode==3){

            cout<<"begin"<<endl;
            if(b_time==0){
                 dv.clear();
            if(dl->is_circle()) {
            for(int i =0;i<n;i++)
            {
                 double sita=i*360*PI/n/180;
                 dv.push_back(QPointF(mid-h*cos(sita), mid+h*sin(sita)));
                // painter.drawEllipse(dv[i], 20, 20);
            }
            }
            else
            {
                for(int i =0;i<n;i++)
                {
                    double tx=rand()%600+50,ty=rand()%600+50;
                    int flag=0;
                    int rtime=0;
                    while(flag==0){
                        rtime++;
                        flag=1;
                    for(int j =0;j<i;j++)
                    {

                        if((f_abs(dv[j].x()-(double)tx)<=30)||(f_abs(dv[j].y()-(double)ty)<=30)||((dv[j].y()-ty)*(dv[j].y()-ty)+ (dv[j].x()-tx)*(dv[j].x()-tx)<50*50))
                            if(rtime<1e6)
                                    {tx=rand()%600+50;ty=rand()%600+50;flag=0;break;}
                      }
                    }
                     dv.push_back(QPointF(tx,ty));

                }
            }
            }
              ///////////////画线

            for(int i=0;i<n;i++)
                for(int j =0;j<g[i].size();j++)
                {
                    painter.drawLine(dv[i],dv[g[i][j]]);
                }
            pen.setWidth(4);
            pen.setColor("orange");
            painter.setPen(pen);
            if(p_mode==1){
            for(int i =1;i<=b_time;i++)
            {
            painter.drawLine(dv[dfs_close[i]],dv[dfs_close[i-1]]);
            }
        }
            else if(p_mode==2||p_mode==3)
                {
                for(int i =1;i<=b_time;i++)
                {
                painter.drawLine(dv[dfs_close[i]],dv[bfs_last[dfs_close[i]]]);
                }
            }
            //////////先画当前节点,再画起点,目标点,最后画剩下的
                int now=dfs_close[b_time],s=0,t=n-1;
                 pen.setWidth(3);
                if(now==s)
                {
                    pen.setColor("green" );
                    brush.setColor("orange");
                    painter.setPen(pen);
                    painter.setBrush(brush);
                    painter.drawEllipse(dv[s], 20, 20);
                    painted[s]=1;
                }
                else {

                    pen.setColor("green" );
                    brush.setColor(QColor(255, 255, 255));
                    painter.setPen(pen);
                    painter.setBrush(brush);
                    painter.drawEllipse(dv[s], 20, 20);
                    painted[s]=1;
                }

                if(now==t)
                {
                    pen.setColor("red" );
                    brush.setColor("orange");
                    painter.setPen(pen);
                    painter.setBrush(brush);
                    painter.drawEllipse(dv[t], 20, 20);
                    painted[t]=1;
                }
                else {
                    pen.setColor("red" );
                    brush.setColor(QColor(255, 255, 255));
                    painter.setPen(pen);
                    painter.setBrush(brush);
                    painter.drawEllipse(dv[t], 20, 20);
                    painted[t]=1;
                }
                if(!painted[now])
                {
                    pen.setColor("orange");
                    painter.setPen(pen);
                    brush.setColor("orange");
                    painter.setBrush(brush);
                    painter.drawEllipse(dv[now], 20, 20);
                    painted[now]=1;
                }
                pen.setColor("orange");
               brush.setColor( QColor(255, 255, 255) );
               painter.setBrush(brush);
               painter.setPen(pen);
                for(int i =0;i<b_time;i++)
                {
                     if(painted[dfs_close[i]]) continue;
                    painter.drawEllipse(dv[dfs_close[i]], 20, 20);
                    painted[dfs_close[i]]=1;
                }
                QFont font("宋体", 20, QFont::Thin, true);
                painter.setFont(font);
                brush.setColor( QColor(255, 255, 255) );
                pen.setColor("black");
                painter.setBrush(brush);
                painter.setPen(pen);
                for(int i =0;i<n;i++)
                {
                    QPointF tmp(-15,10);
                    QString str;
                    if(p_mode==3)
                        str=QString::number(val[i],10);
                    else str=QString::number(i,10);
                     if(!painted[i]) painter.drawEllipse(dv[i], 20, 20);
                      painter.drawText(dv[i]+tmp,str);
                }
                font.setBold(1);
                painter.setFont(font);
                QString str=tr("步骤:")+QString::number(b_time,10)+"\\"+ QString::number(dfstime,10);
                painter.drawText(620,720,str);


        }
    else if(p_mode==4||p_mode==5)
            {
            painter.drawLine(250,250,250,550);
            painter.drawLine(350,250,350,550);
            painter.drawLine(450,250,450,550);
            painter.drawLine(550,250,550,550);
            painter.drawLine(250,250,550,250);
            painter.drawLine(250,350,550,350);
            painter.drawLine(250,450,550,450);
            painter.drawLine(250,550,550,550);
            vector<QPoint>vq;
            vq.push_back(QPoint(300,300));
            vq.push_back(QPoint(400,300));
            vq.push_back(QPoint(500,300));
            vq.push_back(QPoint(300,400));
            vq.push_back(QPoint(400,400));
            vq.push_back(QPoint(500,400));
            vq.push_back(QPoint(300,500));
            vq.push_back(QPoint(400,500));
            vq.push_back(QPoint(500,500));
            QFont font("宋体", 30, QFont::Bold, true);
            painter.setFont(font);

            ll tmpn;
            if(max_time==mp.size())
            {
                    tmpn=mp[astar_time];
            }
            else tmpn=astar_solv[astar_time];
            cout<<tmpn<<endl;
            for(int i =8;i>=0;i--)
            {
                if(tmpn%10==0) {tmpn/=10;continue;}
                QPointF tmp(-15,10);
                QString s=QString::number(tmpn%10,10);
                painter.drawText(vq[i]+tmp ,s);
                tmpn/=10;
            }
            font.setBold(1);
            painter.setFont(font);
            QString str=tr("步骤:")+QString::number(astar_time,10)+"\\"+ QString::number(max_time-1,10);
            painter.drawText(500,700,str);

        }
       else if(p_mode==6||p_mode==7)
        {

            for(int i =160;i<=640;i+=60)
                //for(int j =100;j<=640;j+=60)
                         painter.drawLine(i,160,i,640);
            for(int i =160;i<=640;i+=60)
                //for(int j =100;j<=640;j+=60)
                         painter.drawLine(160,i,640,i);

            vector<QPoint>vq[10];
            int x=160,y=160;
            for(int i =0;i<8;i++)
            {

                for(int j =0;j<8;j++)
                {

                    x+=60;
                    vq[i].push_back(QPoint(x-30,y+30));
                    //QString s=QString::number(i*8+j,10);
                    //painter.drawText(vq[i][j] ,s);
                }
                y+=60;
                x=160;
            }
            ll nowmap=cmp[cb_time];
            cout<<"nowmap"<<nowmap<<endl;
           brush.setColor("black");
           painter.setBrush(brush);
            for(int i =7;i>=0;i--)
            {
              painter.drawEllipse(vq[i][nowmap%10], 20, 20);
              nowmap/=10;
            }
             QFont font("宋体", 30, QFont::Bold, true);

            painter.setFont(font);
            QString str=tr("步骤:")+QString::number(cb_time,10)+"\\"+ QString::number(cmp.size()-1,10);
            painter.drawText(500,700,str);


        }
        else if(p_mode==8)
            {
                cout<<"p1"<<endl;
                int dis=480.0/(cs->n);
                for(int i =160;i<=640;i+=dis)
                    //for(int j =100;j<=640;j+=60)
                             painter.drawLine(i,160,i,640);
                for(int i =160;i<=640;i+=dis)
                    //for(int j =100;j<=640;j+=60)
                             painter.drawLine(160,i,640,i);
                vector<QPoint>vq;
                int x=160,y=160;
                for(int i =0;i<cs->n;i++)
                {

                    for(int j =0;j<cs->n;j++)
                    {

                        x+=dis;
                        vq.push_back(QPoint(x-dis/2,y+dis/2));
                         QString s=QString::number(i*cs->n+j,10);
                         painter.drawText(vq[i*cs->n+j] ,s);
                    }
                    y+=dis;
                    x=160;
                }
                brush.setColor("black");
                painter.setBrush(brush);
                for(int i =1;i<=cs->n;i++)
                    {
                    for(int j=1;j<=cs->n;j++)
                        if(ch[i][j]==-1)
                        {
                           // cout<<i<<" "<<j<<endl;
                              painter.drawEllipse(vq[(i-1)*cs->n+j-1], int(dis/2.5), int(dis/2.5));
                        }
                    }
                brush.setColor("white");
                painter.setBrush(brush);
                for(int i =1;i<=cs->n;i++)
                    {
                    for(int j=1;j<=cs->n;j++)
                        if(ch[i][j]==1)
                        {
                              painter.drawEllipse(vq[(i-1)*cs->n+j-1], int(dis/2.5), int(dis/2.5));
                        }
                    }
        }
    }
}


