/*
 * Copyright 2020 UBports foundation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Florian Leeber <florian@ubports.com>
 */

#ifndef OFFLOADING_IMAGE_PROVIDER_H_
#define OFFLOADING_IMAGE_PROVIDER_H_

#include <QtQuick/QQuickImageProvider>


class OffloadingImageProvider : public QQuickImageProvider
{
public:
    static const char* PROVIDER_ID;

    OffloadingImageProvider();

    virtual QImage requestImage(const QString& id, QSize* size,
                                const QSize& requestedSize);

};

#endif // OFFLOADING_IMAGE_PROVIDER_H_