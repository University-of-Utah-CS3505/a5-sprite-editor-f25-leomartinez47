#ifndef TOOLPANE_H
#define TOOLPANE_H

#include <QWidget>

namespace Ui {
class ToolPane;
}

class ToolPane : public QWidget
{
    Q_OBJECT

public:
    explicit ToolPane(QWidget *parent = nullptr);
    ~ToolPane();

private:
    Ui::ToolPane *ui;
};

#endif // TOOLPANE_H
