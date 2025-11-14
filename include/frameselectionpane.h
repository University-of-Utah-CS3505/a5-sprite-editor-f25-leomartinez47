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
    explicit FrameSelectionPane(Project *project, QWidget *parent = nullptr);
    ~FrameSelectionPane();

signals:
    void frameAdded(int index);
    void frameDeleted(int index);
    void requestInitialImages();



public slots:

    void buttonAdd();
    void buttonDelete();
    ///
    /// \brief addFrame : adds a frame at the index provided
    /// \param index : the index to add a frame at
    ///
    void addFrame(int index);
    ///
    /// \brief DeleteFrame : deletes the current frame in view
    /// \param index : the index to delete a frame at
    ///
    void deleteFrame(int index);
    ///
    /// \brief onUpdate : updates the view based on changes to the frames
    /// \param index : the index of the selected frame
    ///
    void onUpdate(int index, const QImage &img);

    void setupQList(std::vector<QImage> frames);

private:
    Ui::FrameSelectionPane *ui;
    ///
    /// \brief displaySpriteFrames : private helper method to display all of the frames in the sprite
    ///
    Project *proj;

    QPixmap makeIcon(const QImage &img);
    int lastSelectedIndex = -1;
    void adjustSize();
};

#endif // FRAMESELECTIONPANE_H
