#ifndef PUZZLESCENE_H
#define PUZZLESCENE_H

#include<QGraphicsScene>
#include "takuzu.h"
#include "PuzzleSceneItem.h"

class PuzzleScene : public QGraphicsScene
{
public:
    PuzzleScene();
    PuzzleScene(QObject *parent);
    void plotBoard();
    void set_takuzu(takuzu *puzzle);
    void setLight(bool light);
    void resetSceneRect();
    void resetColorToWhite();
    void resetColorToBlack();
    long score(long temps);
private:
    int size ;
    long temps ;
    takuzu *puzzle;
    bool light;
    void setSceneItemColor(PuzzleSceneItem *item);
};

#endif // PUZZLESCENE_H
