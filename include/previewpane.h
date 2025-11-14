/*
    Contributors: Sean Ho and Leo Martinez
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

/// The Preview Pane widget displays an animation of the frames of the Sprite.
class PreviewPane : public QWidget
{
    Q_OBJECT

public:
    ///
    /// @brief Construct a new PreviewPane.
    /// @param project - A pointer to the project model.
    /// @param parent - nullptr because there is no parent.
    ///
    explicit PreviewPane(Project *project, QWidget *parent = nullptr);

    ///
    /// @brief Destructs this PreviewPane by deleting the ui form object.
    ///
    ~PreviewPane();

public slots:
    ///
    /// @brief Receive when the user starts/stops the animation preview.
    ///
    void onPlayPauseClicked();

    ///
    /// @brief Paint the current frame in the animation, and updates
    /// the currentFrameIndex appropriately.
    ///
    void showFrame();

signals:
    ///
    /// @brief Send the frame rate of the animation to the sprite.
    /// @param - The current frame rate of the animation, in ms per frame.
    ///
    void setFrameRate(int frameRate);

protected:
    ///
    /// @brief Paint the current frame in the animation scaled to fit the
    /// frame widget, and add a png-style grid background to represent
    /// the transparent parts of the frame.
    ///
    void paintEvent(QPaintEvent*) override;

private:
    /// The ui form for PreviewPane.
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
