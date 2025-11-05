#include "toolpane.h"
#include "ui_toolpane.h"

ToolPane::ToolPane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolPane)
{
    ui->setupUi(this);
}

ToolPane::~ToolPane()
{
    delete ui;
}
