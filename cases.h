#ifndef CASES_H
#define CASES_H




class cases
{
public:
    cases();
    cases(int value);
    int getValue();
    int getX();
    int getY();
    int getIdValue();
    bool isLocked();
    void setValue(int value);
    void setValue(int value, bool lock);
    void lockPiece();
    void setXy(int x, int y);
private:
    int x,y,value;
    bool lock;
    int Idcase;
};

#endif // PUZZLEPIECE_H
