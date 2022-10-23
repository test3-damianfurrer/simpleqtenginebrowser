#include "qtwengineview.h"
#include <QApplication>
#include <QMenu>
#include <QWebEngineProfile>

WebEngineView::WebEngineView(QString *pwd, QWidget *parent = Q_NULLPTR)
{
    exit->setShortcut(Qt::Key_Escape);
    QString profilepath=*pwd;
    profilepath+="/profile";
    setPage(new QWebEnginePage(new QWebEngineProfile(profilepath)));
    settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    settings()->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    settings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
    this->setAllPaths(*pwd);
    connect(exit, &QAction::triggered, this, &WebEngineView::ExitAction);
    addAction(exit);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &WebEngineView::customContextMenuRequested, this, &WebEngineView::showContextMenu);
    connect(this, &WebEngineView::urlChanged, this, &WebEngineView::updateLink);
    connect(page(), &QWebEnginePage::linkHovered, this, &WebEngineView::detectedLink);
    connect(page(), &QWebEnginePage::fullScreenRequested, this, &WebEngineView::fullscrnReq);
}

void WebEngineView::setUAString(QString userAgent){
    QWebEngineProfile * prf = page()->profile();
    prf->setHttpUserAgent(userAgent);
}

void WebEngineView::setAllPaths(QString currpath){
    QWebEngineProfile * prf = page()->profile();
    prf->setCachePath(currpath);
    prf->setDownloadPath(currpath);
}

void WebEngineView::fullscrnReq(QWebEngineFullScreenRequest req){
    req.accept();
}

void WebEngineView::updateLink(const QUrl &url){
    linkurl=url.toString();
}

QString WebEngineView::returnLink(){
    updateLink(url());
    return linkurl;
}

void WebEngineView::detectedLink(QString link){
    linkurl = link;
}

void WebEngineView::ExitAction(){
    QCoreApplication::exit(0);
}
void WebEngineView::showContextMenu(const QPoint &pos){
    if(linkurl == "")
	return;
    QMenu *contextMenu = new QMenu();
    QAction *return_link = new QAction(tr("Return Link"));
    connect(return_link, &QAction::triggered, this, [this] {setUrl(QUrl(linkurl));ExitAction();});
    contextMenu->addAction(return_link);
    contextMenu->exec(this->mapToGlobal(pos));
}

WebEngineView::~WebEngineView()
{
  page()->~QWebEnginePage();
}
