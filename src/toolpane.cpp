#include "toolpane.h"
#include "ui_toolpane.h"

#include "tools.h"

ToolPane::ToolPane(Project *project, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolPane)
{
    this->ui->setupUi(this);

    // Initialize the current tool.
    this->onToolSelected(&project->getCurrentTool());

    connect(this, &ToolPane::toolSelected,
            project, &Project::onToolChanged);

    connect(this, &ToolPane::toolSelected,
            this, &ToolPane::onToolSelected);

    this->ui->pencilButton->setIcon(QIcon(":/icons/pencil.png"));
    this->ui->pencilButton->setIconSize(this->ui->pencilButton->size());

    connect(this->ui->pencilButton, &QPushButton::clicked,
            this, &ToolPane::onPencilSelected);

    this->ui->eraserButton->setIcon(QIcon(":/icons/eraser.png"));
    this->ui->eraserButton->setIconSize(this->ui->eraserButton->size());

    connect(this->ui->eraserButton, &QPushButton::clicked,
            this, &ToolPane::onEraserSelected);

    this->ui->fillButton->setIcon(QIcon(":/icons/fillbucket.png"));
    this->ui->fillButton->setIconSize(this->ui->fillButton->size());

    connect(this->ui->fillButton, &QPushButton::clicked,
            this, &ToolPane::onFillSelected);
}

ToolPane::~ToolPane()
{
    delete ui;
}

void ToolPane::onPencilSelected()
{
    emit this->toolSelected(new Pencil());
}

void ToolPane::onEraserSelected()
{
    emit this->toolSelected(new Eraser());
}

void ToolPane::onFillSelected()
{
    emit this->toolSelected(new FillBucket());
}

void ToolPane::onToolSelected(Tool *tool)
{
    this->ui->pencilButton->setDisabled(false);
    this->ui->eraserButton->setDisabled(false);
    this->ui->fillButton->setDisabled(false);

    const QString tool_str = tool->toString();

    if (tool_str == PENCIL) {
        this->ui->pencilButton->setDisabled(true);
    } else if (tool_str == ERASER) {
        this->ui->eraserButton->setDisabled(true);
    } else if (tool_str == FILL_BUCKET) {
        this->ui->fillButton->setDisabled(true);
    }

    qDebug() << "focus set to" << tool_str;
}
