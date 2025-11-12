#include "frameselectionpane.h"
#include "project.h"
#include "ui_frameselectionpane.h"
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPainter>

FrameSelectionPane::FrameSelectionPane(Project *project, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrameSelectionPane)
{
    ui->setupUi(this);

    // Buttons -> code // TODO: have buttons emit signals instead and connect signals to project slots in mainWindow (more in commit msg)
    connect(ui->AddFrame, &QPushButton::clicked, this, &FrameSelectionPane::buttonAdd);
    connect(ui->DeleteFrame, &QPushButton::clicked, this, &FrameSelectionPane::buttonDelete);
    connect(ui->listWidget, &QListWidget::currentRowChanged, project, &Project::onCurrentFrameChanged);

    // Pane -> Project
    connect(this, &FrameSelectionPane::frameAdded, project, &Project::onFrameAdded);
    connect(this, &FrameSelectionPane::frameDeleted, project, &Project::onFrameRemoved);

    // Project -> Pane
    //connect(project, &Project::frameListChanged, this, &FrameSelectionPane::setupQList);
    connect(project, &Project::frameAdded, this, &FrameSelectionPane::addFrame);
    connect(project, &Project::frameRemoved, this, &FrameSelectionPane::deleteFrame);
    connect(project, &Project::frameSelectionChanged, this, [this](int index){ui->listWidget->setCurrentRow(index);});
    connect(project, &Project::frameChanged, this, [this, project](const QImage& img){
        this->onUpdate(project->getCurrentFrameIndex(), img);
    });
    connect(project, &Project::initialFrames, this, &FrameSelectionPane::setupQList);
}

FrameSelectionPane::~FrameSelectionPane() {
    delete ui;
}

void FrameSelectionPane::addFrame(int index) {
    auto* item = new QListWidgetItem();
    ui->listWidget->insertItem(index, item);
}

void FrameSelectionPane::deleteFrame(int index) {
    ui->listWidget->takeItem(index);
}

void FrameSelectionPane::onUpdate(int index, const QImage &img) {
    if (auto* item = ui->listWidget->item(index))
        item->setIcon(QIcon(makeIcon(img)));
}

void FrameSelectionPane::setupQList(std::vector<QImage> frames) {
    ui->listWidget->clear();
    for (int i = 0; i < static_cast<int>(frames.size()); i++){
        addFrame(i);
        onUpdate(i, frames[i]);
    }
}

// Temporary checkerboard
QPixmap FrameSelectionPane::makeIcon(const QImage &img) {
    const int S = 64;
    QPixmap pm(S, S);
    pm.fill(Qt::transparent);
    QPainter p(&pm);
    p.setRenderHint(QPainter::SmoothPixmapTransform, false);

    // checkerboard
    const int tile = 8;
    for (int y = 0; y < S; y += tile)
        for (int x = 0; x < S; x += tile)
            p.fillRect(x, y, tile, tile, ((x/tile + y/tile) & 1) ? QColor(200,200,200) : QColor(240,240,240));

    // sprite scaled, centered
    QImage scaled = img.scaled(S, S, Qt::KeepAspectRatio, Qt::FastTransformation);
    p.drawImage(QPoint((S - scaled.width())/2, (S - scaled.height())/2), scaled);
    return pm;
}

void FrameSelectionPane::buttonAdd() {
    emit frameAdded(ui->listWidget->currentRow() + 1);
}

void FrameSelectionPane::buttonDelete(){
    emit frameDeleted(ui->listWidget->currentRow());
}
