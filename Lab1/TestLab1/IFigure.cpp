#include "pch.h"
#include "IFigure.h"

IFigure::IFigure()
    :isFilled(0)
{
}

void IFigure::fill()
{
    isFilled = !isFilled;
    refreshCoordinates();
}