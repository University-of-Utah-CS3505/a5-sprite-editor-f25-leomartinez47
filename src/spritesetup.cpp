/*
    Contributors: Grant Handy
    Date: 11/13/2025
*/

#include "spritesetup.h"
#include "ui_spritesetup.h"

SpriteSetup::SpriteSetup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SpriteSetup)
{
    ui->setupUi(this);

    connect(this->ui->createButton, &QPushButton::clicked,
            this, &SpriteSetup::onCreateProject);
}

SpriteSetup::~SpriteSetup()
{
    delete ui;
}

void SpriteSetup::onCreateProject()
{
    QSize size = QSize(this->ui->widthSpinBox->value(), this->ui->heightSpinBox->value());
    emit this->setupFinished(this, new Project(size));
}
