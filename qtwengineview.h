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
    ~WebEngineView();
protected:
    void showContextMenu(const QPoint &pos);
    void ExitAction();
    QAction *exit = new QAction();
};

#endif
