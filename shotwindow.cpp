#include <QDebug>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QFileDialog>
#include <QPixmap>
#include <QLineEdit>
#include <QGridLayout>
#include <QToolButton>
#include <QTimer>
#include <QWebEnginePage>
#include <QStandardPaths>

#include "shotwindow.h"

ShotWindow::ShotWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);

    view = new QWebEngineView(central);

    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::ScreenCaptureEnabled, true);


    urlLine = new QLineEdit(central);
    urlLine->setText("http://www.yandex.ru/");
    goButton = new QToolButton(central);
    goButton->setText( tr("Go") );

    shotButton = new QToolButton(central);
    shotButton->setText( tr("Take shot") );
    shotButton->setEnabled(false);

    QGridLayout *layout = new QGridLayout(central);
    layout->addWidget(urlLine, 0, 0);
    layout->addWidget(goButton, 0, 1);
    layout->addWidget(shotButton, 0, 2);
    layout->addWidget(view, 1, 0, 1, 3);

    connect(goButton, SIGNAL(clicked()), this, SLOT(goButton_clicked()));

    connect(view, SIGNAL(loadStarted()), this, SLOT(loadStarted()));
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
    connect(view, SIGNAL(loadProgress(int)), this, SLOT(loadProgress(int)));

    connect(shotButton, SIGNAL(clicked(bool)), this, SLOT(takeShot()));
    connect(urlLine, SIGNAL(returnPressed()), this, SLOT(goButton_clicked()));

    setCentralWidget(central);
    goButton->click();
}

ShotWindow::~ShotWindow ()
{}

void ShotWindow::goButton_clicked()
{
    shotButton->setEnabled(false);
    QString url = urlLine->text();
    view->load(QUrl(url));
        view->show();
}

void ShotWindow::loadStarted() {
    qDebug() << Q_FUNC_INFO;
}

void ShotWindow::loadFinished(bool success) {
    qDebug() << Q_FUNC_INFO << success;
    if ( !success ) return;

    shotButton->setEnabled(true);
}

void ShotWindow::loadProgress(int progress)
{
    qDebug() << Q_FUNC_INFO << view->url() << progress;
}

void ShotWindow::shotByTimer()
{

    QSize contentSize = view->page()->contentsSize().toSize();

    QImage image (contentSize, QImage::Format_RGB32);

    QPainter painter(&image);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    view->render(&painter);
    painter.end();


    QString fileName = QDir::homePath() + "/screen-" + QDateTime::currentDateTime().toString("yyyyMMddHHmmsszzz")+ ".png";

    image.save(fileName, "PNG", 100);

    view->resize(viewSize); // restore origin view size
}

void ShotWindow::takeShot()
{
    // save origin view size
    viewSize = view->size();

    // get content size to resize view with it
    QSize contentSize = view->page()->contentsSize().toSize();

    // resize view to content szie
    view->resize(contentSize);

    QTimer timer;
    // give the view about 500 (MAGIC: depends on the actual content size, may not be enought) msec for repaint
    // and take a shot
    timer.singleShot(500, this, SLOT(shotByTimer()));
}

