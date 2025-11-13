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

    this->focusATool(project->getCurrentTool().toString());
    connect(this, &ToolPane::toolSelected,
            project, &Project::onToolChanged);

    /*Connects the slider changes to the methods that get the
    *value from the slider and send them to the project to
    *update the color*/
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
    if(tool == "Pencil"){
        this->ui->pencilButton->setFocus();
    }
    else{
        this->ui->eraserButton->setFocus();
    }
}
