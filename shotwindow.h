#ifndef SHOTWINDOW_H
#define SHOTWINDOW_H

#include <QMainWindow>

class QWebEngineView;
class QLineEdit;
class QToolButton;

class ShotWindow : public QMainWindow
{
    Q_OBJECT
public:
    ShotWindow(QWidget *parent = 0);
    ~ShotWindow();

public slots:
    void loadStarted();
    void loadFinished(bool success);
    void loadProgress(int progress);
    void takeShot();
    void goButton_clicked();
    void shotByTimer();

private:
    QWebEngineView *view;
    QLineEdit *urlLine;
    QToolButton *goButton;
    QToolButton *shotButton;
    QSize viewSize;
};

#endif // SHOTWINDOW_H

