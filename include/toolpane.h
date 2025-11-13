/*
    Contributors: Natalie Bonilla, Grant Handy, and Kailee Kim
    Date: 11/13/2025
*/

#ifndef TOOLPANE_H
#define TOOLPANE_H

#include <QWidget>

#include "tools.h"
#include "project.h"

namespace Ui {
class ToolPane;
}

const QSize ICON_SIZE = QSize(65, 32);

/// The ToolPane displays Sprite editing tools.
class ToolPane : public QWidget
{
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

signals:

    ///
    /// @brief Emit when tool is selected.
    /// @param tool - The tool selected by the user.
    ///
    void toolSelected(Tool *tool);

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

#endif // TOOLPANE_H
