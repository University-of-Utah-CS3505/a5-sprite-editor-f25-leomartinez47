#ifndef TOOL_H
#define TOOL_H

#include <QPoint>
#include <QColor>
#include <QImage>

/*Abstract Class*/
class Tool {


public:

    virtual void applyChange(QPoint currentPoint, QImage &currFrame,  QColor currentColor);

};
#endif // TOOL_H
