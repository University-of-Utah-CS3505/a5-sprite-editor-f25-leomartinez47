#include "toolpane.h"
#include "ui_toolpane.h"

#include "tools.h"

ToolPane::ToolPane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolPane)
{
    this->ui->setupUi(this);
    this->ui->pencilButton->setIcon(QIcon(":/icons/pencil.png"));
    this->ui->pencilButton->setIconSize(this->ui->pencilButton->size());

    this->ui->eraserButton->setIcon(QIcon(":/icons/eraser.png"));
    this->ui->eraserButton->setIconSize(this->ui->eraserButton->size());

    connect(this->ui->pencilButton, &QPushButton::clicked,
            this, &ToolPane::onPencilSelected);
    connect(this->ui->eraserButton, &QPushButton::clicked,
            this, &ToolPane::onEraserSelected);
    connect(this->ui->fillButton, &QPushButton::clicked,
            this, &ToolPane::onFillSelected);
}

ToolPane::~ToolPane()
{
    delete ui;
}

void ToolPane::onPencilSelected()
{
    this->ui->pencilButton->setFocus();
    emit this->toolSelected(new Pencil());
}

void ToolPane::onEraserSelected()
{
    this->ui->eraserButton->setFocus();
    emit this->toolSelected(new Eraser());
}

void ToolPane::onFillSelected()
{
    this->ui->fillButton->setFocus();
    emit this->toolSelected(new FillBucket());
}

void ToolPane::focusATool(const QString &tool)
{
    if (tool == PENCIL) {
        this->ui->pencilButton->setFocus();
    } else if (tool == ERASER) {
        this->ui->eraserButton->setFocus();
    } else if (tool == FILL_BUCKET) {
        this->ui->fillButton->setFocus();
    }

    qDebug() << "focus was set to" << tool;
}
