#ifndef TOOL_H
#define TOOL_H

#include <QPoint>
#include <QColor>
#include <QObject>

/*Abstract Class*/
class Tool : public QObject{

    Q_OBJECT

public:

    explicit Tool(QObject *parent = nullptr);

    virtual void applyChange(QPoint currentPoint, QColor currentColor);

    virtual ~Tool();

};
#endif // TOOL_H
