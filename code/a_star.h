#ifndef A_STAR_H
#define A_STAR_H
#include<bits/stdc++.h>
#include <QDialog>
using namespace  std;
namespace Ui {
class A_star;
}

class A_star : public QDialog
{
    Q_OBJECT

public:

    explicit A_star(QWidget *parent = nullptr);
    ~A_star();
    void bfs();
    void a_star();
    void rand_map();

private slots:
    void on_rand_button_clicked();

    void on_last_button_clicked();

    void on_next_button_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_3_clicked();

private:
    Ui::A_star *ui;
};

#endif // A_STAR_H
