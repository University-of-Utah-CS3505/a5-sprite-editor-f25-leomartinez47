#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>
#include <QSlider>
#include <QLabel>

class colorpicker : public QWidget
{
    Q_OBJECT
    QSlider *red_slider, *green_slider, *blue_slider;

    QLabel *red_label, *green_label, *blue_label;

public:
    colorpicker(QWidget *parent = 0);
    ~colorpicker();


};

#endif // COLORPICKER_H
