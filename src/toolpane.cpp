/*
    Contributors: Natalie Bonilla, Grant Handy, and Kailee Kim
    Date: 11/13/2025
*/

#include "toolpane.h"

#include "tools.h"
#include "ui_toolpane.h"

ToolPane::ToolPane(Project *project, QWidget *parent)
    : QWidget(parent), ui(new Ui::ToolPane) {
    this->ui->setupUi(this);

    // Initialize the current tool.
    this->onToolSelected(&project->getCurrentTool());

    this->receivedColor(project->getCurrentColor());

    this->ui->redSlider->setValue(project->getCurrentColor().red());
    this->ui->blueSlider->setValue(project->getCurrentColor().blue());
    this->ui->greenSlider->setValue(project->getCurrentColor().green());
    this->ui->opacitySlider->setValue(project->getCurrentColor().alpha());

    connect(this, &ToolPane::toolSelected, project, &Project::onToolChanged);

    connect(this, &ToolPane::toolSelected, this, &ToolPane::onToolSelected);

    this->ui->pencilButton->setIcon(QIcon(":/icons/pencil.png"));
    this->ui->pencilButton->setIconSize(ICON_SIZE);

    connect(this->ui->pencilButton, &QPushButton::clicked, this,
            &ToolPane::onPencilSelected);

    this->ui->eraserButton->setIcon(QIcon(":/icons/eraser.png"));
    this->ui->eraserButton->setIconSize(ICON_SIZE);

    connect(this->ui->eraserButton, &QPushButton::clicked, this,
            &ToolPane::onEraserSelected);

    this->ui->fillButton->setIcon(QIcon(":/icons/fillbucket.png"));
    this->ui->fillButton->setIconSize(ICON_SIZE);

    connect(this->ui->fillButton, &QPushButton::clicked, this,
            &ToolPane::onFillSelected);

    connect(this->ui->redSlider, &QAbstractSlider::valueChanged, project,
            &Project::onRedChanged);

    connect(this->ui->greenSlider, &QAbstractSlider::valueChanged, project,
            &Project::onGreenChanged);

    connect(this->ui->blueSlider, &QAbstractSlider::valueChanged, project,
            &Project::onBlueChanged);

    connect(this->ui->opacitySlider, &QAbstractSlider::valueChanged, project,
            &Project::onAlphaChanged);

    connect(project, &Project::sendColor, this, &ToolPane::receivedColor);
}

ToolPane::~ToolPane() {
    delete this->ui;
}

void ToolPane::onPencilSelected() {
    emit this->toolSelected(new Pencil());
}

void ToolPane::onEraserSelected() {
    emit this->toolSelected(new Eraser());
}

void ToolPane::onFillSelected() {
    emit this->toolSelected(new FillBucket());
}

void ToolPane::onToolSelected(Tool *tool) {
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

void ToolPane::receivedColor(QColor color) {
    QString styleSheet =
        "background-color: rgba(" + QString::number(color.red()) + "," +
        QString::number(color.green()) + "," + QString::number(color.blue()) +
        "," + QString::number(color.alpha()) + ")";
    this->ui->colorPreview->setStyleSheet(styleSheet);
}
