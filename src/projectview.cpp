#include "projectview.h"
#include "ui_projectview.h"

ProjectView::ProjectView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectView)
{
    ui->setupUi(this);
}

ProjectView::~ProjectView()
{
    delete ui;
}
