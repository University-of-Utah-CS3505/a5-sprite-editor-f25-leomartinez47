#ifndef PROJECTVIEW_H
#define PROJECTVIEW_H

#include <QWidget>

#include "toolpane.h"
#include "previewpane.h"
#include "canvaspane.h"
#include "frameselectionpane.h"


namespace Ui {
class ProjectView;
}

class ProjectView : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectView(QWidget *parent = nullptr);
    ~ProjectView();

private:
    void embedWidget(QWidget *container, QWidget *child);

    Ui::ProjectView *ui;

    ToolPane *toolPane;
    PreviewPane *previewPane;
    CanvasPane *canvasPane;
    FrameSelectionPane *frameSelectionPane;
};

#endif // PROJECTVIEW_H
