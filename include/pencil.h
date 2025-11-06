#ifndef PENCIL_H
#define PENCIL_H

#include <QPoint>
#include <QColor>
#include "tool.h"

class Pencil : public Tool{

public:

    Pencil();

    void drawPoint(QPoint currentPoint, QColor currentColor);

    void applyChange(QPoint currentPoint, QColor currentColor);

    ~Pencil();
};

#endif // PENCIL_H
