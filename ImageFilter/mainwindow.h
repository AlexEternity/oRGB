#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <graphicview.h>
#include <QToolBar>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QGraphicsView>
#include <QPixmap>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void signal1(QString f);
public slots:
    void on_button_clicked();
    void on_transform_clicked();
protected:
    void paintEvent(QPaintEvent *);


private:
    QList<GraphicView*> widgets;
    Ui::MainWindow *ui;
    double trMatrix[3][3] = {{0.2990,0.5870,0.1140},{0.5000,0.5000,-1.0000},{0.8660,-0.8660,0.0000}};
    double invMartix[3][3] = {{1.0000,0.1140,0.7436},{1.0000,0.1140,-0.4111},{1.0000,-0.8860,0.1663}};

};

#endif // MAINWINDOW_H
