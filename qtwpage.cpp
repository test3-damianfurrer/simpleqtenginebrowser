#include "qtwpage.h"

WebEnginePage::WebEnginePage(QWebEngineProfile *profile) : QWebEnginePage(profile) {
	m_disableNav=false;
}

bool WebEnginePage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame){
	if(m_disableNav){
		return false;
	}
	return true;
}

void WebEnginePage::enableNav(){
	m_disableNav=false;
}
void WebEnginePage::disableNav(){
	m_disableNav=true;
}
