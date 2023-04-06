#ifndef SUB_WINDOW_H
#define SUB_WINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include<QGraphicsScene>
const int Rectangle_Width=20;
const int Rectangle_Height=100;
//extern int ch;
//extern int num;
//extern process p[10],p1[10],temp;

namespace Ui {
class sub_window;
}

class sub_window : public QDialog
{
    Q_OBJECT

public:
    explicit sub_window(QWidget *parent = 0);
    void shortest_job_sort(int n);
    void displayturnwait(int n);
    ~sub_window();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::sub_window *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    //QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;

};

#endif // SUB_WINDOW_H
