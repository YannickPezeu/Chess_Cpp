#include "pieces.h"
#include "board.h"
#include <QDebug>
#include "game.h"
extern int player_turn;
extern int size_of_board;
extern Board* m_board;
extern Game* game;

Pieces::Pieces()
{
    m_size = 0.1*size_of_board;
    q_size = QSize(m_size,m_size);
    setFlag(QGraphicsPixmapItem::ItemIsMovable);
    this->setTransformOriginPoint(m_size/2,m_size/2);
    this->setRotation(180);
}

/*int Pieces::size() const
{
    return m_size;
}

void Pieces::setSize(int size)
{
    m_size = size;
}*/

QSize Pieces::getQ_size() const
{
    return q_size;
}

void Pieces::setQ_size(const QSize &value)
{
    q_size = value;
}

int Pieces::getColor() const
{
    return m_color;
}

void Pieces::setColor(int color)
{
    m_color = color;
}

void Pieces::move(int row_dest, int col_dest)
{
    setPos((col_dest+1)*m_size,(row_dest+1)*m_size);

}

void Pieces::move(int number_position)
{
    int col_dest = number_position % 8;
    int row_dest = number_position / 8;
    setPos((col_dest+1)*m_size,(row_dest+1)*m_size);
}


void Pieces::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int int_promotion = 70;
    QGraphicsPixmapItem::mousePressEvent(event);
    int x0 =  x()+50;
    int y0 =  y()+50;
    int row = (y0-y0%100)/100-1;
    int col = (x0-x0%100)/100-1;
    m_board->setOrigin(8*row + col);
    m_board->setRow_origin(row);
    m_board->setCol_origin(col);
    setPos(x(),y());
}

void Pieces::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{

    int int_promotion= 70;

    //no promotion move

    if(m_board->m_position[int_promotion]=='0')
    {

        qDebug() << "m_position[int_promotion] = " << m_position[int_promotion];
        int x1 = x()+50;
        int y1 = y()+50;
        int row = (y1-y1%100)/100-1;
        int col = (x1-x1%100)/100-1;
        m_board->setDestination(8*row + col);


        m_board->setRow_destination(row);
        m_board->setCol_destination(col);

        int origin = m_board->getOrigin();
        int destination = m_board->getDestination();

        /*if(m_board->is_move_allowed_complete(m_board->m_position,origin, destination))
        {
            QGraphicsPixmapItem::mouseReleaseEvent(event);
            m_board->removePieces(m_board->m_pieces);
            m_board->setPosition(m_board->move_piece_with_test_complete(m_board->m_position, origin, destination));
            m_board->m_pieces = m_board->pieces_map(m_board->m_position);
            m_board->addPiecestoScene(m_board->m_pieces);
        }*/


        //Not King move nor Pawn move nor Rook move
        if(m_board->is_move_allowed_with_check(m_board->m_position,origin, destination) &&
                (m_board->m_position[origin]!='6' && m_board->m_position[origin]!='f')&&
                (m_board->m_position[origin]!='1' && m_board->m_position[origin]!='a')&&
                (m_board->m_position[origin]!='4' && m_board->m_position[origin]!='d'))
        {

            QGraphicsPixmapItem::mouseReleaseEvent(event);
            m_board->removePieces(m_board->m_pieces);
            m_board->setPosition(m_board->move_piece(m_board->m_position, origin, destination));
            m_board->m_pieces = m_board->pieces_map(m_board->m_position);
            m_board->addPiecestoScene(m_board->m_pieces);
        }
        //King move
        else if((m_board->is_move_allowed_with_check(m_board->m_position,origin, destination) ||m_board->is_castling_allowed(m_board->m_position,origin, destination)) &&
                (m_board->m_position[origin]=='6' || m_board->m_position[origin]=='f'))
        {
            QGraphicsPixmapItem::mouseReleaseEvent(event);
            m_board->removePieces(m_board->m_pieces);
            m_board->setPosition(m_board->move_king(m_board->m_position, origin, destination));
            m_board->m_pieces = m_board->pieces_map(m_board->m_position);
            m_board->addPiecestoScene(m_board->m_pieces);
        }
        //Rook move
        else if((m_board->is_move_allowed_with_check(m_board->m_position,origin, destination) ||m_board->is_castling_allowed(m_board->m_position,origin, destination)) &&
                (m_board->m_position[origin]=='4' || m_board->m_position[origin]=='d'))
        {
            QGraphicsPixmapItem::mouseReleaseEvent(event);
            m_board->removePieces(m_board->m_pieces);
            m_board->setPosition(m_board->move_rook(m_board->m_position, origin, destination));
            m_board->m_pieces = m_board->pieces_map(m_board->m_position);
            m_board->addPiecestoScene(m_board->m_pieces);
        }
        //Pawn move
        //Look en_passant and normal_move
        else if((m_board->is_move_allowed_with_check(m_board->m_position,origin, destination) ||
                 ((m_board->m_position[origin]=='1' || m_board->m_position[origin]=='a') &&
                   (m_board->is_en_passant_allowed(m_board->m_position,origin, destination)))))
        {
            //Look promotion
            if(destination/8 == 0 || destination/8 == 7)
            {

                QGraphicsPixmapItem::mouseReleaseEvent(event);
                m_board->removePieces(m_board->m_pieces);
                m_board->setPosition(m_board->move_pawn(m_board->m_position, origin, destination));
                m_board->m_pieces = m_board->pieces_map(m_board->m_position);
                m_board->addPiecestoScene(m_board->m_pieces);
                m_board->addWhiteRectangletoScene();
                qDebug()<< "test";
                m_board->addPiecestoScenePromotion(destination);
            }
            //No promotion
            else
            {
                QGraphicsPixmapItem::mouseReleaseEvent(event);
                m_board->removePieces(m_board->m_pieces);
                m_board->setPosition(m_board->move_pawn(m_board->m_position, origin, destination));
                m_board->m_pieces = m_board->pieces_map(m_board->m_position);
                m_board->addPiecestoScene(m_board->m_pieces);
            }


        }
        else
        {
            QGraphicsPixmapItem::mouseReleaseEvent(event);
            move(m_board->getRow_origin(),m_board->getCol_origin());
        }

    }
    // if position[int_promotion] == 1
    else
    {


        int origin = m_board->getOrigin();
        int destination = m_board->getDestination();

        if(origin == destination || origin == destination -8
                || origin == destination -16 || origin == destination -24)
        {
            QGraphicsPixmapItem::mouseReleaseEvent(event);
            m_board->removePieces(m_board->m_pieces);
            m_board->m_position[destination]=m_board->transform_piece_piecePromotion(m_board->m_promotion_pieces_position[origin]);
            m_board->m_pieces = m_board->pieces_map(m_board->m_position);
            m_board->addPiecestoScene(m_board->m_pieces);
            m_board->removeWhiteRectanglefromScene();
            m_board->removePiecesPromotion(m_board->m_pieces_promotion);
            m_board->m_position[int_promotion]='0';
            m_board->m_position = m_board->change_turn(m_board->m_position);
            m_board->clear_m_promotion_pieces_position();
            /*
            int x0 =  x()+50;
            int y0 =  y()+50;
            int row = (y0-y0%100)/100-1;
            int col = (x0-x0%100)/100-1;
            m_board->setOrigin(8*row + col);
            m_board->setRow_origin(row);
            m_board->setCol_origin(col);*/
        }
        else
        {
            QGraphicsPixmapItem::mouseReleaseEvent(event);
            move(m_board->getRow_origin(),m_board->getCol_origin());
        }



    }

    //Print next possibles positions to console
        /*std::vector<std::string> next_positions = m_board->next_allowed_positions(m_board->m_position);
        for(std::vector<std::string>::const_iterator position=next_positions.begin(); position!=next_positions.end(); position++)
        {
            m_board->print_board(*position);
        }*/

    //computer play


        int depth=4;


        if(m_board->m_position[m_board->int_player_turn]=='0')
        {
            m_board->removePieces(m_board->m_pieces);
            m_board->m_position = m_board->find_best_move_alpha_beta(m_board->m_position,depth);
            m_board->m_pieces = m_board->pieces_map(m_board->m_position);
            m_board->addPiecestoScene(m_board->m_pieces);
            m_board->print_board(m_board->m_position);
        }

}


Bishop::Bishop(int color)
{
    //m_size = 0.1*size_of_board;
    //QSize q_size = QSize(m_size,m_size);
    m_color = color;


    if(m_color == 1){
        m_pixmap = QPixmap(":images/white_bishop.png");
    }
    else
    {
        m_pixmap = QPixmap(":images/black_bishop.png");

    }
    m_pixmap = m_pixmap.scaled(q_size);
    setPixmap(m_pixmap);

    setPos(50,50);
}

Bishop_promotion::Bishop_promotion(int color)
{
    //m_size = 0.1*size_of_board;
    //QSize q_size = QSize(m_size,m_size);
    m_color = color;


    if(m_color == 1){
        m_pixmap = QPixmap(":images/white_bishop_circle.png");
    }
    else
    {
        m_pixmap = QPixmap(":images/black_bishop_circle.png");

    }
    m_pixmap = m_pixmap.scaled(q_size);
    setPixmap(m_pixmap);
    setPos(50,50);
}



Knight::Knight(int color)
{
    m_color = color;


    if(m_color == 1){
        m_pixmap = QPixmap(":images/white_knight.png");
    }
    else
    {
        m_pixmap = QPixmap(":images/black_knight.png");

    }
    m_pixmap = m_pixmap.scaled(q_size);
    setPixmap(m_pixmap);
    setPos(50,50);
}


Knight_promotion::Knight_promotion(int color)
{
    m_color = color;


    if(m_color == 1){
        m_pixmap = QPixmap(":images/white_knight_circle.png");
    }
    else
    {
        m_pixmap = QPixmap(":images/black_knight_circle.png");

    }
    m_pixmap = m_pixmap.scaled(q_size);
    setPixmap(m_pixmap);
    setPos(50,50);
}


Rook::Rook(int color)
{
    m_color = color;


    if(m_color == 1){
        m_pixmap = QPixmap(":images/white_rook.png");
    }
    else
    {
        m_pixmap = QPixmap(":images/black_rook.png");

    }
    m_pixmap = m_pixmap.scaled(q_size);
    setPixmap(m_pixmap);
    setPos(50,50);
}

Rook_promotion::Rook_promotion(int color)
{
    m_color = color;


    if(m_color == 1){
        m_pixmap = QPixmap(":images/white_rook_circle.png");
    }
    else
    {
        m_pixmap = QPixmap(":images/black_rook_circle.png");

    }
    m_pixmap = m_pixmap.scaled(q_size);
    setPixmap(m_pixmap);
    setPos(50,50);
}


Pawn::Pawn(int color)
{
    m_color = color;


    if(m_color == 1){
        m_pixmap = QPixmap(":images/white_pawn.png");
    }
    else
    {
        m_pixmap = QPixmap(":images/black_pawn.png");

    }
    m_pixmap = m_pixmap.scaled(q_size);
    setPixmap(m_pixmap);
    setPos(50,50);
}

Queen::Queen(int color)
{
    m_color = color;


    if(m_color == 1){
        m_pixmap = QPixmap(":images/white_queen.png");
    }
    else
    {
        m_pixmap = QPixmap(":images/black_queen.png");

    }
    m_pixmap = m_pixmap.scaled(q_size);
    setPixmap(m_pixmap);
    setPos(50,50);
}

Queen_promotion::Queen_promotion(int color)
{
    m_color = color;


    if(m_color == 1){
        m_pixmap = QPixmap(":images/white_queen_circle.png");
    }
    else
    {
        m_pixmap = QPixmap(":images/black_queen_circle.png");

    }
    m_pixmap = m_pixmap.scaled(q_size);
    setPixmap(m_pixmap);
    setPos(50,50);
}

King::King(int color)
{
    m_color = color;


    if(m_color == 1){
        m_pixmap = QPixmap(":images/white_king.png");
    }
    else
    {
        m_pixmap = QPixmap(":images/black_king.png");

    }
    m_pixmap = m_pixmap.scaled(q_size);
    setPixmap(m_pixmap);
    setPos(50,50);
}


