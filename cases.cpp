#include "cases.h"



cases::cases()
{
    this->value = 2;
    this->lock = false;
}

cases::cases(int value)
{
    this->value = value;
}

void cases::setValue(int value)
{
    this->value = value;
}

int cases::getValue()
{
    return this->value;
}

bool cases::isLocked()
{
    return this->lock;
}

void cases::lockPiece()
{
    this->lock = true;
}

int cases::getX()
{
    return x;
}

int cases::getY()
{
    return y;
}

void cases::setXy(int x, int y)
{
    this->x = x;
    this->y = y;
}

void cases::setValue(int value, bool lock)
{
    this->value = value;
    this->lock = lock;
}
int cases::getIdValue()
{
    return Idcase;
}
