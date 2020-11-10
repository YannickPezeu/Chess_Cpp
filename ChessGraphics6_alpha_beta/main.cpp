#include "game.h"

#include <QApplication>
int player_turn = 1;
Game* game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    game = new Game();
    game->show();
    game->rotate(180);


    a.exec();
    return a.exec();
}
