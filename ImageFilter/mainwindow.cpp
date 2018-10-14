#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRgb>
#include <QColor>
#include <QtMath>
using namespace std;
double alphaList[9] = { 4.2f, 3.7f, 3.2f, 2.7f, 0,2.2f, 1.7f, 1.2f, 0.7f };
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(482,785);
    ui->setupUi(this);
    QToolBar *bFile=new QToolBar();
            QAction *OpenFile = bFile->addAction("OpenFile");
            QAction *Transform = bFile->addAction("Transform");
            bFile->setFixedSize(this->width(),20);
            bFile->setMovable(false);

            connect(OpenFile, SIGNAL(triggered()), SLOT(on_button_clicked()));
            connect(Transform, SIGNAL(triggered()), SLOT(on_transform_clicked()));
        addToolBar(Qt::TopToolBarArea, bFile);
    int x = 50;
    int y = 50;
    for(int i = 0; i < 9; i++)
    {
        if(i % 3 == 0 && i > 0)
        {
            x = 50;
            y += 250;
            widgets.push_back(new GraphicView(this,x,y));
            x += 150;
        }
        else
        {
            widgets.push_back(new GraphicView(this,x,y));
            x += 150;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_clicked()
{
    GraphicView* example = widgets.at(4);
    example->Om = false;
        example->oFile = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "", "*.bmp *.jpg *.png");
        if (example->oFile.isNull())
        {
            return;
        }

    if(example->Om == false)
    {
        example->Om = true;
        update();
    }
    example->image.load(example->oFile,NULL);
    example->image = example->image.scaled(100,200);
}

void MainWindow::on_transform_clicked()
{
    GraphicView *example = widgets.at(4);
    for(int i = 0; i < 9; i++)
    {
        if(i == 4)
            continue;
        GraphicView *widget = widgets.at(i);
        widget->image = example->image.copy();
        for(int j = 0; j < widget->image.height(); j++)
        {
            for(int k = 0; k < widget->image.width(); ++k)
            {
                QColor *p = new QColor(widget->image.pixel(k,j));
                double lc1c2[3];
                //Convert to LCC
                lc1c2[0] = trMatrix[0][0]*p->red() + trMatrix[0][1]*p->green() + trMatrix[0][2]*p->blue();
                lc1c2[1] = trMatrix[1][0]*p->red() + trMatrix[1][1]*p->green() + trMatrix[1][2]*p->blue();
                lc1c2[2] = trMatrix[2][0]*p->red() + trMatrix[2][1]*p->green() + trMatrix[2][2]*p->blue();
                double q = atan2(lc1c2[2],lc1c2[1]);
                double q0 = 0;
                //Convert to oRGB
                if(q < M_PI/3)
                {
                    q0 = (3/2)* q;
                }
                else
                {
                    q0 = (M_PI/2) + (3/4)*(q - M_PI/3);
                }
                double rq = q0 - q;
                double C[2];
                C[0] = lc1c2[1]*cos(rq) - lc1c2[2]*sin(rq);
                C[1] = lc1c2[2]*cos(rq) + lc1c2[1]*sin(rq);
                //change components by alpha
                C[0] *=alphaList[i];
                C[1] *=alphaList[i];
                //Convert back to LCC
                if(q0 < M_PI/2)
                {
                    q = (2/3)*q0;
                }
                else
                {
                    q = (M_PI/3)+(4/3)*(q0 - M_PI/2);
                }
                rq = q - q0;
                C[0] = C[0]*cos(rq) - C[1]*sin(rq);
                C[1] = C[1]*cos(rq) + C[0]*sin(rq);
                //Convert back to RGB
                double rgb[3];
                rgb[0] = invMartix[0][0]*lc1c2[0] + invMartix[0][1]*C[0] + invMartix[0][2]*C[1];
                rgb[1] = invMartix[1][0]*lc1c2[0] + invMartix[1][1]*C[0] + invMartix[1][2]*C[1];
                rgb[2] = invMartix[2][0]*lc1c2[0] + invMartix[2][1]*C[0] + invMartix[2][2]*C[1];

                widget->image.setPixelColor(k,j,QColor(rgb[0],rgb[1],rgb[2]));
                }

            }
        QPixmap map = QPixmap::fromImage(widget->image);
        widget->scene->addPixmap(map);
        widget->scene->update();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(widgets.count() > 4)
    {
   GraphicView* example = widgets.at(4);
   if(widgets.at(4) != nullptr && example->oFile != nullptr)
   {
        QPixmap map = QPixmap::fromImage(example->image);
        example->scene->addPixmap(map);
        example->scene->update();
   }
    }

}
