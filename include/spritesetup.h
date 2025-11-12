#ifndef SPRITESETUP_H
#define SPRITESETUP_H

#include <QWidget>

#include "project.h"

namespace Ui {
class SpriteSetup;
}

class SpriteSetup : public QWidget
{
    Q_OBJECT

public:
    explicit SpriteSetup(QWidget *parent = nullptr);
    ~SpriteSetup();

signals:
    void setupFinished(QWidget *me, Project *project);

private slots:
    void onCreateProject();

private:
    Ui::SpriteSetup *ui;
};

#endif // SPRITESETUP_H
