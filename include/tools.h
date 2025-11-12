#ifndef TOOLS_H
#define TOOLS_H

#include <QPoint>
#include <QColor>
#include <QImage>


const QString PENCIL = "pencil";
const QString FILL_BUCKET = "fillbucket";
const QString ERASER = "eraser";

/// The general interface for various tools.
class Tool {
public:
    virtual ~Tool() = default;
    virtual void apply(QPoint point, QImage &frame,  QColor color) = 0;
    virtual const QString &toString() const = 0;
};

/// Create a new tool from its string representation.
Tool *toolFromString(const QString &val);

/// Sets the color to the current color to be applied to the current frames pixel point.
class Pencil : public Tool {
public:
    void apply(QPoint point, QImage &frame, QColor color) override;
    const QString &toString() const override { return PENCIL; }
};

/// Sets the color to white to be applied to the current frames pixel point.
class Eraser : public Tool {
public:
    void apply(QPoint point, QImage &frame, QColor color) override;
    const QString &toString() const override  { return ERASER; }
};

/// Fills all the adjacent space around the given point with the color.
class FillBucket : public Tool {
  public:
    void apply(QPoint point, QImage &frame, QColor color) override;
    const QString &toString() const override { return FILL_BUCKET; }
};

#endif // TOOLS_H
