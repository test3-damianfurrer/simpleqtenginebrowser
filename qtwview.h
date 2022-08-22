#ifndef QTWVIEW_H
#define QTWVIEW_H

#include "qtwengineview.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QUrl& url);
    QUrl url();
    QString title();
    void customContextMenu(const QPoint &pos);
    ~MainWindow();

protected slots:

    void loadStarted();
    void urlChanged();
    void adjustTitle();
    void setProgress(int p);
    void finishLoading(bool);

private:
    WebEngineView *view;
    int progress;
};

#endif
