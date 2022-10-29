#include "qtwview.h"
#include "qtwengineview.h"
#include <QApplication>
#include <QWebEngineView>
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
    QCoreApplication::setApplicationName("Qtw-Mobile");
    QCoreApplication::setApplicationVersion("v0.0.1");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication app(argc, argv);

    if(QCoreApplication::arguments().count() < 2)
	return 1;
    QString str (QCoreApplication::arguments().at(1));
    MainWindow *mw = new MainWindow(QUrl(str),&pwd);
    mw->setUAString(QString("Mozilla/5.0 (Linux; U; Android 4.4.2; en-us; SCH-I535 Build/KOT49H) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30"));
    mw->show();

    int ret=0;
    ret = app.exec();
    qStdOut() << mw->url().toString();
    qStdOut() << "\n";
    (*mw).~MainWindow();

    return ret;
}
