#include "mainwindow.h"
#include <QApplication>
#include<bits/stdc++.h>
#include<qpainter.h>
#include<dfslog.h>
#include<pboard.h>
using namespace  std;
int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("人工智能算法可视化 计1708陈嘉尊");
    w.show();

    return a.exec();
}
