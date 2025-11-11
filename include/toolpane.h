#ifndef TOOLPANE_H
#define TOOLPANE_H

#include <QWidget>
#include "tools.h"

namespace Ui {
class ToolPane;
}

class ToolPane : public QWidget
{
    Q_OBJECT

public:
    explicit ToolPane(QWidget *parent = nullptr);
    ~ToolPane();
    void focusATool(QString tool);

signals:
    void toolSelected(Tool *tool);

private slots:
    void onPencilSelected();
    void onEraserSelected();

private:
    Ui::ToolPane *ui;
};

#endif // TOOLPANE_H
