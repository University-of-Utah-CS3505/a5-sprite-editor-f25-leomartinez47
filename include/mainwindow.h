#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

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
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;

private slots:
    void onNewProjectRequested();
    void onHandleCloseTabRequested(int index);
    void onSaveRequested();
    void onOpenRequested();
    void updateTabViewTitle(QWidget* senderView, const QString& newTitle);
};
#endif // MAINWINDOW_H
