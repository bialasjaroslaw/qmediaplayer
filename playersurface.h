#ifndef PLAYERVIDEOSURFACE_H
#define PLAYERVIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QObject>

class PlayerVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    PlayerVideoSurface(QObject* parent = nullptr)
        : QAbstractVideoSurface(parent)
    {}

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const override;
    bool present(const QVideoFrame& frame) override;
    bool isFormatSupported(const QVideoSurfaceFormat &format) const override;
    bool start(const QVideoSurfaceFormat &format) override;
    void stop() override;
};

#endif // PLAYERVIDEOSURFACE_H
