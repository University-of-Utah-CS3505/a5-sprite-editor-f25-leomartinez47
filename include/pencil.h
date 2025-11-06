#ifndef PENCIL_H
#define PENCIL_H
#include "tool.h"

class Pencil : public Tool
{

public:

    void applyChange(QPoint currentPoint, QImage &currFrame, QColor currentColor);

private:

    Tool currentTool;
};

#endif // PENCIL_H
