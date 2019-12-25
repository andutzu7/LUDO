#include "player.h"
#include <stdio.h>
#include <QMessageBox>
Player::Player(const std::vector<Piece>& nPieces,const int nLabel)
{
    if(nPieces.size()>4 || nPieces.size()==0)
    {
        printf("ERROR");
    }
    pieces=nPieces;
    label=nLabel;
}
int Player::GetNrPiecesHome() const
{
    return nrOfPiecesHome;
}
