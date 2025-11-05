#include "mainwindow.h"
#include "projectview.h"

#include <string>

#include <QRect>
#include <QMenuBar>
#include <QAction>
#include <QTabBar>

const QSize DEFAULT_DIMENSIONS = QSize(25, 25);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(QRect(0, 0, 1000, 800));
    this->setWindowTitle("Sprite Editor");

    this->createActions();
    this->createMenus();

    this->tabs = new QTabWidget(this);
    this->tabs->tabBar()->setMovable(true);
    this->tabs->setTabsClosable(true);

    connect(this->tabs, &QTabWidget::tabCloseRequested,
            this, &MainWindow::handleCloseTabRequested);

    this->setCentralWidget(tabs);

    // When the window opens, start an initial new project.
    this->newProject();
}

void MainWindow::newProject() {
    // TODO: prompt the user to configure the dimensions before creating it.
    // TODO (grant): set up fileNameChanged signal to change tab title.
    Project *project = new Project(DEFAULT_DIMENSIONS);
    this->tabs->addTab(new ProjectView(project), "<New Project>");
}

void MainWindow::handleCloseTabRequested(int index) {
    if (index < 0 || index >= tabs->count()) {
        return;
    }

    QWidget *page = tabs->widget(index);

    // TODO (grant): check is saved and if not prompt the user.

    this->tabs->removeTab(index);

    if (page) {
        delete page;
    }
}

void MainWindow::createMenus() {
    this->fileMenu = this->menuBar()->addMenu("File");
    this->fileMenu->addAction(this->newAct);
    this->fileMenu->addAction(this->exitAct);
}

void MainWindow::createActions() {
    this->newAct = new QAction("New", this);
    this->newAct->setShortcuts(QKeySequence::New);
    this->newAct->setStatusTip("Create a new project");
    connect(newAct, &QAction::triggered, this, &MainWindow::newProject);

    this->exitAct = new QAction("Exit", this);
    this->exitAct->setShortcuts(QKeySequence::Quit);
    this->exitAct->setStatusTip("Exit the application");
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}
