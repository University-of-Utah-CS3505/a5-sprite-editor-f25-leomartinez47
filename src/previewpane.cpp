#include "previewpane.h"
#include "ui_previewpane.h"

PreviewPane::PreviewPane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PreviewPane)
{
    ui->setupUi(this);
}

PreviewPane::~PreviewPane()
{
    delete ui;
}
