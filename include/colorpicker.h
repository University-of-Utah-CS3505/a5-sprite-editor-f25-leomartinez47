#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QDialog>
#include <QColor>

class colorpicker : public QWidget
{

public:

    explicit colorpicker (QWidget* parent = nullptr);
    ~colorpicker();
    QColor color() const;

private:

    QColor currentColor;
};

#endif // COLORPICKER_H
