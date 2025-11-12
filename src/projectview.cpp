#include "projectview.h"
#include "ui_projectview.h"

#include <QTabWidget>

ProjectView::ProjectView(Project *project, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectView)
{
    this->ui->setupUi(this);

    this->project = project;

    connect(this->project, &Project::nameChanged,
            this, &ProjectView::handleModelNameChange);

    this->toolPane = new ToolPane();
    this->toolPane->focusATool(project->getCurrentTool().toString());
    this->embedWidget(this->ui->toolboxFrame, this->toolPane);
    connect(this->toolPane, &ToolPane::toolSelected,
            this->project, &Project::onToolChanged);

    // TODO : once it's set up, pass in currentFrameRate from project
    this->previewPane = new PreviewPane();
    this->embedWidget(this->ui->previewFrame, this->previewPane);

    this->canvasPane = new CanvasPane(project);
    this->embedWidget(this->ui->canvasFrame, this->canvasPane);

    this->frameSelectionPane = new FrameSelectionPane(project);
    this->embedWidget(this->ui->frameSelectorFrame, this->frameSelectionPane);

    // TODO : once colorPickerPane is implemented, pass in currentColor from project
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

Project *ProjectView::getProject()
{
    return this->project;
}

void ProjectView::handleModelNameChange(const QString& name)
{
    emit this->wantsTabTitleUpdate(this, name);
}
