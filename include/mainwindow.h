#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QErrorMessage>
#include <QString>

#include "project.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void createActions();
    void createMenus();
    Project *currentProject();

    QTabWidget *tabs;

    // File Menu:
    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *exportAct;
    QAction *closeTabAct;
    QAction *exitAct;

private slots:
    void onNewProjectRequested();
    void onExportRequested();
    void onHandleCloseCurrentTabRequested();
    void onHandleCloseTabRequested(int index);
    void onSaveRequested();
    void onOpenRequested();
    void onFinishSetup(QWidget* senderView, Project *project);
    void onUpdateTabViewTitle(QWidget* senderView, const QString& newTitle);
};


#endif // MAINWINDOW_H
