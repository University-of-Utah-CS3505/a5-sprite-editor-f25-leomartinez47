#include <QAction>
#include <QMenuBar>
#include <QRect>
#include <QTabBar>
#include <QFileDialog>

#include "mainwindow.h"
#include "projectview.h"

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
            this, &MainWindow::onHandleCloseTabRequested);

    this->setCentralWidget(tabs);

    // When the window opens, start an initial new project.
    this->onNewProjectRequested();
}

void MainWindow::onNewProjectRequested()
{
    // TODO: prompt the user to configure the dimensions before creating it.
    // TODO (grant): set up fileNameChanged signal to change tab title.
    Project *project = new Project(DEFAULT_DIMENSIONS);
    ProjectView *view = new ProjectView(project);

    connect(view, &ProjectView::wantsTabTitleUpdate,
            this, &MainWindow::updateTabViewTitle);

    this->tabs->addTab(view, "<New Project>");
}

void MainWindow::onHandleCloseTabRequested(int index)
{
    if (index < 0 || index >= tabs->count()) {
        return;
    }

    QWidget *page = tabs->widget(index);

    // TODO (grant): maybe check is saved and if not prompt the user.

    this->tabs->removeTab(index);

    if (page) {
        delete page;
    }
}

void MainWindow::updateTabViewTitle(QWidget* senderView, const QString& newTitle)
{
    int index = this->tabs->indexOf(senderView);

    if (index != -1)
    {
        this->tabs->setTabText(index, newTitle);
    }
    else
    {
        qWarning() << "Update failed: sender view not found in QTabWidget.";
    }
}

void MainWindow::onSaveRequested() {

    Project *currentProject = qobject_cast<ProjectView*>(this->tabs->currentWidget())->getProject();

    currentProject->save([this]() {
        return QFileDialog::getSaveFileName(this, "Save Project File",
            QDir::home().absolutePath(),
            PROJECT_FILE_EXTENSION);
    });
}

void MainWindow::onOpenRequested() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Project File",
                                                    QDir::home().absolutePath(),
                                                    PROJECT_FILE_EXTENSION);

    if (fileName.isEmpty()) {
        return;
    }

    Project *project = new Project(fileName);
    this->tabs->setCurrentIndex(this->tabs->addTab(new ProjectView(project), project->name()));
}

void MainWindow::createMenus()
{
    this->fileMenu = this->menuBar()->addMenu("File");
    this->fileMenu->addAction(this->newAct);
    this->fileMenu->addAction(this->openAct);
    this->fileMenu->addAction(this->saveAct);
    this->fileMenu->addAction(this->exitAct);
}

void MainWindow::createActions()
{
    this->newAct = new QAction("New", this);
    this->newAct->setShortcuts(QKeySequence::New);
    connect(this->newAct, &QAction::triggered, this, &MainWindow::onNewProjectRequested);

    this->openAct = new QAction("Open", this);
    this->openAct->setShortcuts(QKeySequence::Open);
    connect(this->openAct, &QAction::triggered, this, &MainWindow::onOpenRequested);

    this->saveAct = new QAction("Save", this);
    this->saveAct->setShortcuts(QKeySequence::Save);
    connect(this->saveAct, &QAction::triggered, this, &MainWindow::onSaveRequested);

    this->exitAct = new QAction("Exit", this);
    this->exitAct->setShortcuts(QKeySequence::Quit);

    // TODO: maybe ask the user if they've saved the file.
    connect(this->exitAct, &QAction::triggered, this, &QWidget::close);
}
