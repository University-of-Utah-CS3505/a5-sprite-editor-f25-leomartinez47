#ifndef ERASER_H
#define ERASER_H

#include <QPoint>
#include <QColor>
#include "pencil.h"
#include <QWidget>

namespace Ui {
class Eraser;
}

class Eraser : public Pencil
{
    Q_OBJECT

public:

    explicit Eraser(QWidget *parent = nullptr);

    void drawPoint(QPoint currentPoint, QColor currentColor);

    void applyChange(QPoint currentPoint, QColor currentColor);

    ~Eraser();

private:
    Ui::Eraser *ui;

    Tool currentTool;
};

#endif // ERASER_H
