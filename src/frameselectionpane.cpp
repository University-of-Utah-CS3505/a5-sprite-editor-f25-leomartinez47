#include "frameselectionpane.h"
#include "project.h"
#include "qevent.h"
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
    proj = project;

    // Set up list style
    auto* list = ui->listWidget;
    list->setViewMode(QListView::IconMode);
    list->setMovement(QListView::Static);
    list->setWrapping(false);
    list->setResizeMode(QListView::Adjust);
    list->setIconSize(QSize(95, 95));
    list ->setGridSize(QSize(105, 105));

    list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Buttons -> code // TODO: have buttons emit signals instead and connect signals to project slots in mainWindow (more in commit msg)
    connect(ui->AddFrame, &QPushButton::clicked, this, &FrameSelectionPane::buttonAdd);
    connect(ui->DeleteFrame, &QPushButton::clicked, this, &FrameSelectionPane::buttonDelete);
    connect(ui->listWidget, &QListWidget::currentRowChanged, project, &Project::onCurrentFrameChanged);

    // Pane -> Project
    connect(this, &FrameSelectionPane::frameAdded, project, &Project::onFrameAdded);
    connect(this, &FrameSelectionPane::frameDeleted, project, &Project::onFrameRemoved);
    connect(this, &FrameSelectionPane::requestInitialImages, project, &Project::sendInitialImages);

    // Project -> Pane
    connect(project, &Project::frameAdded, this, &FrameSelectionPane::addFrame);
    connect(project, &Project::frameRemoved, this, &FrameSelectionPane::deleteFrame);
    connect(project, &Project::frameSelectionChanged, this, [this, project](int index) {
        if (lastSelectedIndex >= 0) {
            this->onUpdate(lastSelectedIndex, project->frameAt(lastSelectedIndex));
        }
        this->onUpdate(index, project->frameAt(index));
        ui->listWidget->setCurrentRow(index);
        this->lastSelectedIndex = index;
        ui->currentFrame->setText(QString::number(index));
    });
    connect(project, &Project::initialFrames, this, &FrameSelectionPane::setupQList);

    emit this->requestInitialImages();
}

FrameSelectionPane::~FrameSelectionPane() {
    delete ui;
}

void FrameSelectionPane::addFrame(int index) {
    auto* item = new QListWidgetItem();
    const QSize s = ui->listWidget->iconSize();
    QPixmap blank(s);
    blank.fill(Qt::transparent);
    item->setIcon(QIcon(blank));
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
    for (int i = 0; i < static_cast<int>(frames.size()); i++){
        addFrame(i);
        onUpdate(i, frames[i]);
    }
    ui->currentFrame->setText("0");
    ui->listWidget->setCurrentRow(0);
}

QPixmap FrameSelectionPane::makeIcon(const QImage &img) {
    const int size = 100;
    QPixmap pm(size, size);
    pm.fill(Qt::transparent);
    QPainter p(&pm);
    p.setRenderHint(QPainter::SmoothPixmapTransform, false);

    // checkerboard
    const int tile = 8;
    for (int y = 0; y < size; y += tile)
        for (int x = 0; x < size; x += tile)
            p.fillRect(x, y, tile, tile, ((x/tile + y/tile) & 1) ? QColor(200,200,200) : QColor(240,240,240));

    // sprite scaled, centered
    QImage scaled = img.scaled(size, size, Qt::KeepAspectRatio, Qt::FastTransformation);
    p.drawImage(QPoint((size - scaled.width())/2, (size - scaled.height())/2), scaled);
    return pm;
}


void FrameSelectionPane::buttonAdd() {
    emit frameAdded(ui->listWidget->currentRow() + 1);
}

void FrameSelectionPane::buttonDelete(){
    emit frameDeleted(ui->listWidget->currentRow());
}
