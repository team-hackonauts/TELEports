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

#include <QDebug>
#include <QUrl>
#include <QTimer>
#include <quagzipfile.h>
#include <QIODevice>
#include <QFile>

#include "qlottieframeprovider.h"
#define WIDTH 512

QLottieFrameProvider::QLottieFrameProvider()
    : QObject()
    , m_surface(0)
    , m_format()
    , m_frameNo(0)
    , m_frameTot(0)
    , m_source("")
    , m_width(512)
    , m_height(512)
    , m_nextFrame(QImage(WIDTH, WIDTH, QImage::Format_ARGB32))
{
    // setFormat(WIDTH, WIDTH, QVideoFrame::Format_ARGB32_Premultiplied);
    setFormat(m_width, m_height, QVideoFrame::Format_ARGB32);
    QTimer::singleShot(17, this, SLOT(timesOut()));
}

void QLottieFrameProvider::setVideoSurface(QAbstractVideoSurface *surface)
{
    if (m_surface != surface && m_surface && m_surface->isActive()) {
        m_surface->stop();
    }
    m_surface = surface;
    if (m_surface && m_format.isValid()) {
        m_surface->start(m_format);
        // qDebug() << "surface format:" << m_surface->surfaceFormat();
        // qDebug() << "surface format:" << m_surface->supportedPixelFormats();
    }
}
void QLottieFrameProvider::setFormat(int width, int height, QVideoFrame::PixelFormat pixelFormat)
{
    QVideoSurfaceFormat format = QVideoSurfaceFormat(QSize(width, height), pixelFormat);
    m_format = format;
    // qDebug() << "format changing" << m_format.pixelFormat();
    if (m_surface)
    {
        if (m_surface->isActive())
        {
            m_surface->stop();
        }
        m_surface->start(m_format);
    }
}
void QLottieFrameProvider::present()
{
    if (m_surface) {
        QTimer::singleShot(17, this, SLOT(timesOut()));
        m_surface->present(QVideoFrame(m_nextFrame));
        emit framePresented();
    }
}
void QLottieFrameProvider::presentFrame()
{
    m_requested = false;
    m_timedOut = false;
    if (m_renderNextFrame) {
        if (m_frameNo > m_frameTot) {
            m_frameNo = 0;
        }
        m_frameNo++;
    }
    renderFrame();
    present();
}
void QLottieFrameProvider::renderFrame()
{
    if (m_width != m_nextFrame.width() || m_height != m_nextFrame.height()) {
        m_nextFrame = QImage(m_width, m_height, QImage::Format_ARGB32);
        setFormat(m_width, m_height, QVideoFrame::Format_ARGB32);
    }
    rlottie::Surface surface((uint32_t*)m_nextFrame.bits(), m_width, m_height, m_width * 4);
    // m_handle = m_animation->render(m_frameNo, surface);
    if (m_animation != NULL) {
        m_animation->renderSync(m_frameNo, surface);
    }
}

void QLottieFrameProvider::requestFrame(const bool nextFrame)
{
    m_renderNextFrame = nextFrame;
    m_requested = true;
    if (m_timedOut == true) {
        presentFrame();
    }
}

void QLottieFrameProvider::timesOut()
{
    m_timedOut = true;
    if (m_requested == true) {
        presentFrame();
    }
}

QUrl QLottieFrameProvider::source() const
{
    return m_source;
}
void QLottieFrameProvider::setSource(QUrl source)
{
    if (m_source != source) {
        m_source = source;
        QString path = m_source.path();
        if (m_source.isValid() && path != "" && QFile::exists(path)) {
            if (path.endsWith(".json")) {
                m_animation = rlottie::Animation::loadFromFile(path.toStdString());
            } else if (path.endsWith(".tgs")) {
                QuaGzipFile *quagzip = new QuaGzipFile(path);
                quagzip->open(QIODevice::ReadOnly);
                m_animation = rlottie::Animation::loadFromData(std::string(quagzip->readAll()), path.split("/").last().toStdString());
            } else {
                qDebug() << "Unsupported file format" << path.split(".").last();
                return;
            }
            m_frameTot = m_animation->totalFrame();
            renderFrame();
        } else {
            qDebug() << "Invalid path, lottie animation file does not exists";
        }
    }
}

qreal QLottieFrameProvider::width() const
{
    return m_width;
}
void QLottieFrameProvider::setWidth(const qreal width)
{
    if (m_width != width) {
        m_width = width;
        emit widthChanged();
    }
}
qreal QLottieFrameProvider::height() const
{
    return m_height;
}
void QLottieFrameProvider::setHeight(const qreal height)
{
    if (m_height != height) {
        m_height = height;
        emit heightChanged();
    }
}
