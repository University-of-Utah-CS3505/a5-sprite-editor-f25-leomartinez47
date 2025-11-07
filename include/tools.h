#ifndef TOOLS_H
#define TOOLS_H

#include <QPoint>
#include <QColor>
#include <QImage>

/// The general interface for various tools.
class Tool {
public:
    virtual ~Tool() = default;
    virtual void apply(QPoint point, QImage &frame,  QColor color) = 0;
};

/// Sets the color to the current color to be applied to the current frames pixel point.
class Pencil : public Tool {
public:
    void apply(QPoint point, QImage &frame, QColor color) override;
};

/// Sets the color to white to be applied to the current frames pixel point.
class Eraser : public Tool {
public:
    void apply(QPoint point, QImage &frame, QColor color) override;
};

#endif // TOOLS_H
