#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dfslog.h"
#include "pboard.h"
#include "mainwindow.h"
#include "a_star.h"
#include "climb.h"
#include "chess.h"
using namespace  std;
int p_mode;
int can_paint;
dfslog * dl;
Pboard *pb;
MainWindow *w;
A_star *as;
climb *cb;
chess *cs;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1200,800);
    this->setFixedSize(1200,800);
    w=this;
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{

    cout<<item->text(column).toStdString()<<endl;
   // as->hide();
    //dl->hide();
    if(dl!=NULL) {delete dl;dl=NULL;}
    if(pb!=NULL) {delete pb;pb=NULL;}
    if(as!=NULL) {delete as;as=NULL;}
    if(cb!=NULL) {delete cb;cb=NULL;}
    if(cs!=NULL) {delete cs;cs=NULL;}
    if(item->parent()&&item->parent()->text(column)==tr("旅行问题"))
    {
        if(item->text(column)=="DFS")
        {
            cout<<1<<endl;
            p_mode=1;
            dl=new dfslog;
            cout<<2<<endl;
            dl->show();
             cout<<3<<endl;
        }
        else if(item->text(column)=="BFS")
        {
            p_mode=2;
            dl=new dfslog;
            cout<<2<<endl;
            dl->show();
        }
        else if(item->text(column)==tr("一致优先搜索"))
            {
            p_mode=3;
            dl=new dfslog;
            cout<<2<<endl;
            dl->show();
        }
        else can_paint=0;
    }
    else if(item->parent()&&item->parent()->text(column)==tr("八数码"))
        {
        if(item->text(column)=="BFS")
        {
            cout<<1<<endl;
            p_mode=4;
            as=new A_star;
            cout<<2<<endl;
            as->show();
            cout<<3<<endl;
        }
        else if(item->text(column)=="A*")
        {
            cout<<1<<endl;
            p_mode=5;
            as=new A_star;
            cout<<2<<endl;
            as->show();
            cout<<3<<endl;
        }
    }
    else if(item->parent()&&item->parent()->text(column)==tr("八皇后"))
        {
        if(item->text(column)=="爬山法")
        {
            cout<<1<<endl;
            p_mode=6;
            cb=new climb;
            cout<<2<<endl;
            cb->show();
            cout<<3<<endl;

        }
        else if(item->text(column)=="模拟退火")
        {
            cout<<1<<endl;
            p_mode=7;
            cb=new climb;
            cout<<2<<endl;
            cb->show();
            cout<<3<<endl;
        }
        }
    else if(item->parent()&&item->parent()->text(column)==tr("一字棋"))
        {
        if(item->text(column)=="Alpha-Beta剪枝")
        {
            cout<<1<<endl;
            p_mode=8;
            cs=new chess;
            cout<<2<<endl;
            cs->show();
            cout<<3<<endl;

        }
    }

    else {
        can_paint=0;
    }
    cout<<"ok"<<endl;
}
