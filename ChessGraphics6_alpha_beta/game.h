#ifndef MASCENE_H
#define MASCENE_H
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include "board.h"
#include "pieces.h"
#include <QtGui>
#include <QtCore>


class Game: public QGraphicsView
{
public:
    Game();
    QGraphicsScene* m_scene;
    //Board* m_board;
   // void paintEvent(QPaintEvent *e);


    //void mouseReleaseEvent(QMouseEvent * event);


};

#endif // MASCENE_H
