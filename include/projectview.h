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
    /// Project view must always be in a QTabWidget.
    explicit ProjectView(Project *project, QWidget *parent = nullptr);
    ~ProjectView();
    Project *getProject();

signals:
    void wantsTabTitleUpdate(QWidget* sender, const QString& newTitle);

private slots:
    void handleModelNameChange(const QString &name);

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
