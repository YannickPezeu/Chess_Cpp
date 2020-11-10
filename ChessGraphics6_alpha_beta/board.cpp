#include "board.h"
#include "game.h"

extern Game* game;
extern int size_of_board;
int count_positions_screened;
Board::Board()
{
    m_position = "";
    m_position += "42365324";
    m_position += "11111111";
    m_position += "00000000";
    m_position += "00000000";
    m_position += "00000000";
    m_position += "00000000";
    m_position += "aaaaaaaa";
    m_position += "dbcfecbd";
    m_position += "00000000";
    m_position[68] = '1'; //White to play
    m_promotion_pieces_position = "";
    for (int i=0; i<71;i++) m_promotion_pieces_position += '0';

    m_pieces =pieces_map(m_position);

    int_white_king_castle = 64;
    int_white_queen_castle = 65;
    int_black_king_castle = 66;
    int_black_queen_castle = 67;
    int_player_turn=68;
    int_en_passant=69;
    int_promotion = 70;
    //which_pawn_is_takable_en_passant='0';
    pieces_value['1']=10;
    pieces_value['2']=28;
    pieces_value['3']=30;
    pieces_value['4']=47;
    pieces_value['5']=90;
    pieces_value['6']=10000;
    pieces_value['a']=-10;
    pieces_value['b']=-28;
    pieces_value['c']=-30;
    pieces_value['d']=-47;
    pieces_value['e']=-90;
    pieces_value['f']=-10000;
    pieces_value['0']=0;




    m_white_rectangle->setPixmap(QPixmap(":images/white_rectangle.png"));
    m_white_rectangle->setPos(100,100);

    m_size = 0.8*size_of_board;
    QSize q_size = QSize(m_size,m_size);
    QPixmap board_pixmap = QPixmap(":images/board.png");
    board_pixmap = board_pixmap.scaled(q_size);
    setPixmap(board_pixmap);
    setPos(100,100);


    white_bishop1 = new Bishop(1);
    white_bishop1->move(0,2);
    //white_bishop1->m_board = this;
    white_bishop2 = new Bishop(1);
    white_bishop2->move(0,5);
    //white_bishop2->m_board = this;


    black_bishop1 = new Bishop(0);
    black_bishop1->move(7,2);
    //black_bishop1->m_board = this;

    black_bishop2 = new Bishop(0);
    black_bishop2->move(7,5);
    //black_bishop2->m_board = this;


    std::list<Pieces*> pieces;


    white_knight1 = new Knight(1);
    white_knight1->move(0,1);
    //white_knight1->m_board = this;

    white_knight2 = new Knight(1);
    white_knight2->move(0,6);
    //white_knight2->m_board = this;

    black_knight1 = new Knight(0);
    black_knight1->move(7,1);
    //black_knight1->m_board = this;
    black_knight2 = new Knight(0);
    black_knight2->move(7,6);
    //black_knight2->m_board = this;

    white_pawn1 = new Pawn(1);
    white_pawn1->move(1,0);
    //white_pawn1->m_board = this;
    white_pawn2 = new Pawn(1);
    white_pawn2->move(1,1);
    //white_pawn2->m_board = this;
    white_pawn3 = new Pawn(1);
    white_pawn3->move(1,2);
    //white_pawn3->m_board = this;
    white_pawn4 = new Pawn(1);
    white_pawn4->move(1,3);
    //white_pawn4->m_board = this;
    white_pawn5 = new Pawn(1);
    white_pawn5->move(1,4);
    //white_pawn5->m_board = this;
    white_pawn6 = new Pawn(1);
    white_pawn6->move(1,5);
    //white_pawn6->m_board = this;
    white_pawn7 = new Pawn(1);
    white_pawn7->move(1,6);
    //white_pawn7->m_board = this;
    white_pawn8 = new Pawn(1);
    white_pawn8->move(1,7);
    //white_pawn8->m_board = this;

    black_pawn1 = new Pawn(0);
    black_pawn1->move(6,0);
    //black_pawn1->m_board = this;
    black_pawn2 = new Pawn(0);
    black_pawn2->move(6,1);
    //black_pawn2->m_board = this;
    black_pawn3 = new Pawn(0);
    black_pawn3->move(6,2);
    //black_pawn3->m_board = this;
    black_pawn4 = new Pawn(0);
    black_pawn4->move(6,3);
    //black_pawn4->m_board = this;
    black_pawn5 = new Pawn(0);
    black_pawn5->move(6,4);
    //black_pawn5->m_board = this;
    black_pawn6 = new Pawn(0);
    black_pawn6->move(6,5);
    //black_pawn6->m_board = this;
    black_pawn7 = new Pawn(0);
    black_pawn7->move(6,6);
    //black_pawn7->m_board = this;
    black_pawn8 = new Pawn(0);
    black_pawn8->move(6,7);
    //black_pawn8->m_board = this;

    white_king = new King(1);
    white_king->move(0,3);
    //white_king->m_board = this;
    black_king = new King(0);
    black_king->move(7,3);
    //black_king->m_board = this;

    white_queen = new Queen(1);
    white_queen->move(0,4);
    //white_queen->m_board = this;
    black_queen = new Queen(0);
    black_queen->move(7,4);
    //black_queen->m_board = this;

    white_rook1 = new Rook(1);
    white_rook1->move(0,0);
    //white_rook1->m_board = this;
    white_rook2 = new Rook(1);
    white_rook2->move(0,7);
    //white_rook2->m_board = this;

    black_rook1 = new Rook(0);
    black_rook1->move(7,0);
    //black_rook1->m_board = this;
    black_rook2 = new Rook(0);
    black_rook2->move(7,7);
    //black_rook2->m_board = this;

}

std::map<int,Pieces*> Board::pieces_map(std::string &position)
{

    std::map<int,Pieces*> pieces_map;

    for(int i=0; i<64;i++)
    {
        if(position[i]=='1')
        {
            pieces_map[i]  = new Pawn(1);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='a')
        {
            pieces_map[i]  = new Pawn(0);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='2')
        {
            pieces_map[i]  = new Knight(1);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='b')
        {
            pieces_map[i]  = new Knight(0);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='3')
        {
            pieces_map[i]  = new Bishop(1);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='c')
        {
            pieces_map[i]  = new Bishop(0);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='4')
        {
            pieces_map[i]  = new Rook(1);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='d')
        {
            pieces_map[i]  = new Rook(0);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='5')
        {
            pieces_map[i]  = new Queen(1);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='e')
        {
            pieces_map[i]  = new Queen(0);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='6')
        {
            pieces_map[i]  = new King(1);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='f')
        {
            pieces_map[i]  = new King(0);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }

        //Promotion Pieces

        else if(position[i]=='A')
        {
            pieces_map[i]  = new Knight_promotion(0);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='B')
        {
            pieces_map[i]  = new Bishop_promotion(0);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='C')
        {
            pieces_map[i]  = new Rook_promotion(0);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='D')
        {
            pieces_map[i]  = new Queen_promotion(0);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='E')
        {
            pieces_map[i]  = new Knight_promotion(1);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='F')
        {
            pieces_map[i]  = new Bishop_promotion(1);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='G')
        {
            pieces_map[i]  = new Rook_promotion(1);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }
        else if(position[i]=='H')
        {
            pieces_map[i]  = new Queen_promotion(1);
            pieces_map[i]->move(i);
            //pieces_map[i]->m_board = this;
        }

    }
    return pieces_map;
}




void Board::addWhiteRectangletoScene()
{
    scene()->addItem(m_white_rectangle);
}


void Board::removeWhiteRectanglefromScene()
{
    scene()->removeItem(m_white_rectangle);


}

void Board::clear_m_promotion_pieces_position()
{
    m_promotion_pieces_position="";
    for(int i = 0; i<71; i++) m_promotion_pieces_position+='0';
}

void Board::addPiecestoScene(std::string &position)
{
    std::map<int,Pieces*> pieces = pieces_map(position);
    for(int i=0; i<pieces.size(); i++)
        scene()->addItem(pieces[i]);
}

void Board::addPiecestoScene(std::map<int,Pieces*> &pieces)
{
    for(int i=0; i<pieces.size(); i++)
        if(pieces[i]!=nullptr)
        {
            scene()->addItem(pieces[i]);
        }

    qDebug() << "Pieces added to scene";
}

void Board::addPiecestoScenePromotion(int promotion_position)
{
    std::string empty_position="";
    //initialisation of the string
    /*for(int i = 0; i<72; i++)
    {
        empty_position+='0';
    }*/
    //White
    if(promotion_position>10)
    {


        m_promotion_pieces_position[promotion_position]='H';
        m_promotion_pieces_position[promotion_position-8]='G';
        m_promotion_pieces_position[promotion_position-(2*8)]='F';
        m_promotion_pieces_position[promotion_position-(3*8)]='E';
        m_pieces_promotion = pieces_map(m_promotion_pieces_position);
        addPiecestoScene(m_pieces_promotion);


    }
    //Black
    else
    {
        m_promotion_pieces_position[promotion_position]='D';
        m_promotion_pieces_position[promotion_position+8]='C';
        m_promotion_pieces_position[promotion_position+2*8]='B';
        m_promotion_pieces_position[promotion_position+3*8]='A';
        m_pieces_promotion = pieces_map(m_promotion_pieces_position);
        addPiecestoScene(m_pieces_promotion);


    }

}



void Board::removePieces(std::map<int, Pieces *> &pieces)
{
    //scene()->clear();
    //scene()->addItem(this);

    for(int i=0; i<pieces.size(); i++)
    {
        if(pieces[i] != NULL)
        {
            scene()->removeItem(pieces[i]);        
            delete(pieces[i]);

        }


    }
    qDebug() << "Pieces removed from scene";
}

void Board::removePiecesPromotion(std::map<int, Pieces *> &pieces_promotion)
{
    //scene()->clear();
    //scene()->addItem(this);

    for(int i=0; i<pieces_promotion.size(); i++)
    {
        if(pieces_promotion[i] != NULL)
        {
            scene()->removeItem(pieces_promotion[i]);
            delete(pieces_promotion[i]);

        }


    }
    qDebug() << "Pieces removed from scene";
}

char Board::transform_piece_piecePromotion(char piece)
{
    if(piece=='A') return 'b';
    if(piece=='B') return 'c';
    if(piece=='C') return 'd';
    if(piece=='D') return 'e';
    if(piece=='E') return '2';
    if(piece=='F') return '3';
    if(piece=='G') return '4';
    if(piece=='H') return '5';
}


int Board::getRow_origin() const
{
    return row_origin;
}

void Board::setRow_origin(int value)
{
    row_origin = value;
}

int Board::getCol_origin() const
{
    return col_origin;
}

void Board::setCol_origin(int value)
{
    col_origin = value;
}

int Board::getRow_destination() const
{
    return row_destination;
}

void Board::setRow_destination(int value)
{
    row_destination = value;
}

int Board::getCol_destination() const
{
    return col_destination;
}

void Board::setCol_destination(int value)
{
    col_destination = value;
}

int Board::color(const char &character)
{
    if(character == '1' || character == '2' || character == '3'
            || character == '4' || character == '5' || character == '6')
    {
        return 1;
    }
    else if(character == '0')
    {
        return 2;
    }
    else
    {
        return 0;
    }
}



std::string Board::move_piece(std::string position, const int &origin, const int &destination)
{
    position[destination]=position[origin];
    position[origin]='0';
    position = change_turn(position);
    position[int_en_passant]='0';
    return position;
}

std::string Board::move_piece_with_test_complete(std::string position, const int &origin, const int &destination)
{
    //no promotion move
    if(position[int_promotion]=='0')
    {
        //Not King move nor Pawn move nor Rook move
        if(     (position[origin]!='6' && position[origin]!='f')&&
                (position[origin]!='1' && position[origin]!='a')&&
                (position[origin]!='4' && position[origin]!='d'))
        {
            position =move_piece(position, origin, destination);
            return position;
        }
        //King move
        else if(position[origin]=='6' || position[origin]=='f')
        {

            position =move_king(position, origin, destination);
            return position;


        }
        //Rook move
        else if(position[origin]=='4' || position[origin]=='d')
        {

            position =move_rook(position, origin, destination);
            return position;


        }
        //Pawn move
        //Look en_passant and normal_move
        else if(position[origin]=='1' || position[origin]=='a')
        {
            position =move_pawn(position, origin, destination);
            return position;

        }
        else//Move forbidden
        {
            return position;
        }

    }
    // if position[int_promotion] == 1
    else if(position[int_promotion]=='1')
    {

            position[destination]=transform_piece_piecePromotion(m_promotion_pieces_position[origin]);

            position[int_promotion]='0';
            position = change_turn(position);
            return position;


     }
    else
    {
        qDebug() << "position[int_promotion] != '0' and != '1' in move_piece_with_test_complete";
    }

}

void Board::print_board()
{
    for(int i = 0; i<8;i++)
    {
        std::string line = m_position.substr(8*i, 8);
        QString Qline = QString::fromUtf8(line.c_str());
        qDebug() << Qline;
    }
}

void Board::print_board(const std::string &position)
{
    for(int i = 0; i<8;i++)
    {
        std::string line = position.substr(8*i, 8);
        QString Qline = QString::fromUtf8(line.c_str());
        qDebug() << Qline;
    }
    qDebug() << "\n";
}


bool Board::is_tower_way_free(const std::string &position, const int &origin, const int &destination)
{
    int col_origin = origin%8;
    int row_origin = origin/8;
    int col_destination = destination%8;
    int row_destination = destination/8;

    if (col_destination==col_origin)
    {

        int sign = (row_destination-row_origin)/std::abs((row_destination-row_origin));
        for(int i=1; i<std::abs(row_destination-row_origin); i++)
        {
            //qDebug() << i;
            if((position[8*(row_origin+sign*i) + col_origin])!='0')
            {
                return false;
            }
        }
        return true;
    }
    else if (row_destination==row_origin)
    {
        int sign = (col_destination-col_origin)/std::abs((col_destination-col_origin));
        for(int i=1; i<std::abs(col_destination-col_origin); i++)
        {
            if((position[8*row_origin + col_origin+sign*i])!='0')
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }

}

bool Board::is_bishop_way_free(const std::string &position, const int &origin, const int &destination)
{
    int col_origin = origin%8;
    int row_origin = origin/8;
    int col_destination = destination%8;
    int row_destination = destination/8;

    int sign_col = (col_destination-col_origin)/std::abs((col_destination-col_origin));
    int sign_row = (row_destination-row_origin)/std::abs((row_destination-row_origin));
    for(int i=1; i<std::abs(col_destination-col_origin); i++)
    {
        if((position[8*(row_origin+sign_row*i) + col_origin+sign_col*i])!='0')
        {
            return false;
        }
    }
    return true;
}



void Board::Rook_king_moved(std::string &position, const int &origin)
{
    int col_origin = origin%8;
    int row_origin = origin/8;

    if(col_origin == 0 && row_origin==0)
    {
        position[64]=1;
    }
    if(col_origin == 7 && row_origin==0)
    {
        position[65]=1;
    }
    if(col_origin == 0 && row_origin==7)
    {
        position[66]=1;
    }
    if(col_origin == 7 && row_origin==7)
    {
        position[67]=1;
    }
    if(col_origin == 3 && row_origin==0)
    {
        position[64]=1;
        position[65]=1;
    }
    if(col_origin == 3 && row_origin==7)
    {
        position[66]=1;
        position[67]=1;
    }
}

std::string Board::change_turn(std::string position)
{
    if (position[68]=='0')
    {
        position[68]='1';
        return position;
    }
    else
    {
        position[68]='0';
        return position;
    }
}

bool Board::is_square_attacked(std::string &position, int square)
{

    std::string position_copy = change_turn(position);
    int white_to_play;
    if(position_copy[68]=='0')
    {
        white_to_play = 0;
    }
    else
    {
        white_to_play = 1;
    }

    std::vector<size_t> ennemy_pieces_position = find_pieces(position, white_to_play);

    for (std::vector<size_t>::const_iterator piece_position= ennemy_pieces_position.begin();
         piece_position!=ennemy_pieces_position.end(); ++piece_position)

    {
        //qDebug() << "test move " << *piece_position << "to" << white_king_position;
        if (is_move_allowed(position_copy, static_cast<int>(*piece_position), square))
        {
            //qDebug()<< "check";
            return true;

        }

    }
    //qDebug() << "nocheck white king position" << white_king_position;
    return false;
}


bool Board::is_check(std::string &position)
{
    if (position[68]=='1')//if White to play
    {
        int white_king_position = position.find('6');
        std::string position_copy = change_turn(position);
        std::vector<size_t> black_pieces_position = find_pieces(position, 0);

        for (std::vector<size_t>::const_iterator piece_position= black_pieces_position.begin();
             piece_position!=black_pieces_position.end(); ++piece_position)

        {
            //qDebug() << "test move " << *piece_position << "to" << white_king_position;
            if (is_move_allowed(position_copy, static_cast<int>(*piece_position), static_cast<int>(white_king_position)))
            {
                //qDebug()<< "check";
                return true;

            }

        }
        //qDebug() << "nocheck white king position" << white_king_position;
        return false;


    }
    else
    {
        int black_king_position = position.find('f');
        std::vector<size_t> white_pieces_position = find_pieces(position, 1);
        std::string position_copy = change_turn(position);
        for (std::vector<size_t>::const_iterator piece_position= white_pieces_position.begin();
             piece_position!=white_pieces_position.end(); ++piece_position)
        {
            //qDebug() << "test move " << *piece_position << "to" << black_king_position;
            if (is_move_allowed(position_copy, static_cast<int>(*piece_position), static_cast<int>(black_king_position)))
            {
                //qDebug()<< "check";
                return true;
            }
        }
        //qDebug() << "nocheck black king position:" << black_king_position;
        return false;
    }
}

std::vector<size_t> Board::find_pieces(const std::string &position, const int &color)
{
    if (color == 0)
    {
        std::vector<char> black_pieces;
        black_pieces.push_back('a');
        black_pieces.push_back('b');
        black_pieces.push_back('c');
        black_pieces.push_back('d');
        black_pieces.push_back('e');
        black_pieces.push_back('f');

        std::vector<size_t> black_pieces_positions;
        for (std::vector<char>::const_iterator piece= black_pieces.begin(); piece!= black_pieces.end(); ++piece)
        {
            size_t n = position.find(*piece);

               while (n < position.length())
               {
                   //qDebug() << "black pieces positions: " << n;
                   black_pieces_positions.push_back(n);
                   n = position.find(*piece, n + 1);
               }

        }

        return black_pieces_positions;

    }

    if (color == 1)
    {
        std::vector<char> white_pieces;
        white_pieces.push_back('1');
        white_pieces.push_back('2');
        white_pieces.push_back('3');
        white_pieces.push_back('4');
        white_pieces.push_back('5');
        white_pieces.push_back('6');

        std::vector<size_t> white_pieces_positions;
        for (std::vector<char>::const_iterator piece= white_pieces.begin(); piece!= white_pieces.end(); ++piece)
        {
            size_t n = position.find(*piece);

               while (n < position.length())
               {
                   //qDebug() << "white pieces positions: " << n;
                   white_pieces_positions.push_back(n);
                   n = position.find(*piece, n + 1);
               }

        }
        return white_pieces_positions;

    }

}

std::string Board::getPosition() const
{
    return m_position;
}

void Board::setPosition(const std::string &position)
{
    m_position = position;
}

int Board::minimax( std::string &position, int depth)
{
    if (depth==0)
    {
        count_positions_screened+=1;
        return evaluation_position(position);
    }
    else
    {
        if(position[int_player_turn]=='1')
        {
            int value=-100000;
            std::vector<std::string> next_positions= next_allowed_positions(position);
            for(std::vector<std::string>::const_iterator it_position=next_positions.begin(); it_position!=next_positions.end();
                it_position++)
            {
                count_positions_screened+=1;
                std::string current_position = *it_position;
                value = std::max(value,minimax(current_position, depth-1));

            }
            return value;
        }
        else if(position[int_player_turn]=='0')
        {
            int value=100000;
            std::vector<std::string> next_positions= next_allowed_positions(position);

            for(std::vector<std::string>::const_iterator it_position=next_positions.begin(); it_position!=next_positions.end();
                it_position++)
            {
                count_positions_screened+=1;
                std::string current_position = *it_position;
                value = std::min(value,minimax(current_position, depth-1));
            }
            return value;
        }
    }

}

int Board::alphabeta( std::string &position, int depth, int alpha, int beta)
{
    if (depth==0)
    {
        count_positions_screened+=1;
        return evaluation_position(position);
    }
    else
    {
        if(position[int_player_turn]=='1')
        {
            int value=-100000;
            std::vector<std::string> next_positions= next_allowed_positions(position);
            for(std::vector<std::string>::const_iterator it_position=next_positions.begin(); it_position!=next_positions.end();
                it_position++)
            {
                count_positions_screened+=1;
                std::string current_position = *it_position;
                value = std::max(value,alphabeta(current_position, depth-1, alpha, beta));
                if(value>=beta)
                {
                    return value;
                }
                else alpha = std::max(alpha, value);
            }
            return value;
        }
        else if(position[int_player_turn]=='0')
        {
            int value=100000;
            std::vector<std::string> next_positions= next_allowed_positions(position);

            for(std::vector<std::string>::const_iterator it_position=next_positions.begin(); it_position!=next_positions.end();
                it_position++)
            {
                count_positions_screened+=1;
                std::string current_position = *it_position;
                value = std::min(value,alphabeta(current_position, depth-1, alpha, beta));
                if(value<=alpha)
                {
                    return value;
                }
                else beta = std::min(beta, value);
            }
            return value;
        }
    }

}

std::string Board::find_best_move( std::string &position, int depth)
{
    count_positions_screened=0;
    std::vector<std::string> next_positions= next_allowed_positions(position);
    if(position[int_player_turn]=='1')
    {
        int score = -100000;
        std::string best_position = *next_positions.begin();
        for(std::vector<std::string>::const_iterator it_position=next_positions.begin(); it_position!=next_positions.end();
            it_position++)
        {
            std::string _position = *it_position;
            int eval=minimax(_position,depth);
            if(eval>score)
            {
                score = eval;
                best_position = _position;
            }
        }
        return best_position;
    }
    else
    {
        int score = +100000;
        std::string best_position = *next_positions.begin();
        for(std::vector<std::string>::const_iterator it_position=next_positions.begin(); it_position!=next_positions.end();
            it_position++)
        {
            std::string _position = *it_position;
            int eval=minimax(_position,depth);
            if(eval<score)
            {
                score = eval;
                best_position = _position;
            }
        }
        qDebug() << "count_positions_screened= " <<count_positions_screened;
        return best_position;
    }
}

std::string Board::find_best_move_alpha_beta( std::string &position, int depth)
{
    count_positions_screened=0;
    std::vector<std::string> next_positions= next_allowed_positions(position);
    if(position[int_player_turn]=='1')
    {
        int score = -100000;
        std::string best_position = *next_positions.begin();
        for(std::vector<std::string>::const_iterator it_position=next_positions.begin(); it_position!=next_positions.end();
            it_position++)
        {
            std::string _position = *it_position;
            int eval=alphabeta(_position,depth,-100000,100000);
            if(eval>score)
            {
                score = eval;
                best_position = _position;
            }
        }
        return best_position;
    }
    else
    {
        int score = +100000;
        std::string best_position = *next_positions.begin();
        for(std::vector<std::string>::const_iterator it_position=next_positions.begin(); it_position!=next_positions.end();
            it_position++)
        {
            std::string _position = *it_position;
            int eval=alphabeta(_position,depth,-100000,100000);
            if(eval<score)
            {
                score = eval;
                best_position = _position;
            }
        }
        qDebug() << "count_positions_screened= " <<count_positions_screened;
        return best_position;
    }
}

int Board::getOrigin() const
{
    return origin;
}

void Board::setOrigin(int value)
{
    origin = value;
}

int Board::getDestination() const
{
    return destination;
}

void Board::setDestination(int value)
{
    destination = value;
}

std::vector<std::string> Board::next_allowed_positions(std:: string &position)
{
    std::vector<std::string> next_allowed_positions;

    //define player turn
    int white_to_play;
    if(position[68]=='0')
    {
        white_to_play = 0;
    }
    else
    {
        white_to_play = 1;
    }
    //find all the pieces
    std::vector<size_t> pieces_position = find_pieces(position, white_to_play);

    //Check each piece
    for (std::vector<size_t>::const_iterator piece_position= pieces_position.begin();
         piece_position!=pieces_position.end(); ++piece_position)
    {
        //for each piece, check the next possible destinations
        int origin = static_cast<int>(*piece_position);
        std::vector<int> next_possible_destinations=next_possible_destinations_by_piece(position[origin], origin);

        //for each destination, check if move is allowed
        for(std::vector<int>::const_iterator possible_destination=next_possible_destinations.begin();
            possible_destination!=next_possible_destinations.end();++possible_destination)
        {
            int destination = static_cast<int>(*possible_destination);
            if(is_move_allowed_complete(position,origin,destination))
            {   //check promotion
                if(position[origin]=='1' && destination/8==7)
                {
                    std::string next_position = move_piece_with_test_complete(position,origin,destination);
                    next_position = change_turn(next_position);
                    next_position[int_promotion]='0'; //those two lines because the pawn move has been coded strangely for graphical purposes
                    next_position[destination]='2';
                    next_allowed_positions.push_back(next_position);
                    next_position[destination]='3';
                    next_allowed_positions.push_back(next_position);
                    next_position[destination]='4';
                    next_allowed_positions.push_back(next_position);
                    next_position[destination]='5';
                    next_allowed_positions.push_back(next_position);

                }
                else if(position[origin]=='a' && destination/8==0)
                {
                    std::string next_position = move_piece_with_test_complete(position,origin,destination);
                    next_position[destination]='b';
                    next_allowed_positions.push_back(next_position);
                    next_position[destination]='c';
                    next_allowed_positions.push_back(next_position);
                    next_position[destination]='d';
                    next_allowed_positions.push_back(next_position);
                    next_position[destination]='e';
                    next_allowed_positions.push_back(next_position);

                }
                // if no promotion
                else
                {
                    std::string next_position = move_piece_with_test_complete(position,origin,destination);
                    next_allowed_positions.push_back(next_position);
                }
            }
        }
    }
    //print the positions
    /*for(std::vector<std::string>::const_iterator printposition=next_allowed_positions.begin();
        printposition!=next_allowed_positions.end(); printposition++)
    {
        print_board(*printposition);
    }*/

return next_allowed_positions;
}

std::vector<int> Board::next_possible_destinations_by_piece(const char &piece, const int &origin)
{
    std::vector<int> possible_destinations;

    if(piece == '1')
    {
        if(origin/8==1)
        {
            possible_destinations.push_back(origin+8);
            possible_destinations.push_back(origin+16);
            possible_destinations.push_back(origin+7);
            possible_destinations.push_back(origin+9);
            return possible_destinations;
        }
        else
        {
            possible_destinations.push_back(origin+8);
            possible_destinations.push_back(origin+7);
            possible_destinations.push_back(origin+9);
            return possible_destinations;

        }

    }
    if(piece == '2' || piece == 'b')
    {
        //Can be Upgraded
        int dest=origin+17;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin+15;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin+10;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin+6;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin-17;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin-15;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin-10;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin-6;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);

        return possible_destinations;


    }
    if(piece == '3'|| piece == 'c')
    {
        for(int i=1; i<8;i++)
        {
            int dest=origin-7*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin+7*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin-9*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin+9*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        }
        return possible_destinations;
    }
    if(piece == '4'|| piece == 'd')
    {
        for(int i=1; i<8;i++)
        {
            int dest=origin-8*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin+8*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin-i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin+i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
         }
        return possible_destinations;
    }
    if(piece == '5'|| piece == 'e')
    {
        for(int i=1; i<8;i++)
        {
            int dest=origin-8*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin+8*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin-i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin+i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin-7*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin+7*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin-9*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);
            dest=origin+9*i;
            if(dest>=0 && dest<64) possible_destinations.push_back(dest);

        }
        return possible_destinations;
    }
    if(piece == '6' || piece == 'f')
    {
        int dest=origin-1;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin+1;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin-8;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin+8;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin-7;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin+7;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin-9;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin+9;
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin-2;//Castle
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);
        dest=origin+2;//Castle
        if(dest>=0 && dest<64) possible_destinations.push_back(dest);



        return possible_destinations;

    }
    if(piece == 'a')
    {
        if(origin/8==6)
        {
            possible_destinations.push_back(origin-8);
            possible_destinations.push_back(origin-16);
            possible_destinations.push_back(origin-7);
            possible_destinations.push_back(origin-9);
            return possible_destinations;
        }
        else
        {
            possible_destinations.push_back(origin-8);
            possible_destinations.push_back(origin-7);
            possible_destinations.push_back(origin-9);
            return possible_destinations;

        }

    }

}

int Board::evaluation_position(const std::string &position)
{
    int score = 0;
    for(int i=0;i<64;i++)
    {
        score+=pieces_value[position[i]];
    }
    return score;
}



//Overload of is_move_allowed
bool Board::is_move_allowed(std::string &position, const int &origin, const int &destination)
{
    int col_origin = origin%8;
    int row_origin = origin/8;
    int col_destination = destination%8;
    int row_destination = destination/8;

        char Piece_origin = position[8*row_origin + col_origin];
        char Piece_destination = position[8*row_destination + col_destination];
        // if destination is out of board
        // OR destination == origin

        if(std::max(row_destination,col_destination) >7 || std::min(row_destination,col_destination)<0 ||
                (row_origin==row_destination && col_origin == col_destination)
                || (color(Piece_origin)==color(Piece_destination)))
        {
            return false;
        }



        switch(Piece_origin)
        {
            case '0':
            {
                return false;
            }
            // White Pawn:
            case '1':
            {
                //Check White To play
                if (position[68]=='0')
                {
                    return false;
                }
                //White Pawn first row:

                if (row_origin == 1)
                {
                    if (col_destination == col_origin && (row_destination-row_origin)<=2 && color(Piece_destination)==2)
                    {
                        return true;
                    }
                    else if(abs(col_destination-col_origin) == 1 && row_destination-row_origin==1 && color(Piece_destination)==0)
                    {
                        return true;
                    }
                }
                // White Pawn other rows:
               if (col_destination == col_origin && (row_destination-row_origin)==1 && color(Piece_destination)==2)
               {
                   return true;
               }
               // White Pawn takes
               else if(abs(col_destination-col_origin) == 1 && row_destination-row_origin==1 && color(Piece_destination)==0)
               {
                   return true;
               }

               else
               {
                   return false;
               }


            }//end White Pawn




            // Black Pawn:
            case 'a':
            {
                //Check White To play
                if (position[68]=='1')
                {
                    return false;
                }
                //Black Pawn first row:
                if (row_origin == 6)
                {
                    if (col_destination == col_origin && -(row_destination-row_origin)<=2 && color(Piece_destination)==2)
                    {
                        return true;
                    }
                    else if(abs(col_destination-col_origin) == 1 && row_origin-row_destination==1 && color(Piece_destination)==1)
                    {
                        return true;
                    }
                }
                // Black Pawn other rows:
               if (col_destination == col_origin && -(row_destination-row_origin)==1 && color(Piece_destination)==2)
               {
                   return true;
               }
               // Black Pawn takes
               else if(abs(col_destination-col_origin) == 1 && row_origin-row_destination==1 && color(Piece_destination)==1)
               {
                   return true;
               }

               else
               {
                   return false;
               }
            }//end Black Pawn

        case '2': //White Knight
        {
            //Check White To play
            if (position[68]=='0')
            {
                return false;
            }

            if((std::abs(col_destination-col_origin)==1 && std::abs(row_destination-row_origin)==2)
                    ||(std::abs(col_destination-col_origin)==2 && std::abs(row_destination-row_origin)==1))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        case 'b': //Black Knight
        {
            //Check White To play
            if (position[68]=='1')
            {
                return false;
            }

            if((std::abs(col_destination-col_origin)==1 && std::abs(row_destination-row_origin)==2)
                    ||(std::abs(col_destination-col_origin)==2 && std::abs(row_destination-row_origin)==1))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        case '3': // White Bishop
        {
            //Check White To play
            if (position[68]=='0')
            {
                return false;
            }

            if ((std::abs(col_destination-col_origin)==std::abs(row_destination-row_origin))
                    && is_bishop_way_free(position, origin, destination) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        case 'c': // Black Bishop
        {
            //Check White To play
            if (position[68]=='1')
            {
                return false;
            }

            if ((std::abs(col_destination-col_origin)==std::abs(row_destination-row_origin))
                    && is_bishop_way_free(position, origin, destination) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        case '4': //White Rook
        {
            //Check White To play
            if (position[68]=='0')
            {
                return false;
            }

            if ((row_destination==row_origin || col_destination==col_origin) && is_tower_way_free(position, origin, destination))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        case 'd': //Black Rook
        {
            //Check White To play
            if (position[68]=='1')
            {
                return false;
            }

            if ((row_destination==row_origin || col_destination==col_origin) && is_tower_way_free(position, origin, destination))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        case 'e': //Black Queen
        {
            //Check White To play
            if (position[68]=='1')
            {
                return false;
            }

            if (((row_destination==row_origin || col_destination==col_origin) && is_tower_way_free(position, origin, destination))
                    ||((std::abs(col_destination-col_origin)==std::abs(row_destination-row_origin))&& is_bishop_way_free(position, origin, destination)))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        case '5': //White Queen
        {
            //Check White To play
            if (position[68]=='0')
            {
                return false;
            }

            if (((row_destination==row_origin || col_destination==col_origin) && is_tower_way_free(position, origin, destination))
                    ||((std::abs(col_destination-col_origin)==std::abs(row_destination-row_origin))&& is_bishop_way_free(position, origin, destination)))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        case '6': //White King
        {
            //Check White To play
            if (position[68]=='0')
            {
                return false;
            }




            if (std::abs(row_destination-row_origin) <=1 && std::abs(col_destination-col_origin)<=1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        case 'f': //Black King
        {
            //Check White To play
            if (position[68]=='1')
            {
                return false;
            }

            if (std::abs(row_destination-row_origin) <=1 && std::abs(col_destination-col_origin)<=1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        }// end switch;
        return true;




}

bool Board::is_move_allowed_with_check(std::string &position, const int &origin, const int &destination)
{
    if (is_move_allowed(position,origin,destination))
        {
            // Look if is check in next move
            std::string position_copy;
            position_copy = move_piece(position, origin, destination);
            position_copy = change_turn(position_copy);

            if (is_check(position_copy))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }


}

bool Board::is_move_allowed_complete(std::string &position, const int &origin, const int &destination)
{
    int int_promotion= 70;

    //no promotion move
    if(position[int_promotion]=='0')
    {

        //Not King move nor Pawn move nor Rook move
        if(is_move_allowed_with_check(position,origin, destination) &&
                (position[origin]!='6' && position[origin]!='f')&&
                (position[origin]!='1' && position[origin]!='a')&&
                (position[origin]!='4' && position[origin]!='d'))
        {
            return true;
        }
        //King move
        else if((is_move_allowed_with_check(position,origin, destination) ||is_castling_allowed(position,origin, destination)) &&
                (position[origin]=='6' || position[origin]=='f'))
        {
            return true;
        }
        //Rook move
        else if((is_move_allowed_with_check(position,origin, destination)) &&
                (position[origin]=='4' || position[origin]=='d'))
        {
            return true;
        }

        //Pawn move
        //Look en_passant and normal_move
        else if((is_move_allowed_with_check(position,origin, destination) ||
                 ((position[origin]=='1' || position[origin]=='a') &&
                   (is_en_passant_allowed(position,origin, destination)))))
        {
            //Look promotion
            return true;


        }
        else
        {
            return false;
        }

    }
    // if position[int_promotion] == 1
    else
    {
        if(position[int_player_turn]==0)
        {
            if(origin == destination || origin ==destination +8
                    || origin ==destination +16 || origin ==destination +24)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(origin == destination || origin ==destination -8
                    || origin ==destination -16 || origin ==destination -24)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
std::string Board::castle(std::string &position, const int &origin, const int &destination)
{
    if(origin ==3 && destination == 1)
    {
        position[origin]='0';
        position[destination]='6';
        position[0]='0';
        position[2]='4';
        position[int_white_king_castle]='1';
        position[int_white_queen_castle]='1';


        return position;
    }

    else if(origin == 3 && destination ==5)
    {
        position[origin]='0';
        position[destination]='6';
        position[7]='0';
        position[4]='4';
        position[int_white_king_castle]='1';
        position[int_white_queen_castle]='1';

        return position;

    }
    else if(origin == 59 && destination ==57)
      {
          position[origin]='0';
          position[destination]='f';
          position[56]='0';
          position[58]='d';
          position[int_black_king_castle]='1';
          position[int_black_queen_castle]='1';

          return position;

      }
    else if(origin == 59 && destination == 61)
        {
            position[origin]='0';
            position[destination]='f';
            position[63]='0';
            position[60]='d';
            position[int_black_king_castle]='1';
            position[int_black_queen_castle]='1';
            return position;
        }
}




std::string Board::move_king(std::string position, const int &origin, const int &destination)
{
    std::string return_position;
    if(is_castling_allowed(position, origin, destination))
    {
        return_position = castle(position, origin, destination);
        return_position = change_turn(return_position);
        if(position[origin]=='6')
        {
            return_position[int_white_king_castle]='1';
            return_position[int_white_queen_castle]='1';
        }
        else if(position[origin]=='f')
        {
            return_position[int_black_king_castle]='1';
            return_position[int_black_queen_castle]='1';
        }
    }
    else
    {
        return_position = move_piece(position, origin, destination);
        if(position[origin]=='6')
        {
            return_position[int_white_king_castle]='1';
            return_position[int_white_queen_castle]='1';
        }
        else if(position[origin]=='f')
        {
            return_position[int_black_king_castle]='1';
            return_position[int_black_queen_castle]='1';
        }
    }


    return return_position;
}

std::string Board::move_pawn(std::string &position,const int &origin, const int &destination)
{
    int col_origin = origin%8;
    int col_destination = destination%8;
    //prise en passant blanche

    if (position[origin] == '1' && position[destination]=='0' && col_origin != col_destination)
    {
        position[origin]='0';
        position[destination]='1';
        position[destination - 8]='0';
        position[int_en_passant]='0';
        position = change_turn(position);
        return position;

    }
    //prise en passant noire
    else if (position[origin] == 'a' && position[destination]=='0' && col_origin != col_destination)
    {
        position[origin]='0';
        position[destination]='a';
        position[destination + 8]='0';
        position[int_en_passant]='0';
        position = change_turn(position);

        return position;

    }
    //double square move
    else if((position[origin]=='1' && destination - origin == 16) || (position[origin]=='a' && destination - origin == -16))
    {
        position = move_piece(position,origin,destination);
        position[int_en_passant]=destination;

        return position;

    }
    //white promotion
    else if(position[origin]=='1' && row_destination==7)
    {
        position[destination]='0';
        position[origin] = '0';
        position[int_promotion]='1';

        return position;
    }
    //black promotion
    else if(position[origin]=='a' && row_destination==0)
    {
        position[destination]='0';
        position[origin] = '0';
        position[int_promotion]='1';

        return position;
    }
    else
    {
        position = move_piece(position,origin,destination);
        return position;
    }
}

std::string Board::move_rook(std::string position, const int &origin, const int &destination)
{

    std::string return_position = move_piece(position,origin,destination);
    if(origin == 0) return_position[int_white_king_castle]='1';
    if(origin == 7) return_position[int_white_queen_castle]='1';
    if(origin == 56) return_position[int_black_king_castle]='1';
    if(origin == 63) return_position[int_black_queen_castle]='1';
    return return_position;
}




bool Board::is_en_passant_allowed(std::string position, const int &origin, const int &destination)
{
    int row_origin = origin/8;

    if(position[origin]=='1' && row_origin == 4 && position[int_en_passant]== destination-8
            &&  (destination-origin==7 || destination-origin == 9))

    {
        return true;
    }
    else if(position[origin]=='a' && row_origin == 3 && position[int_en_passant]== destination+8
            &&  (destination-origin==-7 || destination-origin == -9))
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Board::white_king_side_castle(std::string &position, const int &origin, const int &destination)
{
    if(position[origin]=='6' && position[int_white_king_castle]=='0' && is_tower_way_free(position,3,0)
            && destination==1
            &&(!is_square_attacked(position,1)) &&(!is_square_attacked(position,2)) &&(!is_square_attacked(position,3)))
    {
        position[origin]='0';
        position[destination]='6';
        position[0]='0';
        position[2]='4';
        return position;
    }
    else
    {
        return position;
    }
}

std::string Board::white_queen_side_castle(std::string &position, const int &origin, const int &destination)
{
    if(position[origin]=='6' && position[int_white_queen_castle]=='0' && is_tower_way_free(position,7,3)
            && destination==5
            &&(!is_square_attacked(position,3)) &&(!is_square_attacked(position,4)) &&(!is_square_attacked(position,5)))
    {
        position[origin]='0';
        position[destination]='6';
        position[7]='0';
        position[4]='4';
        return position;

    }
    else
    {
        return position;
    }
}

std::string Board::black_king_side_castle(std::string &position, const int &origin, const int &destination)
{
    if(position[origin]=='f' && position[int_black_king_castle]=='0' && is_tower_way_free(position,59,56)
            && destination==58
            &&(!is_square_attacked(position,59)) &&(!is_square_attacked(position,58)) &&(!is_square_attacked(position,57)))
    {
        position[origin]='0';
        position[destination]='f';
        position[56]='0';
        position[58]='d';
        return position;

    }
    else
    {
        return position;
    }
}

std::string Board::black_queen_side_castle(std::string &position, const int &origin, const int &destination)
{
    if(position[origin]=='f' && position[int_white_queen_castle]=='0' && is_tower_way_free(position,3,0)
            && destination==61
            &&(!is_square_attacked(position,59)) &&(!is_square_attacked(position,60)) &&(!is_square_attacked(position,61)))
    {
        position[origin]='0';
        position[destination]='f';
        position[63]='0';
        position[60]='4';
        return position;

    }
    else
    {
        return position;
    }
}



bool Board::is_castling_allowed(std::string &position, const int &origin, const int &destination)
{



    // White King Side castling
    if(position[origin]=='6' && position[int_white_king_castle]=='0' && is_tower_way_free(position,3,0)&& destination==1
            &&(!is_square_attacked(position,1)) &&(!is_square_attacked(position,2)) &&(!is_square_attacked(position,3)))
    {
        return true;

    }
    // White Queen Side castling
    else if(position[origin] == '6' && position[int_white_queen_castle]=='0' && is_tower_way_free(position,3,7)&& destination==5
         &&(!is_square_attacked(position,3)) &&(!is_square_attacked(position,4)) &&(!is_square_attacked(position,5)))
    {
        return true;
    }

    // Black King Side castling
    else if(position[origin]=='f' && position[int_black_king_castle]=='0' && is_tower_way_free(position,59,56)&& destination==57
            &&(!is_square_attacked(position,59)) &&(!is_square_attacked(position,58)) &&(!is_square_attacked(position,57)))
    {
        return true;
    }
    // Black Queen Side castling
    else if(position[origin]=='f' && position[int_black_queen_castle]=='0' && is_tower_way_free(position,59,63)&& destination==61
         &&(!is_square_attacked(position,59)) &&(!is_square_attacked(position,60)) &&(!is_square_attacked(position,61)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
