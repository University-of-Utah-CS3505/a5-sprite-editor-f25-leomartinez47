#ifndef FRAMESELECTIONPANE_H
#define FRAMESELECTIONPANE_H

#include <QWidget>

namespace Ui {
class FrameSelectionPane;
}

class FrameSelectionPane : public QWidget
{
    Q_OBJECT

public:
    explicit FrameSelectionPane(QWidget *parent = nullptr);
    ~FrameSelectionPane();

private:
    Ui::FrameSelectionPane *ui;
};

#endif // FRAMESELECTIONPANE_H
