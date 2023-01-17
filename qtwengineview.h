#ifndef QTWEVIEW_H
#define QTWEVIEW_H

#include <QWebEngineSettings>
#include <QWebEngineView>
#include <QAction>
#include <QWebEngineFullScreenRequest>

class WebEngineView : public QWebEngineView
{
    Q_OBJECT
public:
    WebEngineView(QString *pwd, bool js, bool scrollbar, QWidget *parent);
    QString returnLink();
    void setUAString(QString userAgent);
    void setAllPaths(QString);
    ~WebEngineView();
protected:
    void dlReq(QWebEngineDownloadItem* download);
    void updateLink(const QUrl &url);
    void detectedLink(QString link);
    void showContextMenu(const QPoint &pos);
    void ExitAction();
    void fullscrnReq(QWebEngineFullScreenRequest req);
    QAction *exit = new QAction();
    QString linkurl = "";
};



#endif
