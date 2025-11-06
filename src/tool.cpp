#include "pencil.h"
#include "eraser.h"

/*Sets the color to the current color to be applied to the current frames pixel point*/
void Pencil::applyChange(QPoint currentPoint, QImage &currFrame, QColor currentColor)
{
    if(currFrame.valid(currentPoint))  //Checks if in the image boundaries
    {
        currFrame.setPixelColor(currentPoint, currentColor);
    }
}

/*Sets the color to white to be applied to the current frames pixel point*/
void Eraser::applyChange(QPoint currentPoint, QImage &currFrame, QColor currentColor)
{
    currentColor.setRgb(255, 255, 255);
    if(currFrame.valid(currentPoint))
    {
        currFrame.setPixelColor(currentPoint, currentColor);
    }
}
