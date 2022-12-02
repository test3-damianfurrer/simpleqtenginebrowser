#include "qtwview.h"
#include "qtwengineview.h"
#include <QApplication>
#include <QWebEngineView>
#include <QCommandLineParser>
#include <QNetworkProxy>
#include <unistd.h>

QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}

void showContextMenu(const QPoint &pos){
	qStdOut() << "Custom Context\n";
}
void test(){
	qStdOut() << "Custom Context\n";
}

int main(int argc, char *argv[])
{
    QString pwd=QString(get_current_dir_name())+QString("/.qtw");

    QCoreApplication::setOrganizationName("QtNoobs");
    QCoreApplication::setApplicationName("Qtw-Browser");
    QCoreApplication::setApplicationVersion("v0.0.2");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Qtw-Browser: a very minimalistic implementation of QtWebengine");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("url", QCoreApplication::translate("main", "Url to browse to. Has to be a fully valid url with protocol."));
    QCommandLineOption mobileUAOption("m", QCoreApplication::translate("main", "Use Mobile User Agent"));
    parser.addOption(mobileUAOption);
    QCommandLineOption desktopUAOption("d", QCoreApplication::translate("main", "Use Desktop User Agent(default)"));
    parser.addOption(desktopUAOption);
    QCommandLineOption customUAOption("u", QCoreApplication::translate("main", "Use custom <User Agent>"),QCoreApplication::translate("main", "User Agent"));
    parser.addOption(customUAOption);


    QCommandLineOption proxyOption("p", QCoreApplication::translate("main", "Use Proxy <proxy>"),QCoreApplication::translate("main", "proxy"));
    parser.addOption(proxyOption);
    QCommandLineOption proxyPortOption("o", QCoreApplication::translate("main", "Use Proxy Port <port>"),QCoreApplication::translate("main", "port"));
    parser.addOption(proxyPortOption);
    QCommandLineOption proxyUserOption("proxy-user", QCoreApplication::translate("main", "Use Proxy Auth Username <user>"),QCoreApplication::translate("main", "user"));
    parser.addOption(proxyUserOption);
    QCommandLineOption proxyPassOption("proxy-pass", QCoreApplication::translate("main", "Use Proxy Auth Password <pass>"),QCoreApplication::translate("main", "pass"));
    parser.addOption(proxyPassOption);
    QCommandLineOption proxySocks5Option("socks5", QCoreApplication::translate("main", "Use socks5 Proxy type instead of http"));
    parser.addOption(proxySocks5Option);

    QCommandLineOption noJSOption("nojs", QCoreApplication::translate("main", "Don't use Javascript"));
    parser.addOption(noJSOption);
    QCommandLineOption noScrollOption("noscroll", QCoreApplication::translate("main", "Don't show Scroll Bars"));
    parser.addOption(noScrollOption);



    parser.process(app);
    const QStringList args = parser.positionalArguments();
    QString str = args.at(0);
    QString customUA = parser.value(customUAOption);
    if(customUA==""){
        if(parser.isSet(mobileUAOption)){
	    customUA = QString("Mozilla/5.0 (Linux; U; Android 4.4.2; en-us; SCH-I535 Build/KOT49H) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30");
        } else if(parser.isSet(desktopUAOption)){
            customUA = QString("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36 OPR/91.0.4516.77");
        } else{
            customUA = QString("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36 OPR/91.0.4516.77");
	}
    }
    if(parser.isSet(proxyOption)){
	QNetworkProxy proxy;
	if(parser.isSet(proxySocks5Option)){
	    proxy.setType(QNetworkProxy::Socks5Proxy);
	} else {
	    proxy.setType(QNetworkProxy::HttpProxy);
	}

	proxy.setHostName(parser.value(proxyOption));

	if(parser.isSet(proxyPortOption)){
	    proxy.setPort(parser.value(proxyPortOption).toInt());
	}
	if(parser.isSet(proxyUserOption)){
	    proxy.setUser(parser.value(proxyUserOption));
	}
	if(parser.isSet(proxyPassOption)){
	    proxy.setPassword(parser.value(proxyPassOption));
	}
	QNetworkProxy::setApplicationProxy(proxy);
    }

    bool js = !parser.isSet(noJSOption);
    bool scrollbar = !parser.isSet(noScrollOption);
    MainWindow *mw = new MainWindow(QUrl(str),js,scrollbar,&pwd);
    mw->setUAString(customUA);
    mw->show();

    int ret=0;
    ret = app.exec();
    qStdOut() << mw->url().toString();
    qStdOut() << "\n";
    (*mw).~MainWindow();

    return ret;
}
