#include "qtwengineview.h"
#include <QApplication>
#include <QMenu>
#include <QWebEngineProfile>
#include <QDesktopServices>
#include <QDropEvent>
#include "qtwpage.h"

WebEngineView::WebEngineView(QString *pwd, bool js, bool scrollbar, QWidget *parent = Q_NULLPTR)
{
    exit->setShortcut(Qt::Key_Escape);
    QString profilepath=*pwd;
    profilepath+="/profile";
    WebEnginePage* wpx = new WebEnginePage(new QWebEngineProfile(profilepath));
    setPage(wpx);

    settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
//    settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true); disabled by default, not required (usefull for Pepper Plugin API.)
    settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
//--new
    settings()->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard, true);
    settings()->setAttribute(QWebEngineSettings::JavascriptCanPaste, true); //depends on^
    settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, js);
    settings()->setAttribute(QWebEngineSettings::SpatialNavigationEnabled, true);
    settings()->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);
    settings()->setAttribute(QWebEngineSettings::TouchIconsEnabled, true); //test
    //settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true); default false, https everywhere on https pages
    //settings()->setAttribute(QWebEngineSettings::AllowGeolocationOnInsecureOrigins, false); //default
    settings()->setAttribute(QWebEngineSettings::AllowWindowActivationFromJavaScript, true);
    settings()->setAttribute(QWebEngineSettings::ShowScrollBars, scrollbar);
    settings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false); //default true, like a mobile browser
    //settings()->setAttribute(QWebEngineSettings::WebRTCPublicInterfacesOnly, false); //default, true is more secure
    settings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true); //default disabled
    //settings()->setAttribute(QWebEngineSettings::PdfViewerEnabled, true); //default
    settings()->setFontSize(QWebEngineSettings::MinimumFontSize,12);
    settings()->setFontSize(QWebEngineSettings::MinimumLogicalFontSize,12);
    settings()->setFontSize(QWebEngineSettings::DefaultFontSize,24);
    settings()->setFontSize(QWebEngineSettings::DefaultFixedFontSize,26);
    settings()->setUnknownUrlSchemePolicy(QWebEngineSettings::AllowAllUnknownUrlSchemes);
//https://doc.qt.io/qt-5/qwebenginesettings.html#WebAttribute-enum
//++new
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
//test dl signal
//QWebEngineProfile::downloadRequested(QWebEngineDownloadItem *download) //dlReq
    connect(page()->profile(),&QWebEngineProfile::downloadRequested,this, &WebEngineView::dlReq);
}

//QWebEngineProfile::downloadRequested(QWebEngineDownloadItem *download) //dlReq
void WebEngineView::dlReq(QWebEngineDownloadItem *download){
	download->accept(); //accept by default
}


void WebEngineView::setUAString(QString userAgent){
    QWebEngineProfile * prf = page()->profile();
    prf->setHttpUserAgent(userAgent);
}

void WebEngineView::setAllPaths(QString currpath){
    QWebEngineProfile * prf = page()->profile();
    prf->setCachePath(currpath);
//    prf->setDownloadPath(currpath+"/download");//+"/Download");
    prf->setDownloadPath(currpath+"/../download");//+"/Download");
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
    WebEnginePage* p = (WebEnginePage*)page(); //maybe also attach to a selection chage event, when there might be a direct navigation added.
    p->enableNav();

    linkurl = link;
}

void WebEngineView::ExitAction(){
    QCoreApplication::exit(0);
}
void WebEngineView::showContextMenu(const QPoint &pos){
    WebEnginePage* p = (WebEnginePage*)page();
    p->enableNav();

    if(linkurl == ""){
	if (hasSelection() == false) {
	  return;
	} else {
	  linkurl = selectedText().split("\n").at(0);
        }
    }
    QMenu *contextMenu = new QMenu();
    QAction *return_link = new QAction(tr("Return Link"));
    QAction *sysopen_link = new QAction(tr("Sys Open Link"));
    connect(return_link, &QAction::triggered, this, [this] {setUrl(QUrl(linkurl));ExitAction();});
    connect(sysopen_link, &QAction::triggered, this, [this] {QDesktopServices::openUrl(QUrl(linkurl));});
    contextMenu->addAction(return_link);
    contextMenu->addAction(sysopen_link);
    contextMenu->exec(this->mapToGlobal(pos));
}

/*//from webengineview source code
void WebEngineView::dropEvent(QDropEvent *e)
    Q_D(QWebEngineView);
    if (!d->m_dragEntered)
        return;
    e->accept();
    d->page->d_ptr->adapter->endDragging(e, mapToGlobal(e->position().toPoint()));
    d->m_dragEntered = false;
}*/

void WebEngineView::dropEvent(QDropEvent *e){

    WebEnginePage* p = (WebEnginePage*)page();
    p->disableNav();
    QWebEngineView::dropEvent(e);
}

WebEngineView::~WebEngineView()
{
//  page()->~QWebEnginePage();
  WebEnginePage* p = (WebEnginePage*)page();
  p->~WebEnginePage();
}
