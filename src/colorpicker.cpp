#include "colorpicker.h"

colorpicker::colorpicker(QWidget *parent)
    : QWidget(parent)
{
    red_slider = new QSlider(this);
    green_slider = new QSlider(this);
    blue_slider = new QSlider(this);

    this->setFixedWidth(400);
    this->setFixedHeight(300);

    red_slider->setRange(0,255);
    blue_slider->setRange(0,255);
    green_slider->setRange(0,255);

    red_slider->setOrientation(Qt::Vertical);
    blue_slider->setOrientation(Qt::Vertical);
    green_slider->setOrientation(Qt::Vertical);


    red_slider->move(5,5);

    red_slider->setValue(5);



}

colorpicker::~colorpicker(){

}
