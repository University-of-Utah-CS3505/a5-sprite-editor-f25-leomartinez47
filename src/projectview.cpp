#include "projectview.h"
#include "ui_projectview.h"

ProjectView::ProjectView(Project *project, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectView)
{
    this->ui->setupUi(this);

    this->project = project;
    // TODO: pass `project` into each pane constructor and set up signals there.

    this->toolPane = new ToolPane();
    this->embedWidget(this->ui->toolboxFrame, this->toolPane);

    this->previewPane = new PreviewPane();
    this->embedWidget(this->ui->previewFrame, this->previewPane);

    this->canvasPane = new CanvasPane();
    this->embedWidget(this->ui->canvasFrame, this->canvasPane);

    this->frameSelectionPane = new FrameSelectionPane();
    this->embedWidget(this->ui->frameSelectorFrame, this->frameSelectionPane);
}

ProjectView::~ProjectView()
{
    delete this->ui;
    delete this->project;
}

void ProjectView::embedWidget(QWidget *container, QWidget *child)
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(child);
    layout->setContentsMargins(0, 0, 0, 0);
    container->setLayout(layout);
}
