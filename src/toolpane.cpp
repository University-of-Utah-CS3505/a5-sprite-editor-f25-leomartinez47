#include "toolpane.h"
#include "ui_toolpane.h"

ToolPane::ToolPane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolPane)
{
    ui->setupUi(this);
    ui->pencilButton->setIcon(QIcon(":/icons/pencil.png"));
    qDebug() << ui->pencilButton->size();
    ui->pencilButton->setIconSize(ui->pencilButton->size());
    ui->eraserButton->setIcon(QIcon(":/icons/eraser.png"));
    ui->eraserButton->setIconSize(ui->eraserButton->size());


    connect(this->ui->pencilButton, &QPushButton::clicked,
            this, &ToolPane::onPencilSelected);
    connect(this->ui->eraserButton, &QPushButton::clicked,
            this, &ToolPane::onEraserSelected);
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

void ToolPane::focusATool(QString tool)
{
    qDebug() << tool;
    if(tool == "Pencil"){
        this->ui->pencilButton->setFocus();
        qDebug() << "focus was set to pencil";
    }
    else{
        this->ui->eraserButton->setFocus();
        qDebug() << "focus was set to eraser";
    }
}
