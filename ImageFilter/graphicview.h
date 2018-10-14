#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H

#include <QGraphicsView>



class GraphicView : public QGraphicsView
{
    Q_OBJECT
    public:
        explicit GraphicView(QWidget *parent = 0,int x = 0,int y = 0);
        ~GraphicView();
    bool Om;
    QString oFile;
    QGraphicsScene *scene;
    QImage image;
signals:

private slots:

};

#endif // GRAPHICVIEW_H
