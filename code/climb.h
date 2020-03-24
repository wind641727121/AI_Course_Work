#ifndef CLIMB_H
#define CLIMB_H

#include <QDialog>

namespace Ui {
class climb;
}

class climb : public QDialog
{
    Q_OBJECT

public:
    explicit climb(QWidget *parent = nullptr);
    ~climb();
    void randmap();
     bool cli();
     bool simulated();
     long long maptonum();
private slots:
     void on_rand_button_clicked();

     void on_next_button_clicked();

     void on_last_button_clicked();

     void on_next_button_2_clicked();

     void on_spinBox_valueChanged(int arg1);

     void on_spinBox_editingFinished();

     void on_next_button_3_clicked();

private:
    Ui::climb *ui;
};

#endif // CLIMB_H
