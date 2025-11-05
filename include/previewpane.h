#ifndef PREVIEWPANE_H
#define PREVIEWPANE_H

#include <QWidget>


namespace Ui {
class PreviewPane;
}

class PreviewPane : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewPane(QWidget *parent = nullptr);
    ~PreviewPane();

private:
    Ui::PreviewPane *ui;
};

#endif // PREVIEWPANE_H
