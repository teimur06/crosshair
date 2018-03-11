#include <QApplication>
#include <Qlabel>
#include <QStyle>
#include <QDesktopWidget>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLabel label;
    QPixmap pixmap;
    int x, y;
    QRect rectScreen;
    QCommandLineParser parser;

    int screenNumber = 0;
    QDesktopWidget * desktop = qApp->desktop();
    const QString standartImagPath = ":images/crosshair.png";
    QString imagPath = standartImagPath;
    QCommandLineOption optScreen(QStringList() << "s" << "screen", "Screen number", "screen","0");
    QCommandLineOption optImage(QStringList() << "i" << "image", "Image load", "image");
    QCommandLineOption optWindow(QStringList() << "w" << "window", "The game is open in the window");

    parser.addOption(optScreen);
    parser.addOption(optImage);
    parser.addOption(optWindow);
    parser.addHelpOption();

    parser.process(a);
    bool boolOptScreen = parser.isSet(optScreen);
    bool boolOptImage = parser.isSet(optImage);
    bool window = parser.isSet(optWindow);

    if (boolOptImage) imagPath = parser.value(optImage);
    if (!pixmap.load(imagPath)) pixmap.load(standartImagPath);

    if (boolOptScreen)
    {
        QString argv2 = parser.value(optScreen);
        bool test;
        argv2.toInt(&test);
        if (test) screenNumber = argv2.toInt();
    }

    rectScreen = desktop->screenGeometry(screenNumber);
    x = rectScreen.x() + rectScreen.width()/2 - pixmap.width()/2 ;
    y = rectScreen.y() + rectScreen.height()/2 - (window ? 0 : pixmap.height()/2 ) ;

    label.setAttribute(Qt::WA_TranslucentBackground);
    label.setAttribute(Qt::WA_TransparentForMouseEvents);
    label.setPixmap(pixmap);
    label.setGeometry( x, y, pixmap.width(), pixmap.height() );
    label.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    label.show();
    return a.exec();
}

