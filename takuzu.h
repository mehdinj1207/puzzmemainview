//#ifndef TAKUZU_H
//#define TAKUZU_H


#ifndef PUZZLEGAME_H
#define PUZZLEGAME_H

#include <cstdlib>
#include <time.h>
#include "cases.h"
#include <QDebug>
#include <QGraphicsScene>

class takuzu
{
public:
    takuzu(int size);
    ~takuzu();
    cases *getPieceByXy(int x, int y);
    std::string checkVictory();
    int getValueByXy(int x, int y);
    int getSize();
    bool solveRecursive();
    bool solveRandom();
    bool solveRecursiveOppositeToTemplate();
    bool isOnlyOneSolutionPossible();
    void setDefaultPiece(int value, int x, int y, bool lock);
    void obfuscatePuzzle(int quantity);
    void hidePiecesFromTo(int fromX, int fromY, int quantity);
    bool createNewGame(int difficulty);
    void solveHint();

private:
    takuzu();
    cases **pieces = NULL;
    cases **piecesTemplate = NULL;
    int size;
    bool isMovementStartingByZeroValid(bool (takuzu::*solver)(), int row, int col);
    bool isMovementStartingByOneValid(bool (takuzu::*solver)(), int row, int col);
    void setEmptyPiece(int row, int col);
    bool findNextFreeSpace(int &row, int &col);
    bool IsMovementLocallyPossible(int row, int col, int num);
    bool isRowComplete(int x);
    bool isColComplete(int y);
    bool isRowBalanced(int x);
    bool isColBalanced(int y);
    bool isRowUnique(int x);
    bool isColUnique(int y);
    bool isRowValid(int row);
    bool isColValid(int col);
    bool isHorizontalNeighborGood(int row, int col, int num);
    bool isVerticalNeighborGood(int row, int col, int num);
    bool isNeighbourhoodCorrect();
    bool isHorizontallyBalanced();
    bool isVerticallyBalanced();
    bool isVerticallyDuplicate();
    bool isHorizontallyDuplicate();
    bool checkIfPieceAlreadySelected(std::multimap<int, int> *selectedPieces, int x, int y);
    void clearAllUnlockedPieces();
    bool findNextUnlockedSpace(int &row, int &col);
    void copyPiecesToTemplate();
    bool isRecursiveMovementValid(bool (takuzu::*solver)(),int row, int col, int num);
    void createPiecesDataStructure(cases **newPieces);
    bool isSideNeighborRespected(int row, int col, int num, int target);
    bool isNumDifferentFromNeighbor(int row, int col, int num, int target);
    bool isMovementRespectingRightNeighbors(int row, int col, int num);
    bool isMovementRespectingLeftNeighbors(int row, int col, int num);
    bool isMovementRespectingUpperNeighbors(int row, int col, int num);
    bool isMovementRespectingBottomNeighbors(int row, int col, int num);
    bool isPieceDifferentFromTemplate();
    void deleteAllPieces();
    void reloadPieceDataStructure();
};

#endif // PUZZLEGAME_H
