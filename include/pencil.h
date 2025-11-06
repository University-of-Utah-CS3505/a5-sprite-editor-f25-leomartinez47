#ifndef PENCIL_H
#define PENCIL_H

#include <QPoint>
#include <QColor>
#include "tool.h"
#include <QWidget>

namespace Ui {
class Pencil;
}

class Pencil : public Tool
{
    Q_OBJECT

public:

    explicit Pencil(QWidget *parent = nullptr);

    void drawPoint(QPoint currentPoint, QColor currentColor);

    void applyChange(QPoint currentPoint, QColor currentColor);

    ~Pencil();

private:
    Ui::Pencil *ui;

    Tool currentTool;
};

#endif // PENCIL_H
