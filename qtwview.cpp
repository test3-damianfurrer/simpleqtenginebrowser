#include "qtwview.h"
#include "qtwengineview.h"
#include <QApplication>

MainWindow::MainWindow(const QUrl& url)
{
    //setAttribute(Qt::WA_DeleteOnClose, true); //manual delete
    progress = 0;
    setContextMenuPolicy(Qt::CustomContextMenu);
    view = new WebEngineView(this);
    view->load(url);
    setCentralWidget(view);
}

void MainWindow::customContextMenu(const QPoint &pos){

}

QUrl MainWindow::url(){
	return view->returnLink(); //->url();
}

void MainWindow::loadFinished()
{
}
void MainWindow::adjustTitle()
{
    if (progress <= 0 || progress >= 100)
        setWindowTitle(view->title());
    else
        setWindowTitle(QStringLiteral("%1 (%2%)").arg(view->title()).arg(progress));
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
