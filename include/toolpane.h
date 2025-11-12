#ifndef TOOLPANE_H
#define TOOLPANE_H

#include <QWidget>

#include "tools.h"
#include "project.h"

namespace Ui {
class ToolPane;
}

class ToolPane : public QWidget
{
    Q_OBJECT

public:
    explicit ToolPane(Project *project, QWidget *parent = nullptr);
    ~ToolPane();

signals:
    void toolSelected(Tool *tool);

private slots:
    void onPencilSelected();
    void onEraserSelected();
    void onFillSelected();
    void onToolSelected(Tool *tool);

private:
    Ui::ToolPane *ui;
};

#endif // TOOLPANE_H
