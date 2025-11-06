#ifndef ERASER_H
#define ERASER_H

#include <QPoint>
#include <QColor>
#include "pencil.h"

class Eraser : public Pencil{

public:

    Eraser();

    void drawPoint(QPoint currentPoint, QColor currentColor);

    void applyChange(QPoint currentPoint, QColor currentColor);

    ~Eraser();

};

#endif // ERASER_H
