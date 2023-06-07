#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPushButton"
#include "QPixmap"
#include "cmath"
#include "poland.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    button = new QPushButton(this);
    button->setGeometry(width() * .85, 10, width() * .14, height() * 0.05);
    button->setText("Build graphic");
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    ui -> label -> setGeometry(10, 50, width()* 0.825, height()*0.9);
    lineEdit = new QLineEdit(this);
    lineEdit -> setGeometry(width() * .01, 10, width() * .25, height() * .05);

    Xmin = new QLabel(this);
    Xmin -> setGeometry(width() * .85, height() * .25, width() * .1, height() * 0.05);
    Xmin -> setText("x min");
    lineEditXMin = new QLineEdit(this);
    lineEditXMin -> setGeometry(width() * .85, height() * .3, width() * .1, height() * 0.05);

    Xmax = new QLabel(this);
    Xmax -> setGeometry(width() * .85, height() * .35, width() * .1, height() * 0.05);
    Xmax -> setText("x max");
    lineEditXMax = new QLineEdit(this);
    lineEditXMax -> setGeometry(width() * .85, height() * .4, width() * .1, height() * 0.05);

    Ymin = new QLabel(this);
    Ymin -> setGeometry(width() * .85, height() * .55, width() * .1, height() * 0.05);
    Ymin -> setText("y min");
    lineEditYMin = new QLineEdit(this);
    lineEditYMin -> setGeometry(width() * .85, height() * .6, width() * .1, height() * 0.05);

    Ymax = new QLabel(this);
    Ymax -> setGeometry(width() * .85, height() * .65, width() * .1, height() * 0.05);
    Ymax -> setText("y max");
    lineEditYMax = new QLineEdit(this);
    lineEditYMax -> setGeometry(width() * .85, height() * .7, width() * .1, height() * 0.05);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    /*
    QPainter painter;
    painter.begin(this);
    QPen pen;
    //pen.setColor(Qt::red);
    pen.setColor(0xff0000);
    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);

    painter.setPen(pen);
    painter.drawLine(0, 0, 100, 100);
    painter.end();
    */
}

void MainWindow::buttonClicked() {
    ui -> label -> setGeometry(10, 50, width()* 0.8, height()*0.9);
    button->setGeometry(width() * .85 - 10, 10, width() * .144, height() * 0.05);
    button->setText("Build graphic");
    lineEdit -> setGeometry(width() * .01, 10, width() * .25, height() * .05);

    Xmin -> setGeometry(width() * .85, height() * .25, width() * .1, height() * 0.05);
    lineEditXMin -> setGeometry(width() * .85, height() * .3, width() * .1, height() * 0.05);

    Xmax -> setGeometry(width() * .85, height() * .35, width() * .1, height() * 0.05);
    lineEditXMax -> setGeometry(width() * .85, height() * .4, width() * .1, height() * 0.05);

    Ymin -> setGeometry(width() * .85, height() * .55, width() * .1, height() * 0.05);
    lineEditYMin -> setGeometry(width() * .85, height() * .6, width() * .1, height() * 0.05);

    Ymax -> setGeometry(width() * .85, height() * .65, width() * .1, height() * 0.05);
    lineEditYMax -> setGeometry(width() * .85, height() * .7, width() * .1, height() * 0.05);

    QPixmap pm(width()* 0.8, height()*0.9);
    QPainter painter;
    painter.begin(&pm);
    pm.fill(Qt::white);
    QPainterPath path;
    QPen pen;
    double a = 5;
    double xmin, xmax;
    double ymin, ymax;
    if ((lineEditXMin -> text()).length() == 0 || (lineEditXMax -> text()).length() == 0 ||
            (lineEditYMin -> text()).length() == 0 || (lineEditYMax -> text()).length() == 0) {
        xmin = -a, xmax = a;
        ymin = -a, ymax = a;
    } else {
        xmin = (lineEditXMin -> text()).toDouble(), xmax = (lineEditXMax -> text()).toDouble();
        ymin = (lineEditYMin -> text()).toDouble(), ymax = (lineEditYMax -> text()).toDouble();
    }
    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();
    double x, y;
    int xg, yg;
    double kx = (xgmax - xgmin)/(xmax - xmin), ky = (ygmin - ygmax)/(ymax - ymin);
    double x0 = xgmin - kx * xmin, y0 = ygmin - ky * ymax;
    x = xmin;
    double stepx = (xmax - xmin)/(xgmax - xgmin);
    //stepx = 1e-3;

    pen.setColor(Qt::black);
    pen.setWidth(1);
    pen.setCapStyle(Qt::FlatCap);
    painter.setPen(pen);
    painter.drawLine(x0 - pm.width(), y0, x0 + pm.width(), y0);
    painter.drawLine(x0, y0 - pm.height(), x0, y0 + 2 * pm.height());

    QString sSample = lineEdit -> text();
    QString ss = QString::number(x);
    QString s = sSample;
    ss = '(' + ss;
    ss = ss + ')';
    s.replace("x", ss);
    double ans;
    calc(s.toStdString(), ans);
    y = ans;
    xg = int(x0 + kx * x);
    yg = int(y0 + ky * y);
    path.moveTo(xg, yg);
    int check = 0, checkm = 0;
    while (x <= xmax){
        s = sSample;
        ss = QString::number(x);
        ss = '(' + ss;
        ss = ss + ')';
        s.replace("x", ss);
        calc(s.toStdString(), ans);
        y = ans;
        xg = int(x0 + kx * x);
        yg = int(y0 + ky * y);
        if (abs(ans) < EPS) {
            check = 1;
            path.moveTo(xg, yg);
            x += stepx;
            // QString proof = QString::number(x) + ' '  + QString::number(ans);
            // ui -> listWidget -> addItem(proof);
            continue;
        }
        if ((ans > ymax || ans < ymin) && checkm == 0) {
            checkm = 1;
            path.lineTo(xg, yg);
            x += stepx;
            // QString proof = QString::number(x) + ' '  + QString::number(ans);
            // ui -> listWidget -> addItem(proof);
            continue;
        }
        if (check == 1) {
            path.moveTo(xg, yg);
            check = 0;
        }
        if ((ans > ymax || ans < ymin) && checkm == 1) {
            checkm = 0;
            path.moveTo(xg, yg);
            // QString proof = QString::number(x) + ' '  + QString::number(ans);
            // ui -> listWidget -> addItem(proof);
            continue;
        } else if (checkm == 1){
            checkm = 0;
        }

        path.lineTo(xg, yg);
        x += stepx;
        // QString proof = QString::number(x) + ' '  + QString::number(ans);
        // ui -> listWidget -> addItem(proof);
    }

    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPath(path);
    painter.end();
    ui -> label -> setPixmap(pm);
}
