#ifndef TOOL_H
#define TOOL_H

#include <QPoint>
#include <QColor>
#include <QWidget>

/*Abstract Class*/
class Tool : public QWidget{

    Q_OBJECT

public:

    explicit Tool(QWidget *parent = nullptr);

    virtual void applyChange(QPoint currentPoint, QColor currentColor);

    virtual ~Tool();

};
#endif // TOOL_H
