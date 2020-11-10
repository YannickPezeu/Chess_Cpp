#include "game.h"

Board* m_board;
int size_of_board=1000;
Game::Game()
{
    // Add the scene
    m_scene = new QGraphicsScene();

    // create board item

    m_board = new Board();
    //m_board->setPos(100,100);

    //computer play



    //set the scene
    setScene(m_scene);
    setFixedSize(size_of_board,size_of_board);

    //add the pieces and board


    m_scene->addItem(m_board);
    m_board->addPiecestoScene(m_board->m_pieces);

    m_scene->setSceneRect(0,0,1000,1000);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}

/*void Game::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen paintpen(Qt::black);
    paintpen.setWidth(6);
    painter.drawLine(10,10,200,200);
}*/

