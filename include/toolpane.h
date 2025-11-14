/*
    Contributors: Natalie Bonilla, Grant Handy, and Kailee Kim
    Date: 11/13/2025
*/

#ifndef TOOLPANE_H
#define TOOLPANE_H

#include <QSlider>
#include <QWidget>

#include "project.h"
#include "tools.h"

namespace Ui {
class ToolPane;
}

const QSize ICON_SIZE = QSize(65, 32);

/// The ToolPane displays Sprite editing tools.
class ToolPane : public QWidget {
    Q_OBJECT

  public:
    ///
    /// @brief Construct a ToolPane.
    /// @param project - Model for the Sprite Editor.
    /// @param parent
    ///
    explicit ToolPane(Project *project, QWidget *parent = nullptr);

    ///
    /// @brief Destructor for ToolPane.
    ///
    ~ToolPane();

    ///
    /// @brief redSliderValue
    /// @param value
    ///
    void redSliderValue(int value);

    ///
    /// @brief blueSliderValue
    /// @param value
    ///
    void blueSliderValue(int value);

    ///
    /// @brief greenSliderValue
    /// @param value
    ///
    void greenSliderValue(int value);

    ///
    /// @brief alphaSliderValue
    /// @param value
    ///
    void alphaSliderValue(int value);

  signals:

    ///
    /// @brief Emit when tool is selected.
    /// @param tool - The tool selected by the user.
    ///
    void toolSelected(Tool *tool);

    ///
    /// @brief redSliderUpdate is signal for Project's redChanged
    /// @param value is the integer sent to Project to update
    /// the red RBG.
    ///
    void redSliderUpdate(int value);

    ///
    /// @brief greenSliderUpdate redSliderUpdate is signal for Project's
    /// greenChanged
    /// @param value is the integer sent to Project to update
    /// the green RBG.
    ///
    void greenSliderUpdate(int value);

    ///
    /// @brief blueSliderUpdate redSliderUpdate is signal for Project's
    /// blueChanged
    /// @param value is the integer sent to Project to update
    /// the blue RBG.
    ///
    void blueSliderUpdate(int value);

    ///
    /// @brief alphaSliderUpdate redSliderUpdate is signal for Project's
    /// opacityChanged
    /// @param value is the integer sent to Project to update
    /// the blue RBG.
    ///
    void alphaSliderUpdate(int value);
  public slots:
    ///
    /// @brief Update the current color preview.
    /// @param color - The new color.
    ///
    void receivedColor(QColor color);

  private slots:
    ///
    /// @brief Tell the model the selected tool is a Pencil.
    ///
    void onPencilSelected();

    ///
    /// @brief Tell the model the selected tool is an Eraser.
    ///
    void onEraserSelected();

    ///
    /// @brief Tell the model the selected tool is a FillBucket.
    ///
    void onFillSelected();

    ///
    /// @brief Indicate the selected tool in the display.
    /// @param tool - The currently selected tool.
    ///
    void onToolSelected(Tool *tool);

  private:
    Ui::ToolPane *ui;
};

#endif
