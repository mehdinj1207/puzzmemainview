#include "takuzu.h"




takuzu::takuzu() { /* private */ }


takuzu::takuzu(int size)
{
    srand(time(NULL));
    this->size = size;
    pieces = new cases*[getSize()];
    piecesTemplate = new cases*[getSize()];
    createPiecesDataStructure(this->pieces);
    createPiecesDataStructure(this->piecesTemplate);
}


takuzu::~takuzu()
{
    deleteAllPieces();
}


void takuzu::deleteAllPieces()
{
    for (int i = 0; i < getSize(); i++)
    {
        delete [] pieces[i];
        delete [] piecesTemplate[i];
    }
    delete [] pieces;
    delete [] piecesTemplate;
}

void takuzu::createPiecesDataStructure(cases **newPieces)
{
    for(int i = 0; i < getSize(); ++i)
    {
        newPieces[i] = new cases[getSize()];
        for(int j = 0;j < getSize();j++)
        {
            newPieces[i][j].setXy(i,j);
        }
    }
}

void takuzu::copyPiecesToTemplate()
{
    for(int i = 0;i < getSize(); i++)
    {
        for(int j = 0;j < getSize(); j++)
        {
            piecesTemplate[i][j].setValue(pieces[i][j].getValue());
        }
    }
}


void takuzu::reloadPieceDataStructure()
{
    deleteAllPieces();
    pieces = new cases*[getSize()];
    piecesTemplate = new cases*[getSize()];
    createPiecesDataStructure(this->pieces);
    createPiecesDataStructure(this->piecesTemplate);
}


bool takuzu::createNewGame(int difficulty)
{
    reloadPieceDataStructure();
    if(solveRandom())
    {
        obfuscatePuzzle((double) getSize() * getSize() / 4 / 100 * difficulty);
        if(isOnlyOneSolutionPossible())
        {
            clearAllUnlockedPieces();
            return true;
        }
    }
    return createNewGame(difficulty);
}



bool takuzu::isOnlyOneSolutionPossible()
{
    if(solveRecursiveOppositeToTemplate())
    {
        if(isPieceDifferentFromTemplate())
        {
            return true;
        }
    }

    return false;
}


bool takuzu::isPieceDifferentFromTemplate()
{
    for(int i = 0;i < getSize(); i++)
    {
        for(int j = 0;j < getSize(); j++)
        {
            if(piecesTemplate[i][j].getValue() != pieces[i][j].getValue())
            {
                //std::cout << "New solution at " << i << "," << j << std::endl;
                return false;
            }
        }
    }
    return true;
}


void takuzu::obfuscatePuzzle(int quantity)
{
    copyPiecesToTemplate();

    hidePiecesFromTo(0, getSize() / 2, quantity);
    hidePiecesFromTo(0, 0, quantity);
    hidePiecesFromTo(getSize() / 2, getSize() / 2, quantity);
    hidePiecesFromTo(getSize() / 2, 0, quantity);

    clearAllUnlockedPieces();
}


void takuzu::clearAllUnlockedPieces()
{
    for(int i = 0;i < getSize(); i++)
    {
        for(int j = 0;j < getSize(); j++)
        {
            if(!pieces[i][j].isLocked())
            {
                pieces[i][j].setValue(2,false);
            }
        }
    }
}

void takuzu::solveHint()
{
    int row,col;

    if(!findNextFreeSpace(row,col))
        return;

    pieces[row][col].setValue(piecesTemplate[row][col].getValue());
}



void takuzu::hidePiecesFromTo(int fromX, int fromY, int quantity)
{
    int limit = getSize() / 2;

    for(int i = 0;i < quantity;i++)
    {
        int x; int y;

        x = rand() % limit + fromX;
        y = rand() % limit + fromY;

        if(pieces[x][y].isLocked())
        {
            i--;
        } else {
            pieces[x][y].lockPiece();
        }
    }
}


void takuzu::setEmptyPiece(int row, int col)
{
    pieces[row][col].setValue(2);
}


int takuzu::getValueByXy(int x, int y)
{
    return pieces[x][y].getValue();
}


cases *takuzu::getPieceByXy(int x, int y)
{
    return &pieces[x][y];
}


int takuzu::getSize()
{
    return this->size;
}


void takuzu::setDefaultPiece(int value, int x, int y, bool lock)
{
    pieces[x][y].setValue(value, lock);
}


bool takuzu::solveRecursive()
{
    int row,col;

    if(!findNextFreeSpace(row,col)) // when solveRecursive() has ran successfully until there
        return true;                // are no more free spaces then the game has been solved

    for(int num = 0;num < 2;num++)
    {
        if(isRecursiveMovementValid(&takuzu::solveRecursive,row,col,num))
            return true;
    }

    return false;
}


bool takuzu::solveRandom()
{
    int row,col;

    if(!findNextFreeSpace(row,col))
        return true;

    if(rand() % 2)
    {
        if(isMovementStartingByZeroValid(&takuzu::solveRandom,row, col))
            return true;

    } else {
        if(isMovementStartingByOneValid(&takuzu::solveRandom,row, col))
            return true;
    }

    return false;
}


bool takuzu::solveRecursiveOppositeToTemplate()
{
    int row,col;

    if(!findNextFreeSpace(row,col))
        return true;

    if(pieces[row][col].getValue() == 0)
    {
        if(isMovementStartingByOneValid(&takuzu::solveRecursiveOppositeToTemplate,row, col))
        {
            return true;
        }
    } else {
        if(isMovementStartingByZeroValid(&takuzu::solveRecursiveOppositeToTemplate,row, col))
        {
            return true;
        }
    }

    return false;
}


bool takuzu::isRecursiveMovementValid(bool (takuzu::*solver)(), int row, int col, int num)
{
    if(IsMovementLocallyPossible(row,col,num))
    {
        if((*this.*solver)())
            return true;

        setEmptyPiece(row,col);
    }
    return false;
}

bool takuzu::isMovementStartingByZeroValid(bool (takuzu::*solver)(), int row, int col)
{
    for(int num = 0;num < 2;num++)
    {
        if(isRecursiveMovementValid(solver,row,col,num))
            return true;
    }
    return false;
}


bool takuzu::isMovementStartingByOneValid(bool (takuzu::*solver)(), int row, int col)
{
    for(int num = 1;num > -1;num--)
    {
        if(isRecursiveMovementValid(solver, row,col,num))
            return true;
    }
    return false;
}


bool takuzu::isRowValid(int row)
{
    if(isRowComplete(row))
        if(!isRowBalanced(row) || !isRowUnique(row))
            return false;

    return true;
}


bool takuzu::isColValid(int col)
{
    if(isColComplete(col))
        if(!isColBalanced(col) || !isColUnique(col))
            return false;

    return true;
}


bool takuzu::findNextFreeSpace(int &row, int &col)
{
    for(row = 0; row < getSize(); row++)
        for(col = 0;col < getSize(); col++)
            if(pieces[row][col].getValue() == 2 && !pieces[row][col].isLocked())
                return true;

    return false;
}


bool takuzu::IsMovementLocallyPossible(int row, int col, int num)
{
    if(isHorizontalNeighborGood(row,col,num) && isVerticalNeighborGood(row,col,num))
    {
        pieces[row][col].setValue(num);

        if(isRowValid(row) && isColValid(col))
            return true;

        setEmptyPiece(row,col);
    }
    return false;
}


bool takuzu::isNumDifferentFromNeighbor(int row, int col, int num, int target)
{
    if(target >= 0 && target < getSize())
    {
        if(pieces[row][col].getValue() == num)
        {
            return false;
        }
    }

    return true;
}


bool takuzu::isMovementRespectingLeftNeighbors(int row, int col, int num)
{
    if(!isNumDifferentFromNeighbor(row-1,col,num,row-1))
        if(!isNumDifferentFromNeighbor(row-2,col,num,row-2))
            return false;

    return true;
}


bool takuzu::isMovementRespectingRightNeighbors(int row, int col, int num)
{
    if(!isNumDifferentFromNeighbor(row+1,col,num,row+1))
        if(!isNumDifferentFromNeighbor(row+2,col,num,row+2))
            return false;

    return true;
}


bool takuzu::isMovementRespectingUpperNeighbors(int row, int col, int num)
{
    if(!isNumDifferentFromNeighbor(row,col-1,num,col-1))
        if(!isNumDifferentFromNeighbor(row,col-2,num,col-2))
            return false;

    return true;
}


bool takuzu::isMovementRespectingBottomNeighbors(int row, int col, int num)
{
    if(!isNumDifferentFromNeighbor(row,col+1,num,col+1))
        if(!isNumDifferentFromNeighbor(row,col+2,num,col+2))
            return false;

    return true;
}


bool takuzu::isHorizontalNeighborGood(int row, int col, int num)
{
    if(isMovementRespectingLeftNeighbors(row,col,num))
        if(isMovementRespectingRightNeighbors(row,col,num))
            return true;

    return false;
}


bool takuzu::isVerticalNeighborGood(int row, int col, int num)
{
    if(isMovementRespectingUpperNeighbors(row,col,num))
        if(isMovementRespectingBottomNeighbors(row,col,num))
            return true;

    return false;
}


bool takuzu::isNeighbourhoodCorrect()
{
    for(int i = 0; i < getSize(); i++)
    {
        for(int j = 0; j < getSize(); j++)
        {
            if(!IsMovementLocallyPossible(i,j,pieces[i][j].getValue()))
                return false;
        }
    }
    return true;
}

bool takuzu::isColUnique(int y)
{
    for(int i = 0; i < getSize(); i++)
    {
        if(i == y)
            continue;

        for(int j = 0;j <= (getSize() - 1);j++)
        {
            if(pieces[j][y].getValue() != pieces[j][i].getValue())
                break;
            if(j == (getSize() - 1))
                return false;
        }
    }
    return true;
}


bool takuzu::isRowUnique(int x)
{
    for(int i = 0; i < getSize(); i++)
    {
        if(i == x)
            continue;

        for(int j = 0; j < getSize(); j++)
        {
            if(pieces[x][j].getValue() != pieces[i][j].getValue())
                break;
            if(j == (getSize() - 1))
                return false;
        }
    }
    return true;
}



bool takuzu::isColComplete(int y)
{
    for(int j = 0; j < getSize(); j++)
    {
        if(pieces[j][y].getValue() == 2)
            return false;
    }
    return true;
}


bool takuzu::isRowComplete(int x)
{
    for(int j = 0; j < getSize(); j++)
    {
        if(pieces[x][j].getValue() == 2)
            return false;
    }
    return true;
}


bool takuzu::isRowBalanced(int x)
{
    int colCount = 0;
    for(int j = 0; j < getSize(); j++)
    {
        int value = pieces[x][j].getValue();

        if(value == 2)
            return false;

        colCount += value;
    }
    return (colCount == (size / 2));
}


bool takuzu::isColBalanced(int y)
{
    int rowCount = 0;
    for(int j = 0; j < getSize(); j++)
    {
        int value = pieces[j][y].getValue();

        if(value == 2)
            return false;

        rowCount += value;
    }
    return (rowCount == (size / 2));
}


bool takuzu::isVerticallyBalanced()
{
    for(int i = 0;i < getSize();i++)
    {
        if(!isColBalanced(i))
            return false;
    }
    return true;
}


bool takuzu::isHorizontallyBalanced()
{
    for(int i = 0;i < getSize();i++)
    {
        if(!isRowBalanced(i))
            return false;
    }
    return true;
}



bool takuzu::isVerticallyDuplicate()
{
    for(int i = 0; i < getSize(); i++)
    {
        if(!isColUnique(i))
            return false;
    }
    return true;
}


bool takuzu::isHorizontallyDuplicate()
{
    for(int i = 0; i < getSize(); i++)
    {
        if(!isRowUnique(i))
            return false;
    }
    return true;
}


std::string takuzu::checkVictory()
{
    std::string result;

    if(!isNeighbourhoodCorrect())
        result = "Unfortunately, you did not solve the board correctly.";

    else if(!isVerticallyBalanced())
        result = "Unfortunately, an asymmetric row was found.";

    else if(!isHorizontallyBalanced())
        result = "Unfortunately, an asymmetric column was found.";

    else if(!isHorizontallyDuplicate())
        result = "Unfortunately, a duplicate row was found.";

    else if(!isVerticallyDuplicate())
        result = "Unfortunately, a duplicate column was found.";

    else
        result = "Congratulations! You won the game.";

    return result;
}

