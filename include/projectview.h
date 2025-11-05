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

class ProjectView : public QWidget
{
    Q_OBJECT

public:
    /// Create a new ProjectView, taking *ownership* over `project`.
    explicit ProjectView(Project *project, QWidget *parent = nullptr);
    ~ProjectView();

private:
    void embedWidget(QWidget *container, QWidget *child);

    Ui::ProjectView *ui;

    Project *project;

    ToolPane *toolPane;
    PreviewPane *previewPane;
    CanvasPane *canvasPane;
    FrameSelectionPane *frameSelectionPane;
};

#endif // PROJECTVIEW_H
