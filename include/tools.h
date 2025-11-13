/*
    Contributors: Natalie Bonilla, Grant Handy, and Kailee Kim
    Date: 11/13/2025
*/

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
    ///
    /// @brief The destructor for Tool.
    ///
    virtual ~Tool() = default;

    ///
    /// @brief Apply a color to a given point in a QImage.
    /// @param point - A point in the QImage.
    /// @param frame - The QImage to color.
    /// @param color - Color to be applied.
    ///
    virtual void apply(QPoint point, QImage &frame,  QColor color) = 0;

    ///
    /// @brief Format a Tool as a QString.
    /// @return The QString.
    ///
    virtual const QString &toString() const = 0;
};

///
/// @brief Create a new Tool from its string representation.
/// @param val - QString used to determine type of Tool to create.
/// @return A Tool object.
///
Tool *toolFromString(const QString &val);

/// Sets the color to the current color to be applied to the current frames pixel point.
class Pencil : public Tool {
public:   
    ///
    /// @brief Apply a color to a given point in a QImage.
    /// @param point - A point in the QImage.
    /// @param frame - The QImage to color.
    /// @param color - Color to be applied.
    ///
    void apply(QPoint point, QImage &frame, QColor color) override;

    ///
    /// @brief Format a Pencil as a QString.
    /// @return The QString.
    ///
    const QString &toString() const override { return PENCIL; }
};

/// Sets the color to white to be applied to the current frames pixel point.
class Eraser : public Tool {
public:
    ///
    /// @brief Make a given point in a QImage completely transparent.
    /// @param point - A point in the QImage.
    /// @param frame - The QImage to color.
    /// @param color - Unused parameter.
    ///
    void apply(QPoint point, QImage &frame, QColor color) override;

    ///
    /// @brief Format Eraser as a QString.
    /// @return The QString.
    ///
    const QString &toString() const override  { return ERASER; }
};

/// Fills all the adjacent space around the given point with the color.
class FillBucket : public Tool {
  public:
    ///
    /// @brief Apply a color to adjacent space around a given point in a QImage.
    /// @param point - A point in the QImage.
    /// @param frame - The QImage to color.
    /// @param color - Color to be applied.
    ///
    void apply(QPoint point, QImage &frame, QColor color) override;

    ///
    /// @brief Format a FillBucket as a QString.
    /// @return The QString.
    ///
    const QString &toString() const override { return FILL_BUCKET; }
};

#endif // TOOLS_H
