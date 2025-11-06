#ifndef ERASER_H
#define ERASER_H
#include "pencil.h"

namespace Ui {
class Eraser;
}

class Eraser : public Pencil
{

public:

    void applyChange(QPoint currentPoint, QImage &currFrame, QColor currentColor);

private:
    Ui::Eraser *ui;

    Tool currentTool;
};

#endif // ERASER_H
