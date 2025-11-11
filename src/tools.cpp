#include "tools.h"

void setPixel(QPoint point, QImage &frame, QColor color)
{
    if (frame.valid(point)) {
        frame.setPixelColor(point, color);
    }
}

void Pencil::apply(QPoint point, QImage &frame,  QColor color)
{
    setPixel(point, frame, color);
}

void Eraser::apply(QPoint point, QImage &frame,  QColor /* color unused */)
{
    setPixel(point, frame, QColor(255, 255, 255));
}

QString Pencil::toString(){
    return "Pencil";
}

QString Eraser::toString(){
    return "Eraser";
}
