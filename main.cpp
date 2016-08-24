#include <QApplication>
#include <QNetworkProxy>

#include "shotwindow.h"

int main (int argc, char **argv)
{
    QApplication app(argc, argv);

//	QNetworkProxy proxy;
//	proxy.setType(QNetworkProxy::HttpProxy);
//	proxy.setHostName(QString("proxy.tander"));
//	proxy.setPort(3128);
//	proxy.setUser(QString("zayac_aa"));
//	proxy.setPassword(QString("LtymGj,tls45"));
//	QNetworkProxy::setApplicationProxy(proxy);

    ShotWindow *window = new ShotWindow();
    window->show();

    return app.exec();
}


