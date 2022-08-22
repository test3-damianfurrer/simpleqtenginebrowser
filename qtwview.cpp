#include "qtwview.h"
#include "qtwengineview.h"
#include <QApplication>

MainWindow::MainWindow(const QUrl& url)
{
    progress = 0;
    view = new WebEngineView(this);
    connect(view, &WebEngineView::urlChanged, this, &MainWindow::urlChanged);
    connect(view, &WebEngineView::titleChanged, this, &MainWindow::urlChanged);
    connect(view, &WebEngineView::loadFinished, this, &MainWindow::finishLoading);
    connect(view, &WebEngineView::loadProgress, this, &MainWindow::setProgress);
    view->load(url);
    setCentralWidget(view);
}

QUrl MainWindow::url(){
    return view->returnLink();
}

QString MainWindow::title(){
    return view->title();
}
void MainWindow::adjustTitle()
{
    if (progress >= 100)
        setWindowTitle(view->title());
    else if (progress == 0)
	setWindowTitle(QStringLiteral("Loading"));
    else
        setWindowTitle(QStringLiteral("%1 (%2%)").arg(progress).arg(view->title()));
}

void MainWindow::urlChanged(){
    //progress = 0;
    adjustTitle();
}

void MainWindow::loadStarted(){
    progress = 0;
    adjustTitle();
}

void MainWindow::setProgress(int p)
{
    progress = p;
    adjustTitle();
}
void MainWindow::finishLoading(bool)
{
    progress = 100;
    adjustTitle();
}

MainWindow::~MainWindow()
{
  view->~WebEngineView();
}
