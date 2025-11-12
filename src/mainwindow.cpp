#include <QAction>
#include <QMenuBar>
#include <QRect>
#include <QTabBar>
#include <QFileDialog>

#include "mainwindow.h"
#include "projectview.h"
#include "spritesetup.h"

const QString NEW_PROJECT_TITLE = "<New Project>";

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
    SpriteSetup *setup = new SpriteSetup();

    connect(setup, &SpriteSetup::setupFinished,
            this, &MainWindow::onFinishSetup);

    int newIndex = this->tabs->addTab(setup, NEW_PROJECT_TITLE);

    if (this->tabs->count() != 0) {
        this->tabs->setCurrentIndex(newIndex);
    }
}

void MainWindow::onHandleCloseTabRequested(int index)
{
    if (index < 0 || index >= tabs->count()) {
        return;
    }

    if (tabs->count() == 1) {
        emit this->close();
        return;
    }

    // TODO: possibly check if project isn't saved?

    QWidget *page = tabs->widget(index);
    this->tabs->removeTab(index);

    if (page) {
        delete page;
    }
}

void MainWindow::onHandleCloseCurrentTabRequested() {
    this->onHandleCloseTabRequested(this->tabs->currentIndex());
}

void MainWindow::onUpdateTabViewTitle(QWidget* senderView, const QString& newTitle)
{
    int index = this->tabs->indexOf(senderView);

    if (index == -1)
    {
        qWarning() << "Update failed: sender view not found in QTabWidget.";
        return;
    }

    this->tabs->setTabText(index, newTitle);
}

void MainWindow::onFinishSetup(QWidget* setupView, Project *project) {
    int index = this->tabs->indexOf(setupView);

    if (index == -1) {
        qWarning() << "Update failed: sender view not found in QTabWidget.";
        return;
    }

    ProjectView *view = new ProjectView(project);

    connect(view, &ProjectView::wantsTabTitleUpdate,
            this, &MainWindow::onUpdateTabViewTitle);

    // Remove the old setup view
    this->tabs->removeTab(index);
    setupView->deleteLater();

    // Add the new project view with the associated project as the visible tab.
    int newIndex = this->tabs->insertTab(index, view, NEW_PROJECT_TITLE);

    if (this->tabs->count() != 1) {
        this->tabs->setCurrentIndex(newIndex);
    }
}

void MainWindow::onSaveRequested() {
    Project* currentProject = this->currentProject();

    if (currentProject == nullptr) {
        return;
    }

    currentProject->save([this]() {
        return QFileDialog::getSaveFileName(this, "Save Project File",
            QDir::home().absolutePath(),
            PROJECT_FILE_EXTENSION_DESCRIPTION);
    });
}

void MainWindow::onExportRequested()
{
    Project* currentProject = this->currentProject();

    if (currentProject == nullptr) {
        return;
    }

    QString path = QFileDialog::getSaveFileName(this, "Export Sprite",
                                                QDir::home().absolutePath(),
                                                "GIF Image (*.gif);;Current Frame PNG Image (*.png)");

    // TODO: handle case with no extension returned, which should we pick?

    currentProject->exportFile(path);
}

void MainWindow::onOpenRequested() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Project File",
                                                    QDir::home().absolutePath(),
                                                    PROJECT_FILE_EXTENSION_DESCRIPTION);

    // Dialog was canceled
    if (fileName.isEmpty()) {
        return;
    }

    // Don't open the same file multiple times.
    for (int i = 0; i < this->tabs->count(); i++) {
        ProjectView *view = qobject_cast<ProjectView*>(this->tabs->widget(i));

        if (view != nullptr && fileName == view->getProject()->getPath()) {
            this->tabs->setCurrentIndex(i);
            return;
        }
    }
  
    Project *project;
    try
    {
        project = new Project(fileName);
    }
    catch(std::invalid_argument ex) { //an exception isn't being thrown right now. Project is making a Sprite out of a bad Json
        qWarning() << ex.what();
        return;
    }
    int newIndex = this->tabs->addTab(new ProjectView(project), project->getName());
    this->tabs->setCurrentIndex(newIndex);
}

Project *MainWindow::currentProject() {
    ProjectView *currentView = qobject_cast<ProjectView*>(this->tabs->currentWidget());

    if (currentView == nullptr) {
        return nullptr;
    }

    return currentView->getProject();
}


void MainWindow::createMenus()
{
    this->fileMenu = this->menuBar()->addMenu("File");
    this->fileMenu->addAction(this->newAct);
    this->fileMenu->addAction(this->openAct);
    this->fileMenu->addAction(this->saveAct);
    this->fileMenu->addAction(this->exportAct);
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

    this->exportAct = new QAction("Export", this);
    this->exportAct->setShortcuts(QKeySequence::Print);
    connect(this->exportAct, &QAction::triggered, this, &MainWindow::onExportRequested);

    this->closeTabAct = new QAction(this);
    this->closeTabAct->setShortcuts(QKeySequence::Close);
    connect(this->closeTabAct, &QAction::triggered,
            this, &MainWindow::onHandleCloseCurrentTabRequested);
    // closeTabAct is not registered in the file menu.
    this->addAction(this->closeTabAct);

    // TODO: maybe ask the user if they've saved the file.
    this->exitAct = new QAction("Exit", this);
    this->exitAct->setShortcuts(QKeySequence::Quit);
    connect(this->exitAct, &QAction::triggered, this, &QWidget::close);
}
