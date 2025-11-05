#ifndef CANVASPANE_H
#define CANVASPANE_H

#include <QWidget>

namespace Ui {
class CanvasPane;
}

class CanvasPane : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasPane(QWidget *parent = nullptr);
    ~CanvasPane();

private:
    Ui::CanvasPane *ui;
};

#endif // CANVASPANE_H
