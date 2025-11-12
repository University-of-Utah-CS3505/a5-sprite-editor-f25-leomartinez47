#ifndef TOOLPANE_H
#define TOOLPANE_H

#include <QWidget>
#include <QSlider>
#include "tools.h"
#include "project.h"

namespace Ui {
class ToolPane;
}

class ToolPane : public QWidget
{
    Q_OBJECT

public:
    explicit ToolPane(Project *project, QWidget *parent = nullptr);
    ~ToolPane();
    void focusATool(QString tool);

    void redSliderValue(int value);
    void blueSliderValue(int value);
    void greenSliderValue(int value);
    void alphaSliderValue(int value);

signals:
    void toolSelected(Tool *tool);

    //emit to project
    void redSliderUpdate(int value);
    void greenSliderUpdate(int value);
    void blueSliderUpdate(int value);
    void alphaSliderUpdate(int value);

private slots:
    void onPencilSelected();
    void onEraserSelected();

private:
    Ui::ToolPane *ui;
};

#endif // TOOLPANE_H
