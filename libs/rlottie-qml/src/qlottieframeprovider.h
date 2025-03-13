/*
 * Copyright (C) 2021  Michele Castellazzi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * rlottie is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QObject>
#include <QVideoFrame>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include "rlottie.h"

class QLottieFrameProvider: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)
    Q_PROPERTY(QUrl source READ source WRITE setSource)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)

public:
    QLottieFrameProvider();
    ~QLottieFrameProvider() = default;
    QAbstractVideoSurface* videoSurface() const { return m_surface; }
    void setVideoSurface(QAbstractVideoSurface *surface);
    void setFormat(int width, int height, QVideoFrame::PixelFormat pixelFormat);
    QUrl source() const;
    void setSource(const QUrl source);
    qreal width() const;
    void setWidth(const qreal width);
    qreal height() const;
    void setHeight(const qreal height);

public slots:
    void present();
    void presentFrame();
    Q_INVOKABLE void requestFrame(const bool nextFrame = true);
    void timesOut();

signals:
    void framePresented();
    void widthChanged();
    void heightChanged();
private:
    void renderFrame();

    QAbstractVideoSurface *m_surface;
    QVideoSurfaceFormat m_format;
    uint m_frameNo;
    qreal m_frameTot;
    QUrl m_source;
    std::unique_ptr<rlottie::Animation> m_animation;
    std::future<rlottie::Surface> m_handle;
    bool m_requested;
    bool m_timedOut;
    QImage m_nextFrame;
    qreal m_width;
    qreal m_height;
    bool m_renderNextFrame;
};

#endif
