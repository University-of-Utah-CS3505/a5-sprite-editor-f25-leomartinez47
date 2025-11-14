/*
    Contributors: Sean Ho, Leo Martinez, Bryce Wiley
    Date: 13/11/2025
*/

#ifndef FRAMESELECTIONPANE_H
#define FRAMESELECTIONPANE_H

#include <QListWidget>
#include <QWidget>

#include "project.h"

namespace Ui {
class FrameSelectionPane;
}

/// The FrameSelectionPane is where the user can add, delete, and select Sprite
/// frames.
class FrameSelectionPane : public QWidget {
    Q_OBJECT

  public:
    ///
    /// @brief Constructs a FrameSelectionPane from a Project.
    /// @param project - The Project associated with this pane.
    /// @param parent
    ///
    explicit FrameSelectionPane(Project *project, QWidget *parent = nullptr);

    ///
    /// @brief Desctructs this FrameSelectionPane.
    ///
    ~FrameSelectionPane();

  signals:
    ///
    /// @brief Emitted when the add frame button is pressed.
    /// @param index - the index to insert the frame to.
    ///
    void frameAdded(int index);

    ///
    /// @brief Emitted when the delete frame button is pressed.
    /// @param index - The index to delete.
    ///
    void frameDeleted(int index);

    ///
    /// @brief Emitted when pane is constructed to retrieve the initial list of
    /// frames.
    ///
    void requestInitialImages();

  public slots:
    ///
    /// @brief Acts as a middleman between the add button and the project slot
    /// that handles adding.
    ///
    void onAddButtonPressed();

    ///
    /// @brief Middleman between delete button and the project slot to delete
    /// the actual item.
    ///
    void onDeleteButtonPressed();

    ///
    /// @brief Captures signal from project to reflect changes after adding.
    /// @param index - the index to add a frame at.
    ///
    void onFrameAdded(int index);

    ///
    /// @brief Captures signal from project to reflect changes after deleting.
    /// @param index - the index to delete a frame at.
    ///
    void onFrameDeleted(int index);

    ///
    /// @brief Refreshes the icon of the list widget item at the specified
    /// index.
    /// @param index - the index of the selected frame.
    ///
    void onFrameUpdate(int index, const QImage &img);

    ///
    /// @brief Called by the project whenever the initial list is created to
    /// reflect changes to the list.
    /// @param frames - The vector of QImages to display.
    ///
    void onStartingList(std::vector<QImage> frames);

  private:
    Ui::FrameSelectionPane *ui;

    ///
    /// @brief Makes a QPixmap of the image provided to be used as an icon
    /// @param img - The image to be converted.
    /// @return A pixmap of the specified image.
    ///
    QPixmap makeIcon(const QImage &img);

    /// The last index.
    int lastSelectedIndex = -1;
};

#endif
