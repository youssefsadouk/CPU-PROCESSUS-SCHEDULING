#include "sub_window.h"
#include "ui_sub_window.h"
#include"mainwindow.h"
#include<QMessageBox>
#include<windows.h>

#include <QElapsedTimer>
#include<QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>

extern int ch;
extern int num;
extern process p[10],p1[10],temp;
extern queue<int>q1;
int time_slice;
int condition=0;
//const int Dpi=100;
//int Slider_Value;
sub_window::sub_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sub_window)
{
    ui->setupUi(this);

    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //scene->setSceneRect(0,0,200,100);
    QStringList header;
    header<<"ID"<<"Arrival Time"<<"Burst Time"<<"Priority"<<"Color";
    ui->tableWidget->setRowCount(num);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:green;}");
    ui->lineEdit_timeslice->setPlaceholderText("Input time slice...");
    //ui->tableWidget->horizontalHeader()->resizeSection(5,220);
    \
    //    int ItemCount=1;
    //    for(int i=0;i<ItemCount;i++)
    //    {
    //        MyItem* item=new MyItem();
    //        scene->addItem(item);
    //    }

    //    timer=new QTimer(this);
    //    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    //    timer->start(1000);
}

void sub_window::shortest_job_sort(int n)
{
    int i, j;
    for (i = 2; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            if (p[j].at > p[i].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
            else if (p[j].at == p[i].at)
            {
                if (p[j].bt > p[i].bt)
                {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
    }
}

void sub_window::displayturnwait(int n)
{
    int i;
    int j;
    for(i=1;i<=num;i++)
    {
        p[i].tat=p[i].ft-p1[i].at;
        p[i].wt=p[i].tat-p1[i].bt;
        p[0].tat=p[0].tat+p[i].tat;
        p[0].wt=p[0].wt+p[i].wt;
    }

    p[0].tat=p[0].tat/n;
    p[0].wt=p[0].wt/n;



    QStringList header;
    header<<"ID"<<"Finish Time"<<"Turnaround Time"<<"Waiting Time";
    ui->tableWidget_Result->setRowCount(num);
    ui->tableWidget_Result->setColumnCount(4);
    ui->tableWidget_Result->setHorizontalHeaderLabels(header);
    ui->tableWidget_Result->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->verticalHeader()->setStyleSheet("QHeaderView::section{background:green;}");
    ui->tableWidget_Result->horizontalHeader()->resizeSection(2,150);


    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {

        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].id);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,0,item);
    }

    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {

        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].ft);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,1,item);
    }

    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].tat);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,2,item);
    }

    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].wt);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,3,item);
    }
}

sub_window::~sub_window()
{
    delete ui;
}

void sub_window::on_pushButton_clicked()
{


    int temp_data[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];

    QString tableData[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            tableData[i][j]=ui->tableWidget->item(i,j)->text();
        }
    }

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount()-1;j++)
        {
            temp_data[i][j]=tableData[i][j].toInt();
        }
    }

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        p[i+1].id=temp_data[i][0];
    }

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        p[i+1].at=temp_data[i][1];
    }

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        p[i+1].bt=temp_data[i][2];
    }

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        p[i+1].pr=temp_data[i][3];
    }

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        p[i+1].color=tableData[i][4];
    }


    QString text_tempa=ui->lineEdit_timeslice->text();
    time_slice=text_tempa.toInt();

    if(time_slice==0)
    {
        QMessageBox::warning(this,"Warning","Please Input The Time Slice!!!");
    }
    else
    {
        condition+=1;
    }

    //    ui->horizontalSlider_Speed->setRange(1,100);
    //    int Slider_Value=ui->horizontalSlider_Speed->value();
    //    Slider_Value=Slider_Value/Dpi;


    // QString str=QString::number(p[2].pr);

    // QMessageBox::information(this,"temp",p[2].color);

}

void sub_window::on_pushButton_2_clicked()
{
    if(ui->radioButton_Sub_FCFS->isChecked())
    {
        ch=1;
        condition+=1;
    }
    else if(ui->radioButton_Sub_NSJF->isChecked())
    {
        ch=2;
        condition+=1;
    }
    else if(ui->radioButton_Sub_PSJF->isChecked())
    {
        ch=3;
        condition+=1;
    }
    else if(ui->radioButton_Sub_RR->isChecked())
    {
        ch=4;
        condition+=1;
    }
    else if(ui->radioButton_Sub_PR->isChecked())
    {
        ch=5;
        condition+=1;
    }
    else
    {
        QMessageBox::warning(this,"Warning","Please select an algorithm!");
    }

    if(condition>=2){
        if(ch==1)
        {


            int i;
            for(i=1;i<=num;i++)
            {
                p1[i]=p[i];
            }
            p[1].st = p[1].at;
            for (i = 2; i <= num; i++)
            {
                p[i].st = p[i - 1].st + p[i - 1].bt;

            }

            p[1].ft=p[1].bt;

            for(i=2;i<=num;i++)
            {
                p[i].ft=p[i-1].ft+p[i].bt;
            }


            QBrush color_brush(QColor(p[1].color));
            QPen blackpen(Qt::black);
            blackpen.setWidth(1);
            QElapsedTimer t;
            t.start();
            //QGraphicsRectItem *rectangle=new QGraphicsRectItem();
            rectangle=scene->addRect(-200,0,Rectangle_Width*p[1].bt,Rectangle_Height,blackpen,color_brush);

            QGraphicsTextItem *txtitem = new QGraphicsTextItem("0");
            txtitem->setPos(QPointF(-200, 100));
            scene->addItem(txtitem);


            while(t.elapsed() < 2500)
            {
                QCoreApplication::processEvents();
            }
            for(i=2;i<=num;i++)
            {
                QBrush color_brush(QColor(p[i].color));
                QPen blackpen(Qt::black);
                blackpen.setWidth(1);
                rectangle=scene->addRect(-200+Rectangle_Width*p[i-1].ft,0,Rectangle_Width*p[i].bt,Rectangle_Height,blackpen,color_brush);
                QString temp_str=QString::number(p[i-1].ft);
                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                txtitem->setPos(QPointF(-200+Rectangle_Width*p[i-1].ft, 100));
                scene->addItem(txtitem);
                //text=scene->addText();
                QElapsedTimer t;
                t.start();
                while(t.elapsed() < 2500)
                {
                    QCoreApplication::processEvents();
                }

            }

            QString temp_str=QString::number(p[num].ft);
            QGraphicsTextItem *txtitema = new QGraphicsTextItem(temp_str);
            txtitema->setPos(QPointF(-200+Rectangle_Width*p[num].ft, 100));
            scene->addItem(txtitema);

            condition=0;


            displayturnwait(num);
            QMessageBox::information(this,"Succeed","Simulation Completed!");
        }

        if(ch==2)
        {

            //shortest_job_sort(num);
            int i,limit,nextval,m,min,pre_min;
            p[0].wt=p[0].tat=0;
            limit=p[1].at;

            for(i=1;i<=num;i++)
            {
                limit+=p[i].bt;
            }

            for(i=1;i<=num;i++)
            {
                p1[i]=p[i];
            }

            nextval=p[1].at;
            m=1;
            pre_min=1;
            //p[1].ft=p[1].bt;
            //        QBrush color_brush(QColor(p[m].color));
            //        QPen blackpen(Qt::black);
            //        blackpen.setWidth(1);
            //        rectangle=scene->addRect(-200,0,Rectangle_Width*p[1].bt,Rectangle_Height,blackpen,color_brush);
            //        QGraphicsTextItem *txtitem = new QGraphicsTextItem("0");
            //        txtitem->setPos(QPointF(-200, 100));
            //        scene->addItem(txtitem);
            //        //p[1].bt=0;
            QElapsedTimer t;
            t.start();
            while(t.elapsed() < 2500)
            {
                QCoreApplication::processEvents();
            }

            do
            {
                min=9999;
                for(i=1;p[i].at<=nextval&&i<=num;i++)
                {
                    if(p[i].bt<min && p[i].bt>0)
                    {
                        m=i;
                        min=p[i].bt;
                    }
                }
                nextval+=p[m].bt;
                QBrush color_brush(QColor(p[m].color));
                QPen blackpen(Qt::black);
                blackpen.setWidth(1);
                rectangle=scene->addRect(-200+Rectangle_Width*p[pre_min].ft,0,Rectangle_Width*p[m].bt,Rectangle_Height,blackpen,color_brush);
                QString temp_str=QString::number(p[pre_min].ft);
                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                txtitem->setPos(QPointF(-200+Rectangle_Width*p[pre_min].ft, 100));
                scene->addItem(txtitem);
                p[m].bt=0;
                if (p[m].bt == 0)
                {
                    p[m].ft = nextval;
                    p[m].tat = p[m].ft - p[m].at;
                    p[m].wt = p[m].tat - p1[m].bt;
                    p[0].tat += p[m].tat;
                    p[0].wt += p[m].wt;
                }
                //pre_min=m;

                pre_min=m;

                QElapsedTimer t;
                t.start();
                while(t.elapsed() < 2500)
                {
                    QCoreApplication::processEvents();
                }

                //           QBrush color_brush(QColor(p[m].color));
                //           QPen blackpen(Qt::black);
                //           blackpen.setWidth(1);
                //           rectangle=scene->addRect(-200+Rectangle_Width*p[pre_min].ft,0,Rectangle_Width*p[m].bt,Rectangle_Height,blackpen,color_brush);
                //           QString temp_str=QString::number(p[pre_min].ft);
                //           QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                //           txtitem->setPos(QPointF(-200+Rectangle_Width*p[pre_min].ft, 100));
                //           scene->addItem(txtitem);
                //           pre_min=m;

                //           QElapsedTimer t;
                //           t.start();
                //           while(t.elapsed() < 2500)
                //           {
                //             QCoreApplication::processEvents();
                //           }

            }while(nextval<limit);

            QString temp_str=QString::number(p[m].ft);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200+Rectangle_Width*p[m].ft, 100));
            scene->addItem(txtitem);
            condition=0;

            displayturnwait(num);
            QMessageBox::information(this,"Succeed","Simulation Completed!");
        }


        if(ch==3)
        {

            shortest_job_sort(num);
            int i,limit,nextval,m,min;
            p[0].wt=p[0].tat=0;

            limit=p[1].at;
            for(i=1;i<=num;i++)
            {
                limit+=p[i].bt;
            }

            for(i=1;i<=num;i++)
            {
                p1[i]=p[i];
            }

            nextval=p[1].at;
            m=1;
            //pre_min=1;
            QString temp_str=QString::number(p[1].at);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200,100));
            scene->addItem(txtitem);

            do{
                min=9999;
                for(i=1;p[i].at<=nextval && i<=num;i++)
                {
                    if(p[i].bt<min && p[i].bt>0)
                    {
                        m=i;
                        min=p[i].bt;
                    }
                }
                nextval+=1;
                p[m].bt=p[m].bt-1;
                QBrush color_brush(QColor(p[m].color));
                QPen blackpen(Qt::black);
                blackpen.setWidth(1);
                rectangle=scene->addRect(-200+Rectangle_Width*nextval,0,Rectangle_Width,Rectangle_Height,blackpen,color_brush);
                QString temp_str=QString::number(nextval);
                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                txtitem->setPos(QPointF(-200+Rectangle_Width*nextval+1, 100));
                scene->addItem(txtitem);
                QElapsedTimer t;
                t.start();
                while(t.elapsed() < 2500)
                {
                    QCoreApplication::processEvents();
                }

                //pre_min=m;
                if (p[m].bt == 0)
                {
                    p[m].ft = nextval;
                    p[m].tat = p[m].ft - p[m].at;
                    p[m].wt = p[m].tat - p1[m].bt;
                    p[0].tat += p[m].tat;
                    p[0].wt += p[m].wt;
                }
                //pre_min=m;
            }while(nextval<limit);

            condition=0;

            displayturnwait(num);
            QMessageBox::information(this,"Succeed","Simulation Completed!");
        }
        if(ch==4)
        {

            int i,m,nextval,nextarr;
            for(i=1;i<=num;i++)
            {
                p1[i]=p[i];
            }
            nextval=p[1].at;
            for(i=1;i<=num,p[i].at<=nextval;i++)
            {
                q1.push(p[i].id);
            }
            nextarr=p[1].at;
            //p[1].ft=p[1].bt;
            while(!q1.empty())
            {
                m=q1.front();
                q1.pop();
                if(p[m].bt>=time_slice)
                {
                    QBrush color_brush(QColor(p[m].color));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle=scene->addRect(-200+Rectangle_Width*nextval,0,Rectangle_Width*time_slice,Rectangle_Height,blackpen,color_brush);
                    QString temp_str=QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF(-200+Rectangle_Width*nextval, 100));
                    scene->addItem(txtitem);

                    nextval=nextval+time_slice;
                }
                else
                {
                    QBrush color_brush(QColor(p[m].color));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle=scene->addRect(-200+Rectangle_Width*nextval,0,Rectangle_Width*p[m].bt,Rectangle_Height,blackpen,color_brush);
                    QString temp_str=QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF(-200+Rectangle_Width*nextval, 100));
                    scene->addItem(txtitem);

                    nextval=nextval+p[m].bt;
                }



                p[m].bt=p[m].bt-time_slice;

                if (nextval < nextarr)
                {
                    if (p[m].bt>0)
                    {
                        q1.push(m);
                    }
                    if (p1[m].bt <= 0)
                    {
                        p[m].ft = nextval;
                    }
                }
                else
                {
                    while (i <= num&&p1[i].at <= nextval)
                    {
                        q1.push(p[i].id);
                        i++;
                    }
                    if (i <= num)
                        nextarr = p[i].at;
                    if (p[m].bt>0)
                        q1.push(m);
                    if (p[m].bt <= 0)
                        p[m].ft = nextval;
                }
                QElapsedTimer t;
                t.start();
                while(t.elapsed() < 2500)
                {
                    QCoreApplication::processEvents();
                }

            }
            QString temp_str=QString::number(nextval);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200+Rectangle_Width*nextval, 100));
            scene->addItem(txtitem);

            condition=0;

            displayturnwait(num);
            QMessageBox::information(this,"Succeed","Simulation Completed!");
        }
        if(ch==5)
        {
            int i,j,nextval;
            for(i=1;i<=num;i++)
            {
                for(j=i;j<=num;j++)
                {
                    if(p[i].pr>p[j].pr)
                    {
                        temp=p[j];
                        p[j]=p[i];
                        p[i]=temp;
                    }
                    if ((p[i].pr == p[j].pr))
                    {
                        if (p[i].at > p[j].at)
                        {
                            temp = p[j];
                            p[j] = p[i];
                            p[i] = temp;
                        }
                    }
                }
            }

            for(i=1;i<=num;i++)
            {
                p1[i]=p[i];
            }

            nextval=p[1].at;
            p[1].ft=p[1].bt;

            for(i=1;i<=num ;i++)
            {
                //nextval=nextval+p1[i].bt;

                // shortest_job_sort(num);
                QBrush color_brush(QColor(p[i].color));
                QPen blackpen(Qt::black);
                blackpen.setWidth(1);
                rectangle=scene->addRect(-200+(Rectangle_Width*nextval),0,Rectangle_Width*p[i].bt,Rectangle_Height,blackpen,color_brush);
                QString temp_str=QString::number(nextval);
                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                txtitem->setPos(QPointF((-200+Rectangle_Width*nextval), 100));
                scene->addItem(txtitem);

                nextval=nextval+p[i].bt;
                p[i].ft=nextval;

                //                QElapsedTimer t;
                //                t.start();
                //                while(t.elapsed() < 2500)
                //                {
                //                    QCoreApplication::processEvents();
                //                }

                QElapsedTimer t;
                t.start();
                while(t.elapsed() < 2500)
                {
                    QCoreApplication::processEvents();
                }

            }
            QString temp_str=QString::number(nextval);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200+Rectangle_Width*nextval, 100));
            scene->addItem(txtitem);
            condition=0;

            displayturnwait(num);
            QMessageBox::information(this,"Succeed","Simulation Completed!");
        }
    }
    else
    {
        QMessageBox::warning(this,"Warning","Check your data!");
    }
}

void sub_window::on_pushButton_4_clicked()
{
    scene->clear();
    for(int i=0;i<num;i++)
    {
        p[i].at=0;
        p[i].bt=0;
        p[i].color="";
        p[i].ft=0;
        p[i].id=0;
        p[i].pr=0;
        p[i].st=0;
        p[i].tat=0;
        p[i].wt=0;
    }

    QStringList header;
    header<<"ID"<<"Finish Time"<<"Turnaround Time"<<"Waiting Time";
    ui->tableWidget_Result->setRowCount(num);
    ui->tableWidget_Result->setColumnCount(4);
    ui->tableWidget_Result->setHorizontalHeaderLabels(header);
    ui->tableWidget_Result->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->verticalHeader()->setStyleSheet("QHeaderView::section{background:green;}");
    ui->tableWidget_Result->horizontalHeader()->resizeSection(2,150);
}
