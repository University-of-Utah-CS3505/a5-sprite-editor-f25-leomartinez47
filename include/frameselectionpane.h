/*
    Contributors: Sean Ho, Leo Martinez, Bryce Wiley
    Date: 13/11/2025
*/
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
    ///
    /// @brief frameAdded : Emitted when the add frame button is pressed.
    /// @param index : the index to insert the frame to
    ///
    void frameAdded(int index);

    ///
    /// @brief frameDeleted : Emitted when the delete frame button is pressed
    /// @param index : The index to delete
    ///
    void frameDeleted(int index);

    ///
    /// @brief requestInitialImages : Emitted when pane is constructed to retrieve the initial list of frames
    ///
    void requestInitialImages();

public slots:
    ///
    /// @brief buttonAdd : Acts as a middleman between the add button
    ///                     and the project slot that handles adding
    ///
    void buttonAdd();

    ///
    /// @brief buttonDelete : Middleman between delete button and the
    ///                     project slot to delete the actual item
    ///
    void buttonDelete();

    ///
    /// @brief addFrame : captures signal from project to reflect changes
    ///                     after adding.
    /// @param index : the index to add a frame at
    ///
    void addFrame(int index);

    ///
    /// @brief DeleteFrame : captures signal from project to reflect changes
    ///                     after deleting.
    /// @param index : the index to delete a frame at
    ///
    void deleteFrame(int index);

    ///
    /// @brief onUpdate : refreshes the icon of the list widget item at the specified index
    /// @param index : the index of the selected frame
    ///
    void onUpdate(int index, const QImage &img);

    ///
    /// @brief setupQList : Called by the project whenever the initial list is created to
    ///                     reflect changes to the list
    /// @param frames : The vector of QImages to display
    ///
    void setupQList(std::vector<QImage> frames);

private:
    Ui::FrameSelectionPane *ui;
    QPixmap makeIcon(const QImage &img);
    int lastSelectedIndex = -1;
    void adjustSize();
};

#endif // FRAMESELECTIONPANE_H
