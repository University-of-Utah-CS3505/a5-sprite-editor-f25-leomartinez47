/*
    Contributors: Leo Martinez and Sean Ho
    Date: 11/11/2025
*/

#include <QPainter>

#include "previewpane.h"
#include "ui_previewpane.h"
#include "sprite.h"


PreviewPane::PreviewPane(Project *project, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PreviewPane)
    , currentFrameIndex(0)
{
    ui->setupUi(this);

    this->sprite = project->getSprite();

    ui->frameRateSelector->setRange(0, 60);
    ui->frameRateSelector->setValue(30);
    this->timer.setInterval(1000/this->sprite->getFrameRate());


    connect(ui->playPauseButton,
        &QPushButton::clicked,
        this,
        &PreviewPane::onPlayPauseClicked);

    connect(&timer,
            &QTimer::timeout,
            this,
            &PreviewPane::showFrame);

    connect(this,
            &PreviewPane::setFrameRate,
            project,
            &Project::onFrameRateSet);

     connect(ui->frameRateSelector,
        &QSpinBox::valueChanged,
        this,
        [this](int fps) {
            this->timer.setInterval(1000/fps);
            emit setFrameRate(fps);
        });

}

PreviewPane::~PreviewPane()
{
    delete ui;
}

void PreviewPane::onPlayPauseClicked()
{
    if (!this->isPlaying) {
        this->timer.start();
        this->currentFrameIndex = 0;
        ui->playPauseButton->setText("Pause");
    }
    else {
        this->timer.stop();
        this->currentFrameIndex = 0;
        ui->playPauseButton->setText("Play");
    }
    this->isPlaying = !this->isPlaying;
}

void PreviewPane::showFrame()
{
    update();
    this->currentFrameIndex >= this->sprite->frameCount() - 1 ? this->currentFrameIndex = 0 : this->currentFrameIndex++;
}

void PreviewPane::paintEvent(QPaintEvent*)
{
    QImage *currentFrame = &sprite->getFrame(this->currentFrameIndex);
    int scaleFactor, xOffset, yOffset;
    QPainter painter(this);
    QPixmap framePixmap = QPixmap::fromImage(*currentFrame);

    // Calculate the scale factor and offsets for the current frame
    int scaleFactorX = ui->frame->width() / currentFrame->width();
    int scaleFactorY = ui->frame->height() / currentFrame->height();
    scaleFactor = qMax(1, qMin(scaleFactorX, scaleFactorY));

    int scaledWidth = currentFrame->width() * scaleFactor;
    int scaledHeight = currentFrame->height() * scaleFactor;
    xOffset = (this->width() - scaledWidth) / 2;
    yOffset = (ui->frame->height() - scaledHeight) / 2;

    if(scaledWidth > this->width() || scaledHeight > this->height()){
        qDebug() << "Scaled width: " << scaledWidth << width() << "Scaled height: " << scaledHeight << height();
    }

    // Transparency grid
    QRect gridArea(xOffset, yOffset, scaledWidth, scaledHeight);

    const int gridSize = qMax(1, scaleFactor/2);
    QColor lightGray(0xCC, 0xCC, 0xCC);
    QColor darkGray(0xAA, 0xAA, 0xAA);

    // Loop through the scaled area, drawing alternating squares
    for (int y = gridArea.top(); y < gridArea.bottom(); y += gridSize) {
        for (int x = gridArea.left(); x < gridArea.right(); x += gridSize) {
            QColor squareColor = (((x - xOffset) / gridSize +
                                   (y - yOffset) / gridSize)
                                      % 2 == 0) ? lightGray : darkGray;

            int drawWidth = qMin(gridSize, gridArea.right() - x);
            int drawHeight = qMin(gridSize, gridArea.bottom() - y);

            // Draw the clamped rectangle
            painter.fillRect(x, y, drawWidth, drawHeight, squareColor);
        }
    }

    // Draw the scaled frame
    // painter.drawPixmap(xOffset, yOffset,
    //                    framePixmap.scaled(
    //                        scaledWidth, scaledHeight,
    //                        Qt::KeepAspectRatio, Qt::FastTransformation));
}
