#include "pencil.h"
#include "eraser.h"

void Pencil::applyChange(QPoint currentPoint, QImage &currFrame, QColor currentColor)
{


}

void Eraser::applyChange(QPoint currentPoint, QImage &currFrame, QColor currentColor)
{
    currentColor.setRgb(255, 255, 255);
}
