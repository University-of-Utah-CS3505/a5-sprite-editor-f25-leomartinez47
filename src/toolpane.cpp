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

    //Connects the slider changes to the methods that get the
    //value from the slider and send them to the project to
    //update the color.
    connect(this->ui->redSlider, &QAbstractSlider::valueChanged,
            project, &Project::redChanged);

    connect(this->ui->greenSlider, &QAbstractSlider::valueChanged,
            project, &Project::greenChanged);

    connect(this->ui->blueSlider, &QAbstractSlider::valueChanged,
            project, &Project::blueChanged);

    connect(this->ui->opacitySlider, &QAbstractSlider::valueChanged,
            project, &Project::alphaChanged);
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
