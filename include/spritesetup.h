/*
    Contributors: Grant Handy
    Date: 11/13/2025
*/

#ifndef SPRITESETUP_H
#define SPRITESETUP_H

#include <QWidget>

#include "project.h"

namespace Ui {
class SpriteSetup;
}

/// The SpriteSetup prompts the user to input desired Sprite dimensions before
/// directing them to the Sprite Editor program.
class SpriteSetup : public QWidget
{
    Q_OBJECT

public:
    ///
    /// @brief Construct the SpriteSetup.
    /// @param parent
    ///
    explicit SpriteSetup(QWidget *parent = nullptr);
    ~SpriteSetup();

signals:
    ///
    /// @brief Emit when user confirms their input.
    /// @param me - This instance of SpriteSetup.
    /// @param project - The model for the Sprite Editor.
    ///
    void setupFinished(QWidget *me, Project *project);

private slots:
    ///
    /// @brief Create a Project with user's dimensions specifications.
    ///
    void onCreateProject();

private:
    Ui::SpriteSetup *ui;
};

#endif
