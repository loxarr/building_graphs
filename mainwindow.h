#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    QPushButton *button;
    QLineEdit *lineEdit;
    QLineEdit *lineEditXMin;
    QLabel *Xmin;
    QLineEdit *lineEditXMax;
    QLabel *Xmax;
    QLineEdit *lineEditYMin;
    QLabel *Ymin;
    QLineEdit *lineEditYMax;
    QLabel *Ymax;
    //QLabel *label;
public slots:
     void buttonClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
