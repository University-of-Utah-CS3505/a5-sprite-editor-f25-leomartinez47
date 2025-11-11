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
    connect(ui->AddFrame, &QPushButton::clicked, project, [this, project]{ project->onFrameAdded(ui->listWidget->currentRow() + 1); });
    connect(ui->DeleteFrame, &QPushButton::clicked, project, [this, project]{ project->onFrameRemoved(ui->listWidget->currentRow()); });
    connect(ui->listWidget, &QListWidget::currentRowChanged, project, &Project::onCurrentFrameChanged);

    // Pane -> Project
    //connect(this, &FrameSelectionPane::addFrame, project, &Project::onFrameAdded);
    //connect(this, &FrameSelectionPane::deleteFrame, project, &Project::onFrameRemoved);

    // Project -> Pain
    //connect(project, &Project::frameListChanged, this, &FrameSelectionPane::setupQList);
    connect(project, &Project::frameAdded, this, &FrameSelectionPane::addFrame);
    connect(project, &Project::frameRemoved, this, &FrameSelectionPane::deleteFrame);
    connect(project, &Project::frameSelectionChanged, this, [this](int index){ui->listWidget->setCurrentRow(index);});
    connect(project, &Project::frameChanged, this, [this, project](const QImage& img){
        this->onUpdate(project->getCurrentFrameIndex(), img);
    });

    this->setupQList();
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

void FrameSelectionPane::setupQList() {
    ui->listWidget->clear();
    // TODO: My idea was to refresh the list every time the list is updated.
    //       But I realized that view doesn't have access to project, and therefore
    //       woudln't be able to access frameCount and frameAt
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
