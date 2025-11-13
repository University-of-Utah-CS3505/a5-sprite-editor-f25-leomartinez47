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
    this->ui->pencilButton->setIconSize(ICON_SIZE);

    connect(this->ui->pencilButton, &QPushButton::clicked,
            this, &ToolPane::onPencilSelected);

    this->ui->eraserButton->setIcon(QIcon(":/icons/eraser.png"));
    this->ui->eraserButton->setIconSize(ICON_SIZE);

    connect(this->ui->eraserButton, &QPushButton::clicked,
            this, &ToolPane::onEraserSelected);

    this->ui->fillButton->setIcon(QIcon(":/icons/fillbucket.png"));
    this->ui->fillButton->setIconSize(ICON_SIZE);

    connect(this->ui->fillButton, &QPushButton::clicked,
            this, &ToolPane::onFillSelected);

    connect(this->ui->redSlider, &QAbstractSlider::valueChanged,
            project, &Project::redChanged);

    connect(this->ui->greenSlider, &QAbstractSlider::valueChanged,
            project, &Project::greenChanged);

    connect(this->ui->blueSlider, &QAbstractSlider::valueChanged,
            project, &Project::blueChanged);

    connect(this->ui->opacitySlider, &QAbstractSlider::valueChanged,
            project, &Project::alphaChanged);

    connect(project, &Project::sendColor,
            this, &ToolPane::receiveColor);

    connect(project, &Project::sendOpacity,
            this, &ToolPane::receiveOpacity);
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
}

void ToolPane::receiveColor(QColor color)
{
    this->ui->colorPreview->setStyleSheet(QString("background-color: %1;").arg(color.name()));
}

void ToolPane::receiveOpacity(int opacity)
{
    this->ui->opacityPreview->setStyleSheet(QString("background-color: rgba(255, 255, 255, %1);")
                                                .arg(opacity));
}
