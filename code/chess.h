#ifndef CHESS_H
#define CHESS_H

#include <QDialog>

namespace Ui {
class chess;
}

class chess : public QDialog
{
    Q_OBJECT

public:
    explicit chess(QWidget *parent = nullptr);
    ~chess();
    int check(int flag);
    int n,m,maxh;
    int alpha_beta(int h, int player, int alpha, int beta);
    int evaluate(int player);
private slots:
    void on_groupBox_toggled(bool arg1);

    void on_radio3_toggled(bool checked);

    void on_radio4_toggled(bool checked);

    void on_radio5_toggled(bool checked);

    void on_radio6_toggled(bool checked);

    void on_radio7_toggled(bool checked);

    void on_radio8_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radio8_clicked();

    void on_radio7_clicked();

    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_5_toggled(bool checked);

    void on_radioButton_6_toggled(bool checked);

    void on_pushButton_clicked();

    void on_okbutton_clicked();

private:
    Ui::chess *ui;
};

#endif // CHESS_H
