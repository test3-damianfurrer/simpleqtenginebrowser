#ifndef QTWEPAGE_H
#define QTWEPAGE_H

#include <QWebEnginePage>

class WebEnginePage : public QWebEnginePage
{
    Q_OBJECT
public:
    WebEnginePage(QWebEngineProfile *profile);
    void enableNav();
    void disableNav();
    //~WebEnginePage();
protected:
    bool acceptNavigationRequest(const QUrl&, QWebEnginePage::NavigationType, bool);
    bool m_disableNav;
};



#endif
