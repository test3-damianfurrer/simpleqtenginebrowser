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
    QCoreApplication::setApplicationName("Qtw-Desktop");
    QCoreApplication::setApplicationVersion("v0.0.1");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication app(argc, argv);

    if(QCoreApplication::arguments().count() < 2)
	return 1;
    QString str (QCoreApplication::arguments().at(1));
    MainWindow *mw = new MainWindow(QUrl(str),&pwd);
//    mw->setUAString(QString("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36"));
    mw->setUAString(QString("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36 OPR/91.0.4516.77"));
    mw->show();

    int ret=0;
    ret = app.exec();
    qStdOut() << mw->url().toString();
    qStdOut() << "\n";
    (*mw).~MainWindow();

    return ret;
}
