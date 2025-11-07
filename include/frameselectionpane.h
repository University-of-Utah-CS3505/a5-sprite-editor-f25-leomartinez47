#ifndef FRAMESELECTIONPANE_H
#define FRAMESELECTIONPANE_H

#include <QWidget>
#include <QListWidget>
#include "project.h"

namespace Ui {
class FrameSelectionPane;
}

class FrameSelectionPane : public QWidget
{
    Q_OBJECT

public:
    QListWidget listWidget;

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
    /// \param index : the index of the selected frame
    ///
    void onUpdate(int index);

    void addFrameToList();

private:
    Ui::FrameSelectionPane *ui;
    int currentIndex;
    ///
    /// \brief displaySpriteFrames : private helper method to display all of the frames in the sprite
    ///
    void setupQList();
};

#endif // FRAMESELECTIONPANE_H
