#ifndef TOOLPANE_H
#define TOOLPANE_H

#include <QWidget>
#include <QSlider>
#include "tools.h"
#include "project.h"

namespace Ui {
class ToolPane;
}

const QSize ICON_SIZE = QSize(65, 32);
class ToolPane : public QWidget
{
    Q_OBJECT

public:
    explicit ToolPane(Project *project, QWidget *parent = nullptr);
    ~ToolPane();

    /*!
     * \brief redSliderValue
     * \param value
     */
    void redSliderValue(int value);

    /*!
     * \brief blueSliderValue
     * \param value
     */
    void blueSliderValue(int value);

    /*!
     * \brief greenSliderValue
     * \param value
     */
    void greenSliderValue(int value);

    /*!
     * \brief alphaSliderValue
     * \param value
     */
    void alphaSliderValue(int value);

signals:
    void toolSelected(Tool *tool);

    /*!
     * \brief redSliderUpdate is signal for Project's redChanged
     * \param value is the integer sent to Project to update
     * the red RBG.
     */
    void redSliderUpdate(int value);

    /*!
     * \brief greenSliderUpdate redSliderUpdate is signal for Project's greenChanged
     * \param value is the integer sent to Project to update
     * the green RBG.
     */
    void greenSliderUpdate(int value);

    /*!
     * \brief blueSliderUpdate redSliderUpdate is signal for Project's blueChanged
     * \param value is the integer sent to Project to update
     * the blue RBG.
     */
    void blueSliderUpdate(int value);

    /*!
     * \brief alphaSliderUpdate redSliderUpdate is signal for Project's opacityChanged
     * \param value is the integer sent to Project to update
     * the blue RBG.
     */
    void alphaSliderUpdate(int value);
public slots:
    void receiveColor(QColor);
    void receiveOpacity(int opacity);

private slots:
    void onPencilSelected();
    void onEraserSelected();
    void onFillSelected();
    void onToolSelected(Tool *tool);

private:
    Ui::ToolPane *ui;
};

#endif // TOOLPANE_H
