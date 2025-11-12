#include "toolpane.h"
#include "ui_toolpane.h"

ToolPane::ToolPane(Project *project, QWidget *parent)
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

    //qslider connections here that go to view
    //sample for the connections for the sliders
    this->focusATool(project->getCurrentTool().toString());
    connect(this, &ToolPane::toolSelected,
            project, &Project::onToolChanged);

    //connect slider changes to the methods in this class
    //all in here
    connect(this->ui->redSlider, &QSlider::valueChanged,
            this, &ToolPane::redSliderValue);

    connect(this->ui->blueSlider, &QSlider::valueChanged,
            this, &ToolPane::blueSliderValue);

    connect(this->ui->greenSlider, &QSlider::valueChanged,
            this, &ToolPane::greenSliderValue);

    connect(this->ui->opacitySlider, &QSlider::valueChanged,
            this, &ToolPane::alphaSliderValue);
}

ToolPane::~ToolPane()
{
    delete ui;
}

void ToolPane::onPencilSelected()
{
    qDebug() << "Pencil";
    this->ui->pencilButton->setFocus();
    emit this->toolSelected(new Pencil());
}

void ToolPane::onEraserSelected()
{
    qDebug() << "Eraser";
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

void ToolPane::redSliderValue(int value){
    qDebug() << value;
    emit this->redSliderUpdate(value);
}

void ToolPane::blueSliderValue(int value){
    qDebug() << value;
    emit this->blueSliderUpdate(value);
}

void ToolPane::greenSliderValue(int value){
    qDebug() << value;
    emit this->greenSliderUpdate(value);
}

void ToolPane::alphaSliderValue(int value){
    qDebug() << value;
    emit this->alphaSliderUpdate(value);
}
