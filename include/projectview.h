/*
    Contributors: Grant Handy
    Date: 11/13/2025
*/

#ifndef PROJECTVIEW_H
#define PROJECTVIEW_H

#include <QWidget>

#include "toolpane.h"
#include "previewpane.h"
#include "canvaspane.h"
#include "frameselectionpane.h"
#include "project.h"

namespace Ui {
class ProjectView;
}

/// The ProjectView represents the view of a project Sprite Editor program. ProjectView must always be in a QTabWidget.
class ProjectView : public QWidget
{
    Q_OBJECT

public:
    ///
    /// @brief Construct a new ProjectView, taking *ownership* over `project`.
    /// @param project - The model for the Sprite Editor.
    /// @param parent
    ///
    explicit ProjectView(Project *project, QWidget *parent = nullptr);

    ///
    /// @brief Destructor for ProjectView.
    ///
    ~ProjectView();

    ///
    /// @brief Get the project associated with this view.
    /// @return The project.
    ///
    Project *getProject();

signals:
    ///
    /// @brief Emit when tab title of this view's QTabWidget needs to be updated.
    /// @param sender - The sender of this signal. In this case, sender is always
    /// an instance of ProjectView.
    /// @param newTitle - The new title of the tab.
    ///
    void wantsTabTitleUpdate(QWidget* sender, const QString& newTitle);

private slots:
    ///
    /// @brief Update the tab name when the model name has changed.
    /// @param name - The new name.
    ///
    void handleModelNameChange(const QString &name);

private:
    ///
    /// @brief Embeds a widget in a container.
    /// @param container - The container.
    /// @param child - The widget to embed.
    ///
    void embedWidget(QWidget *container, QWidget *child);

    Ui::ProjectView *ui;

    /// The model for the Sprite Editor.
    Project *project;

    /// Displays the Sprite Editor tools.
    ToolPane *toolPane;

    /// Displays a preview of the Sprite's animation cycle.
    PreviewPane *previewPane;

    /// Sprite editing pane.
    CanvasPane *canvasPane;

    /// Displays the frames of the Sprite and enables user to add, delete,
    /// and select frames.
    FrameSelectionPane *frameSelectionPane;
};

#endif
