#include "toolpane.h"
#include "ui_toolpane.h"

ToolPane::ToolPane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolPane)
{
    ui->setupUi(this);
    ui->pencilButton->setFocus();

    ui->pencilButton->setIcon(QIcon(":/icons/pencil.png"));
    qDebug() << ui->pencilButton->size();
    ui->pencilButton->setIconSize(ui->pencilButton->size());
    ui->eraserButton->setIcon(QIcon(":/icons/eraser.png"));
    ui->eraserButton->setIconSize(ui->eraserButton->size());


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
    this->ui->pencilButton->setDefault(true);

    this->ui->eraserButton->setDefault(false);
    this->ui->fillButton->setDefault(false);
    emit this->toolSelected(new Pencil());
}

void ToolPane::onEraserSelected()
{
    this->ui->eraserButton->setDefault(true);

    this->ui->pencilButton->setDefault(false);
    this->ui->fillButton->setDefault(false);
    emit this->toolSelected(new Eraser());
}

void ToolPane::onFillSelected()
{
    this->ui->fillButton->setDefault(true);

    this->ui->pencilButton->setDefault(false);
    this->ui->eraserButton->setDefault(false);
}

void ToolPane::focusATool(QString tool)
{
    qDebug() << tool;
    if(tool == "Pencil"){
        this->ui->pencilButton->setDefault(true);
    }
    else{
        this->ui->eraserButton->setDefault(true);
    }
}
