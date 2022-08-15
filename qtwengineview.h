#ifndef QTWEVIEW_H
#define QTWEVIEW_H

#include <QWebEngineSettings>
#include <QWebEngineView>
#include <QAction>

class WebEngineView : public QWebEngineView
{
    Q_OBJECT
public:
    WebEngineView(QWidget *parent);
    QString returnLink();
    ~WebEngineView();
protected:
    void updateLink(const QUrl &url);
    void detectedLink(QString link);
    void showContextMenu(const QPoint &pos);
    void ExitAction();
    QAction *exit = new QAction();
    QString linkurl = "";
};



#endif
