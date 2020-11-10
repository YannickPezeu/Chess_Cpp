#ifndef PIECES_H
#define PIECES_H
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QMouseEvent>
//#include "board.h"

class Board;

class Pieces: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Pieces();


    //Board* m_board;

    QSize getQ_size() const;
    void setQ_size(const QSize &value);
    int getColor() const;
    void setColor(int color);



public slots:
    void move(int row_dest, int col_dest);
    void move(int number_position);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) ;

protected:
    int m_size;
    QSize q_size;
    int m_position[2];
    int m_color;
    QPixmap m_pixmap;

};

class Bishop: public Pieces
{
    Q_OBJECT
public:
    Bishop(int color);

private:
    //int m_size=100;
};

class Bishop_promotion: public Pieces
{
    Q_OBJECT
public:
    Bishop_promotion(int color);

private:
    //int m_size=100;
};

class Knight: public Pieces
{
public:
    Knight(int color);

private:
};

class Knight_promotion: public Pieces
{
public:
    Knight_promotion(int color);

private:
};

class Pawn: public Pieces
{
public:
    Pawn(int color);

private:
};

class Rook: public Pieces
{
public:
    Rook(int color);

private:
};

class Rook_promotion: public Pieces
{
public:
    Rook_promotion(int color);

private:
};

class King: public Pieces
{
public:
    King(int color);

private:
};

class Queen: public Pieces
{
public:
    Queen(int color);

private:
};

class Queen_promotion: public Pieces
{
public:
    Queen_promotion(int color);

private:
};



#endif // PIECES_H
