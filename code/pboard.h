#ifndef PBOARD_H
#define PBOARD_H

#include <QWidget>
#include<QTreeWidget>
#include<bits/stdc++.h>
#include<qpainter.h>
namespace Ui {
class Pboard;
}
const int mid=400;
class Pboard : public QWidget
{
    Q_OBJECT

public:
    explicit Pboard(QWidget *parent = nullptr);
    ~Pboard();
private:
    Ui::Pboard *ui;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // PBOARD_H
