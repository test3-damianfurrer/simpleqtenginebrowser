#include "qtwengineview.h"
#include <QApplication>

//#include <QWebEngineView>

WebEngineView::WebEngineView(QWidget *parent = Q_NULLPTR)
{
    exit->setShortcut(Qt::Key_Escape);
    setPage(new QWebEnginePage());
    settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, false);
    settings()->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    settings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
    connect(exit, &QAction::triggered, this, &WebEngineView::ExitAction);
    addAction(exit);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &WebEngineView::customContextMenuRequested, this, &WebEngineView::showContextMenu);
}
void WebEngineView::ExitAction(){
	QCoreApplication::exit(0);
}
void WebEngineView::showContextMenu(const QPoint &pos){
ExitAction();
}

WebEngineView::~WebEngineView()
{
  page()->~QWebEnginePage();
}
