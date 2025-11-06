#ifndef FRAMESELECTIONPANE_H
#define FRAMESELECTIONPANE_H

#include <QWidget>
#include "project.h"

namespace Ui {
class FrameSelectionPane;
}

class FrameSelectionPane : public QWidget
{
    Q_OBJECT

public:
    explicit FrameSelectionPane(Project *project, QWidget *parent = nullptr);
    ~FrameSelectionPane();

signals:
    ///
    /// \brief AddFrame : adds a frame at the index provided
    /// \param index : the index to add a frame at
    ///
    void addFrame(int index);

    ///
    /// \brief DeleteFrame : deletes the current frame in view
    /// \param index : the index to delete a frame at
    ///
    void deleteFrame(int index);

public slots:
    ///
    /// \brief onUpdate : updates the view based on changes to the frames
    ///
    void onUpdate();

private:
    Ui::FrameSelectionPane *ui;
    ///
    /// \brief displaySpriteFrames : private helper method to display all of the frames in the sprite
    ///
    void displaySpriteFrames();
};

#endif // FRAMESELECTIONPANE_H
