/*
    Contributors: Grant Handy and Kailee Kim
    Date: 11/13/2025
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QErrorMessage>
#include <QMainWindow>
#include <QString>

#include "project.h"

/// MainWindow displays the currently opened Sprite projects in tabs.
class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    ///
    /// @brief Construct the MainWindow.
    /// @param parent
    ///
    MainWindow(QWidget *parent = nullptr);

  private slots:
    ///
    /// @brief Open a tab and display a SpriteSetup.
    ///
    void onNewProjectRequested();

    ///
    /// @brief Open a file dialog for user to select a file to export to.
    ///
    void onExportRequested();

    ///
    /// @brief Close the current tab.
    ///
    void onHandleCloseCurrentTabRequested();

    ///
    /// @brief Close a tab. If there are no other tabs, then this window will
    /// close.
    /// @param index - The index of the tab being closed.
    ///
    void onHandleCloseTabRequested(int index);

    ///
    /// @brief Open a file dialog for user to select a file to save to.
    ///
    void onSaveRequested();

    ///
    /// @brief Open a file dialog for user to select a file to open.
    ///
    void onOpenRequested();

    ///
    /// @brief Open a new Sprite project in the current tab based on
    /// specifications inputed by the user in a SpriteSetup.
    /// @param senderView - Use to find the SpriteSetup tab.
    /// @param project - The new project.
    ///
    void onFinishSetup(QWidget *senderView, Project *project);

    ///
    /// @brief Update the name of a tab.
    /// @param senderView - Use to find the desired tab.
    /// @param newTitle - The new name of the tab.
    ///
    void onUpdateTabViewTitle(QWidget *senderView, const QString &newTitle);

  private:
    ///
    /// @brief Set up the events associated with the menu bar.
    ///
    void createActions();

    ///
    /// @brief Set up the menu bar.
    ///
    void createMenus();

    ///
    /// @brief Get the Sprite project being displayed in the current tab.
    /// @return The currently displayed project.
    ///
    Project *currentProject();

    /// The MainWindow tabs.
    QTabWidget *tabs;

    /// File Menu.
    QMenu *fileMenu;

    /// Action taken when 'new' is selected in file menu.
    QAction *newAct;

    /// Action taken when 'open' is selected in file menu.
    QAction *openAct;

    /// Action taken when 'save' is selected in file menu.
    QAction *saveAct;

    /// Action taken when 'export' is selected in file menu.
    QAction *exportAct;

    /// Action taken when a tab is closed.
    QAction *closeTabAct;

    /// Action taken when window is closed or all tabs
    QAction *exitAct;
};

#endif
