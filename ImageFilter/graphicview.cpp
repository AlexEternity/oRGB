#include "graphicview.h"

GraphicView::GraphicView(QWidget *parent,int x, int y)
    :QGraphicsView(parent)
{
    this->setParent(parent);
    Om = false;
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::red);
    setAutoFillBackground(true);
    setPalette(Pal);
    move(x,y);
    setFixedWidth(100);
    setFixedHeight(200);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(0,50,this->height(),this->width());
    show();
}

GraphicView::~GraphicView()
{

}
