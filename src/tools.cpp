/*
    Contributors: Natalie Bonilla, Grant Handy, and Kailee Kim
    Date: 11/13/2025
*/

#include <QQueue>

#include "tools.h"

void setPixel(QPoint point, QImage &frame, QColor color)
{
    if (frame.valid(point)) {
        frame.setPixelColor(point, color);
    }
}

Tool *toolFromString(const QString &val) {
    if (val == PENCIL) {
        return new Pencil();
    } else if (val == ERASER) {
        return new Eraser();
    } else if (val == FILL_BUCKET) {
        return new FillBucket();
    }

    // TODO: throw and catch exceptions.
    return nullptr;
}

void Pencil::apply(QPoint point, QImage &frame,  QColor color)
{
    setPixel(point, frame, color);
}

void Eraser::apply(QPoint point, QImage &frame,  QColor /* color unused */)
{
    setPixel(point, frame, Qt::transparent);
}

// This is the AI feature.
void FillBucket::apply(QPoint point, QImage &frame, QColor color)
{
    // 1. Check if the starting point is valid
    if (!frame.valid(point)) {
        return;
    }

    // 2. Get the color we need to replace
    const QColor targetColor = frame.pixelColor(point);

    // 3.Get the color to fill with (the "replacement" color)
    const QColor replacementColor = color;

    //4. If the target and replacement are the same, no work is needed.
    if (targetColor == replacementColor) {
        return;
    }

    // 5. Get image dimensions for boundary checking
    const int width = frame.width();
    const int height = frame.height();

    // 6. Set up the queue for our breadth-first-search
    QQueue<QPoint> queue;
    queue.enqueue(point);

    // 7. Process the queue until it's empty
    while (!queue.isEmpty()) {
        // Get the next point to process
        QPoint p = queue.dequeue();

        // 8.Basic bounds check
        if (p.x() < 0 || p.x() >= width || p.y() < 0 || p.y() >= height) {
            continue; // This point is off the image
        }

        // 9. Check if this pixel has the color we're trying to replace
        if (frame.pixelColor(p) != targetColor) {
            continue; // Not the target color, so we don't fill or spread from here
        }

        // 10. It's the right color and in bounds. Change it!
        frame.setPixelColor(p, replacementColor);

        // 11. Add its four neighbors to the queue to be checked
        queue.enqueue(QPoint(p.x() + 1, p.y())); // East
        queue.enqueue(QPoint(p.x() - 1, p.y())); // West
        queue.enqueue(QPoint(p.x(), p.y() + 1)); // South
        queue.enqueue(QPoint(p.x(), p.y() - 1)); // North
    }
}

