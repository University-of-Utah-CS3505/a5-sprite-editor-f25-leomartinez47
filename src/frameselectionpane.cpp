/*
    Contributors: Sean Ho, Leo Martinez, Bryce Wiley
    Date: 13/11/2025
*/

#include "frameselectionpane.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QPainter>
#include <QPushButton>

#include "project.h"
#include "ui_frameselectionpane.h"

FrameSelectionPane::FrameSelectionPane(Project *project, QWidget *parent)
    : QWidget(parent), ui(new Ui::FrameSelectionPane) {
    this->ui->setupUi(this);

    // Set up list style
    auto *list = ui->listWidget;
    list->setViewMode(QListView::IconMode);
    list->setMovement(QListView::Static);
    list->setWrapping(false);
    list->setResizeMode(QListView::Adjust);
    list->setIconSize(QSize(123, 123));
    list->setGridSize(QSize(128, 128));

    list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Buttons -> code
    connect(ui->AddFrame, &QPushButton::clicked, this,
            &FrameSelectionPane::onAddButtonPressed);

    connect(ui->DeleteFrame, &QPushButton::clicked, this,
            &FrameSelectionPane::onDeleteButtonPressed);

    connect(ui->listWidget, &QListWidget::currentRowChanged, project,
            &Project::onCurrentFrameChanged);

    // Pane -> Project
    connect(this, &FrameSelectionPane::frameAdded, project,
            &Project::onFrameAdded);

    connect(this, &FrameSelectionPane::frameDeleted, project,
            &Project::onFrameRemoved);

    connect(this, &FrameSelectionPane::requestInitialImages, project,
            &Project::sendInitialImages);

    // Project -> Pane
    connect(project, &Project::frameAdded, this,
            &FrameSelectionPane::onFrameAdded);

    connect(project, &Project::frameRemoved, this,
            &FrameSelectionPane::onFrameDeleted);

    connect(project, &Project::frameSelectionChanged, this,
            [this, project](int index) {
                // If the index we are coming from is not the first or last
                // object, update that frame. This makes the frames show the
                // updates made when clicking off
                if (lastSelectedIndex >= 0 &&
                    lastSelectedIndex <= project->frameCount() - 1) {
                    this->onFrameUpdate(lastSelectedIndex,
                                        project->frameAt(lastSelectedIndex));
                }
                this->onFrameUpdate(index, project->frameAt(index));
                ui->listWidget->setCurrentRow(index);
                this->lastSelectedIndex = index;
                ui->currentFrame->setText(QString::number(index));
            });

    connect(project, &Project::initialFrames, this,
            &FrameSelectionPane::onStartingList);

    emit this->requestInitialImages();
}

FrameSelectionPane::~FrameSelectionPane() {
    delete this->ui;
}

void FrameSelectionPane::onFrameAdded(int index) {
    auto *item = new QListWidgetItem();
    const QSize s = this->ui->listWidget->iconSize();
    QPixmap blank(s);
    blank.fill(Qt::transparent);
    item->setIcon(QIcon(blank));
    this->ui->listWidget->insertItem(index, item);
}

void FrameSelectionPane::onFrameDeleted(int index) {
    this->ui->listWidget->takeItem(index);
}

void FrameSelectionPane::onFrameUpdate(int index, const QImage &img) {
    if (auto *item = ui->listWidget->item(index))
        item->setIcon(QIcon(makeIcon(img)));
}

void FrameSelectionPane::onStartingList(std::vector<QImage> frames) {
    for (int i = 0; i < static_cast<int>(frames.size()); i++) {
        onFrameAdded(i);
        onFrameUpdate(i, frames[i]);
    }
    ui->currentFrame->setText("0");
    ui->listWidget->setCurrentRow(0);
}

QPixmap FrameSelectionPane::makeIcon(const QImage &img) {
    const int size = 100;
    QPixmap pm = QPixmap(size, size);
    pm.fill(Qt::transparent);
    QPainter p = QPainter(&pm);
    p.setRenderHint(QPainter::SmoothPixmapTransform, false);

    // checkerboard
    const int tile = 8;
    for (int y = 0; y < size; y += tile)
        for (int x = 0; x < size; x += tile)
            p.fillRect(x, y, tile, tile,
                       ((x / tile + y / tile) & 1) ? QColor(200, 200, 200)
                                                   : QColor(240, 240, 240));

    // sprite scaled, centered
    QImage scaled =
        img.scaled(size, size, Qt::KeepAspectRatio, Qt::FastTransformation);
    p.drawImage(
        QPoint((size - scaled.width()) / 2, (size - scaled.height()) / 2),
        scaled);
    return pm;
}

void FrameSelectionPane::onAddButtonPressed() {
    emit this->frameAdded(ui->listWidget->currentRow() + 1);
}

void FrameSelectionPane::onDeleteButtonPressed() {
    emit this->frameDeleted(ui->listWidget->currentRow());
}
