#include "playersurface.h"
#include <QGuiApplication>
#include <QMediaPlayer>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <QtGlobal>

QString link("https://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4");

void launch_player()
{
    QUrl url(link);
    auto surface = new PlayerVideoSurface;
    auto player = new QMediaPlayer;

    QObject::connect(player, &QMediaPlayer::stateChanged,
                     [](QMediaPlayer::State newState) { qDebug() << "stateChanged: " << newState; });
    QObject::connect(player, &QMediaPlayer::positionChanged,
                     [](qint64 position) { qDebug() << "positionChanged: " << position; });
    QObject::connect(player, &QMediaPlayer::videoAvailableChanged,
                     [](bool videoAvailable) { qDebug() << "videoAvailableChanged: " << videoAvailable; });
    QObject::connect(player, &QMediaPlayer::mediaStatusChanged,
                     [](QMediaPlayer::MediaStatus status) { qDebug() << "mediaStatusChanged: " << status; });
    QObject::connect(player, qOverload<QMediaPlayer::Error>(&QMediaPlayer::error),
                     [](QMediaPlayer::Error error) { qDebug() << "error: " << error; });

    player->setVideoOutput(surface);
    player->setMedia(url);
    player->play();
}

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
            QTimer::singleShot(2500, launch_player);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
