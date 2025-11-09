#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void createActions();
    void createMenus();

    QTabWidget *tabs;

    // File Menu:
    QMenu *fileMenu;
    QAction *newAct;
    QAction *exitAct;

    // TODO: add saveAct and openAct

private slots:
    void newProject();
    void handleCloseTabRequested(int index);
};
#endif // MAINWINDOW_H
