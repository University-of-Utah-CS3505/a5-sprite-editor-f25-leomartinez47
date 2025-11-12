/*
    Contributors: Leo Martinez and Sean Ho
    Date: 11/11/2025
*/

#ifndef PREVIEWPANE_H
#define PREVIEWPANE_H

#include <QWidget>
#include <QTimer>

#include "project.h"


namespace Ui {
class PreviewPane;
}

class PreviewPane : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewPane(Project *project, QWidget *parent = nullptr);
    ~PreviewPane();

public slots:
    /// @brief Receives when the user starts/stops the animation preview.
    void onPlayPauseClicked();

    /// @brief Paints the current frame in the animation, and updates
    /// the currentFrameIndex appropriately.
    void showFrame();

protected:
    /// @brief  Paints the current frame in the animation scaled to fit the
    /// frame widget, and adds a png-style grid background to represent
    /// the transparent parts of the frame.
    void paintEvent(QPaintEvent*) override;

private:
    Ui::PreviewPane *ui;

    /// A Pointer to the Sprite object held by the current Project.
    Sprite *sprite;

    /// The index of the current frame in the animation.
    int currentFrameIndex;

    /// Times out based on the frameRateSelector spinbox to paint
    /// the current frame in the animation.
    QTimer timer;

    /// If the animation is currently playing.
    bool isPlaying;
};

#endif
