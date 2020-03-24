#include "chess.h"
#include "ui_chess.h"
#include<bits/stdc++.h>
#include "mainwindow.h"
#include<QMessageBox>
#include <qvalidator.h>
using namespace std;
extern int p_mode;
extern Pboard *pb;
extern MainWindow *w;
extern chess *cs;
int chn,chm,chh;
chess::chess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chess)
{
    ui->setupUi(this);
    this->setParent(w);
     this->move(0,350);
     chn=3,chm=3,chh=2;
     ui->okbutton->setEnabled(0);
     //ui->next_button->setEnabled(0);
}

chess::~chess()
{
    delete ui;
}
int ch[25][25];
int my;
int chess::check(int flag) //自己1 别人是-1
{
   // cout<<"flag"<<flag<<endl;
    int i, j;
 //   for(int i=1;i<=n;i++)
  //      {
 //       for(int j=1;j<=n;j++)
  //          cout<<ch[i][j];
  //      cout<<endl;
 //   }
    for(i=1; i<=n; i++)
    {
        int w = 0, l = 0;
        int maxw=0,maxl=0;
        for(j=1; j<=n; j++)
        {
            if(ch[i][j] == flag)
            {
                w++;
                l=0;
                maxw=max(maxw,w);
            }
            if(ch[i][j] == -flag)
            {
                w=0;
                l++;
                maxl=max(l,maxl);
            }
        }
      //  cout<<i<<" "<<maxw<<" "<<maxl<<endl;
        if(maxw>=m){
            return 1;
        }
        if(maxl>=m){
            return -1;
        }


    }
   // cout<<"1"<<endl;
    for(i=1; i<=n; i++)
    {
        int w = 0, l = 0;
        int maxw=0,maxl=0;
        for(j=1; j<=n; j++)
        {
            if(ch[j][i] == flag)
            {
                w++;
                l=0;
                maxw=max(maxw,w);
            }
            if(ch[j][i] == -flag)
            {
                w=0;
                l++;
                maxl=max(l,maxl);
            }
        }
    //    cout<<i<<" "<<maxw<<" "<<maxl<<endl;
        if(maxw>=m){
            return 1;
        }
        if(maxl>=m){
            return -1;
        }
    }

// cout<<"2"<<endl;
    for(i=1-n; i<=n-1; i++)
    {
        int w = 0, l = 0;
        int maxw=0,maxl=0;
        for(int j=1;j<=n;j++){
            if(i+j>=1&&i+j<=n) {
            if(ch[j][i+j] == flag)
            {
                w++;
                l=0;
                maxw=max(maxw,w);
            }
            if(ch[j][i+j] == -flag)
            {
                w=0;
                l++;
                maxl=max(l,maxl);
            }
            }
        }
     ///   cout<<i<<" "<<maxw<<" "<<maxl<<endl;
        if(maxw>=m){
            return 1;
        }
        if(maxl>=m){
            return -1;
        }
    }


// cout<<"3"<<endl;
    for(i=2; i<=n+n; i++)
    {
        int w = 0, l = 0;
        int maxw=0,maxl=0;
        for(int j =1;j<=n;j++)
        {
            if(i-j>=1&&i-j<=n) {
            if(ch[j][i-j] == flag)
            {
                w++;
                l=0;
                maxw=max(maxw,w);
            }
            if(ch[j][i-j] == -flag)
            {
                w=0;
                l++;
                maxl=max(l,maxl);
            }
            }
        }
    //    cout<<i<<" "<<maxw<<" "<<maxl<<endl;
        if(maxw>=m){
            return 1;
        }
        if(maxl>=m){
            return -1;
        }

    }
  //   cout<<"4"<<endl;
    return 0;
}
int chess::evaluate(int player)
{
    int x;
    if(player){
        x = 1;
    }
    else{
        x = -1;
    }

    int i, j;
    int ans = 0;
    for(i=1; i<=n; i++)
    {
        int w = 0, l = 0;
        int maxw=0,maxl=0;
        for(j=1; j<=n; j++)
        {
            if(ch[i][j] == x||ch[i][j] == 0)
            {
                w++;
                l=0;
                maxw=max(maxw,w);
                if(maxw==m){
                  ans++;
                  maxw=w=0;
                }
            }
            else w=0;
        }

    }
    cout<<ans<<endl;
    for(i=1; i<=n; i++)
    {
        int w = 0, l = 0;
        int maxw=0,maxl=0;
        for(j=1; j<=n; j++)
        {
            if(ch[j][i] == x||ch[j][i]==0)
            {
                w++;
                l=0;
                maxw=max(maxw,w);
                if(maxw>=m){
                  ans++;
                  maxw=w=0;
                }
            }
            else w=0;

        }

    }

    cout<<ans<<endl;
    for(i=1-n; i<=n-1; i++)
    {
        int w = 0, l = 0;
        int maxw=0,maxl=0;
        for(int j=1;j<=n;j++){
            if(i+j>=1&&i+j<=n) {
            if(ch[j][i+j] == x||ch[j][i+j]==0)
            {
                w++;
                l=0;
                maxw=max(maxw,w);
                if(maxw>=m){
                  ans++;
                  maxw=w=0;
                }
            }
            else w=0;

            }
        }

    }


    cout<<ans<<endl;
    for(i=2; i<=n+n; i++)
    {
        int w = 0, l = 0;
        int maxw=0,maxl=0;
        for(int j =1;j<=n;j++)
        {
            if(i-j>=1&&i-j<=n) {
            if(ch[j][i-j] == x||ch[j][i-j] == 0)
            {
                w++;
                l=0;
                maxw=max(maxw,w);
                if(maxw>=m){
                  ans++;
                  maxw=w=0;
                }
            }
            else w=0;

            }
        }


    }
    cout<<ans<<endl;
    return ans;
}
int ansx,ansy;
int chess::alpha_beta(int h, int player, int alpha, int beta)      //h搜索深度，player=1表示自己,player=0表示对手
{
    cout<<h<<" "<<player<<alpha<<" "<<beta<<endl;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
            cout<<ch[i][j]<<" ";
        cout<<endl;
    }
    int result=check(1);
    if(h==maxh || (result != 0))   //若到达深度 或是出现胜负
    {
        if(result != 0){        //若是胜负返回-inf 或+inf
            return result*1e8;
        }
        else{
            cout<<"evaluate"<<" "<<evaluate(1)<<" "<<evaluate(0)<<endl;
            return evaluate(1) - evaluate(0);   //否则返回此局面的评价值
        }
    }

    int i, j;
    if(player){//自己
        for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
        {
            if(ch[i][j] == 0)
            {
                ch[i][j] = 1;
                int ans = alpha_beta(h+1, player^1, alpha, beta);
                ch[i][j] = 0;
                if(ans > alpha){    //通过向上传递的子节点beta值修正alpha值
                    alpha = ans;
                    ansx = i;       //记录位置
                    ansy = j;
                }

                if(alpha >= beta)   //发生 alpha剪枝
                {
                    return alpha;
                }
            }
        }
        return alpha;
    }
    else{//对手
        for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
        {
            if(ch[i][j] == 0)
            {
                ch[i][j] = -1;
                int ans = alpha_beta(h+1, player^1, alpha, beta);
                ch[i][j] = 0;
                if(ans < beta){     //通过向上传递的子节点alpha值修正beta值
                    beta = ans;
                }
                if(alpha >= beta)   //发生 beta剪枝
                {
                    return beta;
                }
            }
        }
        return beta;
    }
}

void chess::on_groupBox_toggled(bool arg1)
{

}
void chess::on_radio3_toggled(bool checked)
{
    if(checked)
        chn=3;
}

void chess::on_radio4_toggled(bool checked)
{
    if(checked)
        chn=4;
}

void chess::on_radio5_toggled(bool checked)
{
    if(checked)
        chn=5;
}

void chess::on_radio6_toggled(bool checked)
{
    if(checked)
        chn=6;
}

void chess::on_radio7_toggled(bool checked)
{
    if(checked)
        chn=7;
}

void chess::on_radio8_toggled(bool checked)
{
    if(checked)
        chn=8;
}

void chess::on_radioButton_toggled(bool checked)
{
    if(checked)
        chm=3;
}

void chess::on_radioButton_3_toggled(bool checked)
{
    if(checked)
        chm=5;
}

void chess::on_radioButton_2_toggled(bool checked)
{
    if(checked)
        chm=4;
}

void chess::on_radio8_clicked()
{

}

void chess::on_radio7_clicked()
{

}

void chess::on_radioButton_4_toggled(bool checked)
{
    chh=2;
}

void chess::on_radioButton_5_toggled(bool checked)
{
    chh=3;
}


void chess::on_radioButton_6_toggled(bool checked)
{
    chh=4;
}
extern int can_paint;
void chess::on_pushButton_clicked()
{
   // ui->last_button->setEnabled(0);
    can_paint=1;
    n=chn;m=chm;maxh=chh;
    QString tmp=tr("棋盘大小:")+QString::number(n,10)+
                tr("\t\n胜利条件:")+QString::number(m,10)+
                tr("\t\n搜索深度:")+QString::number(maxh,10);
    QMessageBox::about(this,tr("设置成功"),tmp);
    memset(ch,0,sizeof ch);
    ui->okbutton->setEnabled(1);
    ui->lineEdit->clear();
    QRegExp regx("[0-9][0-9]");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit );
    ui->lineEdit->setValidator(validator);
    cout<<"c1"<<endl;
    if(ui->checkBox->checkState()==0)
        {
            alpha_beta(1, 1, -0x3f3f3f3f, 0x3f3f3f3f);
            ch[ansx][ansy]=1;
    }
    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
     cout<<"c2"<<endl;
    pb->show();
}

void chess::on_okbutton_clicked()
{
    QString s=ui->lineEdit->text();
    int ha=s.toInt();
    if(ha>=n*n)
        {
        QString tmp=tr("无效的输入,请重新输入");
        QMessageBox::about(this,tr("警告"),tmp);
        return;
    }
    int x=(ha)/n,y=ha%n;
    ++x,++y;
    if(ch[x][y]!=0)
    {
        QString tmp=tr("该位置已经有子了,请重新输入");
        QMessageBox::about(this,tr("警告"),tmp);
        return;
    }
    ch[x][y]=-1;
    int emtp=0;
    for(int i=1;i<=n;i++)
        for(int j =1;j<=n;j++)
        {
               if(ch[i][j]==0) ++emtp;
        }
    if(emtp==0)
    {
        QString tmp=tr("平局");
        QMessageBox::about(this,tr("很遗憾"),tmp);
         ui->okbutton->setEnabled(0);
         return ;
    }

    alpha_beta(1, 1, -0x3f3f3f3f, 0x3f3f3f3f);
    ch[ansx][ansy]=1;
    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
     cout<<"c2"<<endl;
    pb->show();
    int tmp=check(1);
    if(tmp==1)
    {
        QString tmp=tr("你输了");
        QMessageBox::about(this,tr("很遗憾"),tmp);
         ui->okbutton->setEnabled(0);
    }
    else if(tmp==-1)
    {
        QString tmp=tr("你赢了");
        QMessageBox::about(this,tr("恭喜"),tmp);
         ui->okbutton->setEnabled(0);
    }
    emtp=0;
        for(int i=1;i<=n;i++)
            for(int j =1;j<=n;j++)
            {
                   if(ch[i][j]==0) ++emtp;
            }
        if(emtp==0)
        {
            QString tmp=tr("平局");
            QMessageBox::about(this,tr("很遗憾"),tmp);
             ui->okbutton->setEnabled(0);
             return ;
        }


}

