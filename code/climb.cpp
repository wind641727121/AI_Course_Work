#include "climb.h"
#include "ui_climb.h"
#include "dfslog.h"
#include "pboard.h"
#include "mainwindow.h"
#include<bits/stdc++.h>
#include<qmessagebox.h>
#include<qspinbox.h>
using namespace  std;
extern int p_mode;
extern Pboard *pb;
extern MainWindow *w;
climb::climb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::climb)
{
    ui->setupUi(this);
    this->setParent(w);
    this->move(0,350);
    ui->last_button->setEnabled(0);
    ui->next_button->setEnabled(0);
    ui->next_button_3->setEnabled(0);

}
typedef  long long ll;
climb::~climb()
{
    delete ui;
}
int queens[10][10];
int temp[10][10];
ll climb::maptonum()
{
    ll tmpn=0;
    for(int i =0;i<8;i++)
    {
        int j=0;
        for(j;j<8;j++) if(queens[i][j]) break;
        tmpn=tmpn*10+j;
    }
    return tmpn;
}
vector<ll> cmp;
void climb::randmap() {
    cmp.clear();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            queens[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++) {
        int num = rand() % 8;
        queens[i][num] = 1;
    }
    cmp.push_back(maptonum());
}


int findCollision(int row, int col) {
    int count = 0;
    temp[row][col] = 1;
    for (int k = 0; k < 64; k++) {
        if (temp[k/8][k%8] == 1) {
            for (int i = 0; i < 8; i++)
                if (i != k/8 && temp[i][k%8] == 1)
                    count++;
            for (int i = k/8, j = k%8; i < 8 && j < 8; i++, j++)
                if (i != k/8 && temp[i][j] == 1)
                    count++;
            for (int i = k/8, j = k%8; i >= 0 && j >= 0; i--, j--)
                if (i != k/8 && temp[i][j] == 1)
                    count++;
            for (int i = k/8, j = k%8; i < 8 && j >= 0; i++, j--)
                if (i != k/8 && temp[i][j] == 1)
                    count++;
            for (int i = k/8, j = k%8; i >= 0 && j < 8; i--, j++)
                if (i != k/8 && temp[i][j] == 1)
                    count++;
        }
    }
    temp[row][col] = 0;
    return count/2;
}

bool check(int h[8][8]) {
    for (int i = 0; i < 8; i++) {
        bool flag = false;
        for (int j = 0; j < 8; j++) {
            if (queens[i][j] == 1 && h[i][j] == 0) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return true;
}
int max_try=100;

bool climb::cli() {
    for (int trial = 0; trial <= max_try-1; trial++) {

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                temp[i][j] = queens[i][j];
            }
        }
        int h[8][8];
        int minH = 0x3f3f3f3f, minX = 0, minY = 0, curState;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 8; k++)
                    temp[i][k] = 0;
                // 查找h(i, j)
                h[i][j] = findCollision(i, j);
                // 当前状态的h值
                if (queens[i][j] == 1) {
                    curState = h[i][j];
                }
                // 先找出冲突个数最小的位置
                if (h[i][j] < minH) {
                    minH = h[i][j];
                    minX = i;
                    minY = j;
                }
                // 计算h(i,j)之后要复原数据，避免计算错误
                for (int k = 0; k < 8; k++)
                    temp[i][k] = queens[i][k];
            }
        }

        // 将皇后放在该行冲突最少的位置处
        if (curState > minH) {
            for (int i = 0; i < 8; i++)
                queens[minX][i] = 0;
            queens[minX][minY] = 1;
        }
        cmp.push_back(maptonum());
        // 判断是否找到解, 有解则返回值为真
        if (check(h)) {
            return true;
        }
    }
    return false;
}
bool climb::simulated() {
    double temperature = 5;
    int trial = 0;
    while (temperature > 0.00001) {

        // 拷贝原始棋盘数据到temp
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                temp[i][j] = queens[i][j];
            }
        }
        int h[8][8], curState;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                // 在计算h(i, j)之前，对i行所有位置赋值为0
                for (int k = 0; k < 8; k++)
                    temp[i][k] = 0;
                // 查找h(i, j)
                h[i][j] = findCollision(i, j);
                // 当前状态的h值
                if (queens[i][j] == 1) {
                    curState = h[i][j];
                }
                // 计算h(i,j)之后要复原数据，避免计算错误
                for (int k = 0; k < 8; k++)
                    temp[i][k] = queens[i][k];
            }
        }

        // 随机选取一个下一状态
        bool better = false;
        int next, nextState, times = 0;

        next = rand() % 64;
        nextState = h[next/8][next%8];
        int E = nextState - curState;
        if (E < 0) {
            better = true;
        } else if (exp((-1)*E/temperature) > ((double)(rand() % 1000) / 1000)) {
            better = true;
        }

        if (better) {
            for (int i = 0; i < 8; i++)
                queens[next/8][i] = 0;
            queens[next/8][next%8] = 1;  // 放置皇后
            trial++;
            cmp.push_back(maptonum());
            if(trial>max_try-1) break;
        }


        // 判断是否找到解, 有解则返回值为真
        if (check(h))
            return true;

        temperature *= 0.99;
    }
    return false;
}

extern int can_paint;
int cb_time;

void climb::on_rand_button_clicked()
{
    ui->last_button->setEnabled(0);
    can_paint=1;
    cb_time=0;
    int flag = 0;
     max_try=ui->spinBox->value();
    cout<<"x1"<<endl;
    randmap();
    cout<<"x2"<<endl;
    if(p_mode==6)
    {
        flag=cli();
    }
    else if(p_mode==7)
        {
        flag=simulated();
    }
    else return;
    if(flag==0)
    {
         QMessageBox::about(this,tr("搜索结果"),tr("限定次数内未找到最优解"));
    }
    else QMessageBox::about(this,tr("搜索结果"),tr("成功找到最优解"));

    cout<<"x3"<<endl;
    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
    pb->show();
    ui->next_button->setEnabled(1);
    ui->next_button_3->setEnabled(1);
}

void climb::on_next_button_clicked()
{
    ;
    if(cb_time>=cmp.size()-1)
    {
        QString tmp;

            tmp=tr("已到达最终状态\n");
        QMessageBox::about(this,tr("搜索结果"),tmp);
                ui->next_button->setEnabled(0);
        return ;
    }
    ++cb_time;
    can_paint=1;
    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
    pb->show();
    ui->last_button->setEnabled(1);
}

void climb::on_last_button_clicked()
{
    if(cb_time<=0)
    {

        QMessageBox::about(this,tr("搜索结果"),tr("不能后退了"));
         ui->last_button->setEnabled(0);

        return ;
    }
    --cb_time;
    can_paint=1;
    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
    pb->show();
     ui->next_button->setEnabled(1);
}

void climb::on_next_button_2_clicked()
{
    cb_time=cmp.size()-2;
    on_next_button_clicked();
}

void climb::on_spinBox_valueChanged(int arg1)
{

}

void climb::on_spinBox_editingFinished()
{

}

void climb::on_next_button_3_clicked()
{
    max_try=ui->spinBox->value();
    can_paint=1;
    cb_time=0;
    cout<<"last:"<<cmp[0]<<endl;
    memset(queens,0,sizeof queens);
    for(int i =7;i>=0;i--)
    {

        queens[i][cmp[0]%10]=1;
        cmp[0]/=10;
    }
    cmp.clear();
    cmp.push_back(maptonum());
    cout<<"now:"<<cmp[0]<<endl;
    int flag = 0;
    if(p_mode==6)
    {
        flag=cli();
    }
    else if(p_mode==7)
    {
        flag=simulated();
    }
    else return;
    if(flag==0)
    {
         QMessageBox::about(this,tr("搜索结果"),tr("限定次数内未找到最优解"));
    }
    else QMessageBox::about(this,tr("搜索结果"),tr("成功找到最优解"));

    cout<<"x3"<<endl;
    if(pb!=NULL) {delete pb;pb=NULL;}
    pb=new Pboard;
    pb->show();
    ui->next_button->setEnabled(1);
}
