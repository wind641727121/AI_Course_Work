#ifndef DFSLOG_H
#define DFSLOG_H

#include <QDialog>
#include<bits/stdc++.h>
#include<qpainter.h>
#include<QVector>
namespace Ui {
class dfslog;
}
using namespace std;
const int MAXN=15;

class dfslog : public QDialog
{
    Q_OBJECT
public:
    explicit dfslog(QWidget *parent = nullptr);
    ~dfslog();
    void rand_map();
    void dfs(int s,int r);
    void bfs(int s,int r);
    bool is_circle();
    void pri_bfs(int s,int r);
private slots:

    void on_next_Button_clicked();

    void on_rand_Button_clicked();

    void on_check_circle_stateChanged(int arg1);

    void on_pushButton_3_clicked();



    void on_last_Button_clicked();

private:
    Ui::dfslog *ui;
};

#endif // DFSLOG_H
