#ifndef BOARD_H
#define BOARD_H
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include "pieces.h"
#include <QDebug>
#include <QRectF>
#include <QGraphicsRectItem>
#include <QBrush>
#include <vector>
#include <map>

class Board: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Board();
    Knight* white_knight1;
    Knight* white_knight2;
    Knight* black_knight1;
    Knight* black_knight2;

    Bishop* white_bishop1;
    Bishop* white_bishop2;
    Bishop* black_bishop1;
    Bishop* black_bishop2;

    Pawn* white_pawn1;
    Pawn* white_pawn2;
    Pawn* white_pawn3;
    Pawn* white_pawn4;
    Pawn* white_pawn5;
    Pawn* white_pawn6;
    Pawn* white_pawn7;
    Pawn* white_pawn8;
    Pawn* black_pawn1;
    Pawn* black_pawn2;
    Pawn* black_pawn3;
    Pawn* black_pawn4;
    Pawn* black_pawn5;
    Pawn* black_pawn6;
    Pawn* black_pawn7;
    Pawn* black_pawn8;

    Rook* white_rook1;
    Rook* white_rook2;
    Rook* black_rook1;
    Rook* black_rook2;

    King* white_king;
    King* black_king;
    Queen* white_queen;
    Queen* black_queen;

    std::map<char,int> pieces_value;

    int int_white_king_castle;
    int int_white_queen_castle;
    int int_black_king_castle;
    int int_black_queen_castle;
    int int_player_turn;
    int int_en_passant;
    int int_promotion;
    char which_pawn_is_takable_en_passant;
    QGraphicsPixmapItem* m_white_rectangle = new QGraphicsPixmapItem;


    int getRow_origin() const;
    void setRow_origin(int value);

    int getCol_origin() const;
    void setCol_origin(int value);

    int getRow_destination() const;
    void setRow_destination(int value);

    int getCol_destination() const;
    void setCol_destination(int value);

    int color(const char& character);


    void print_board();
    void print_board(const std::string &position);

    bool is_move_allowed();
    bool is_move_allowed( std::string &position, const int &origin, const int &destination);
    bool is_move_allowed_with_check( std::string &position, const int &origin, const int &destination);
    bool is_move_allowed_complete(std::string &position, const int &origin, const int &destination);
    bool is_castling_allowed(std::string &position, const int &origin, const int &destination);
    std::string white_king_side_castle(std::string &position, const int &origin, const int &destination);
    std::string white_queen_side_castle(std::string &position, const int &origin, const int &destination);
    std::string black_king_side_castle(std::string &position, const int &origin, const int &destination);
    std::string black_queen_side_castle(std::string &position, const int &origin, const int &destination);
    std::string castle(std::string &position, const int &origin, const int &destination);
    std::string move_piece(std::string position, const int &origin, const int &destination);
    std::string move_king(std::string position, const int &origin, const int &destination);
    std::string move_pawn(std::string &position, const int &origin, const int &destination);
    std::string move_rook(std::string position, const int &origin, const int &destination);
    std::string move_piece_with_test_complete(std::string position, const int &origin, const int &destination);

    bool is_en_passant_allowed(std::string position, const int &origin, const int &destination);

    bool is_tower_way_free(const std::string &position, const int &origin,const int &destination);
    bool is_bishop_way_free(const std::string &position, const int &origin, const int &destination);
    void Rook_king_moved(std::string &position, const int &origin);
    std::string change_turn(std::string position);
    bool is_check(std::string &position);
    std::vector<size_t> find_pieces(const std::string &position,const int &color);
    std::map<int,Pieces*> pieces_map(std::string &position);
    void addPiecestoScene(std::map<int,Pieces*> &pieces);
    void addPiecestoScene(std::string &position);
    void addPiecestoScenePromotion(int promotion_position);
    void addWhiteRectangletoScene();
    void removeWhiteRectanglefromScene();
    void clear_m_promotion_pieces_position();
    bool is_square_attacked(std::string &position, int square);

    void removePieces(std::map<int,Pieces*> &pieces);
    void removePiecesPromotion(std::map<int, Pieces *> &pieces_promotion);
    char transform_piece_piecePromotion(char piece);
    std::map<int,Pieces*> m_pieces;
    std::map<int,Pieces*> m_pieces_promotion;

    char c_white_pawn = '1';
    char c_white_knight = '2';
    char c_white_bishop = '3';
    char c_white_rook = '4';
    char c_white_queen = '5';
    char c_white_king = '6';

    char c_black_pawn = 'a';
    char c_black_knight = 'b';
    char c_black_bishop = 'c';
    char c_black_rook = 'd';
    char c_black_queen = 'e';
    char c_black_king = 'f';

    std::vector<std::string> m_history_positions;
    std::string getPosition() const ;
    void setPosition(const std::string &position);
    std::string m_position;
    std::string m_promotion_pieces_position;
    int minimax( std::string &position, int depth);
    int alphabeta( std::string &position, int depth, int alpha, int beta);
    std::string find_best_move(std::string &position, int depth);
    std::string find_best_move_alpha_beta(std::string &position, int depth);
    int getOrigin() const;
    void setOrigin(int value);


    int getDestination() const;
    void setDestination(int value);
    std::vector<std::string> next_allowed_positions(std::string &position);
    std::vector<int> next_possible_destinations_by_piece(const char &piece, const int &origin);
    int evaluation_position(const std::string &position);

    int row_origin;
    int col_origin;

    int row_destination;
    int col_destination;

    int origin;
    int destination;
    int m_size;
protected:



};

#endif // BOARD_H
