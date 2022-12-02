#include "qtwview.h"
#include "qtwengineview.h"
#include <QApplication>
#include <QWebEngineView>
#include <QCommandLineParser>
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
    QString pwd=QString(get_current_dir_name());

    QCoreApplication::setOrganizationName("QtNoobs");
    QCoreApplication::setApplicationName("Qtw-Browser");
    QCoreApplication::setApplicationVersion("v0.0.1");
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
    parser.process(app);
    const QStringList args = parser.positionalArguments();
    QString str = args.at(0);
    bool mobileUA = parser.isSet(mobileUAOption);
    bool desktopUA = parser.isSet(desktopUAOption);
//    bool bcustUA = parser.isSet(customUAOption); //not required, but possible
    QString customUA = parser.value(customUAOption);
/*    if(bcustUA){
	qStdOut() << "custom UA set\n";
    } */
    if(customUA==""){
        if(mobileUA){
        //    qStdOut() << "mobile UA set\n";
	    customUA = QString("Mozilla/5.0 (Linux; U; Android 4.4.2; en-us; SCH-I535 Build/KOT49H) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30");
        } else if(desktopUA){
	  //  qStdOut() << "desktop UA set\n";
            customUA = QString("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36 OPR/91.0.4516.77");
        } else{
            customUA = QString("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36 OPR/91.0.4516.77");
	}
    }
//    qStdOut() << "custom UA:";
//    qStdOut() << customUA;
/*
    if(QCoreApplication::arguments().count() < 2)
	return 1;
    QString str (QCoreApplication::arguments().at(1)); //pos 0 = prog path
*/
    MainWindow *mw = new MainWindow(QUrl(str),&pwd);
//    mw->setUAString(QString("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36"));
//    mw->setUAString(QString("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36 OPR/91.0.4516.77"));
    mw->setUAString(customUA);
    mw->show();

    int ret=0;
    ret = app.exec();
    qStdOut() << mw->url().toString();
    qStdOut() << "\n";
    (*mw).~MainWindow();

    return ret;
}
