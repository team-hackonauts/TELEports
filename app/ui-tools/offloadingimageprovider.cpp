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

#include "offloadingimageprovider.h"

#include <QtGlobal>
#include <QtCore/QFileInfo>
#include <QtGui/QImageReader>

const char* OffloadingImageProvider::PROVIDER_ID = "photo";
const char* EXIF_ORIENTATION_KEY = "Exif.Image.Orientation";

OffloadingImageProvider::OffloadingImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image, QQuickImageProvider::ForceAsynchronousImageLoading)
{
}

QImage OffloadingImageProvider::requestImage(const QString& id,
                                        QSize* size, const QSize& requestedSize)
{
    QUrl url(id);
    QString filePath = url.path();

    QImageReader reader(filePath);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 5, 0))
    reader.setAutoTransform(true);
#endif
    QSize fullSize = reader.size();
    QSize loadSize(fullSize);

    if (fullSize.isValid() && (requestedSize.width() > 0 || requestedSize.height() > 0)) {
        loadSize.scale(requestedSize, Qt::KeepAspectRatio);
        if (loadSize.width() > fullSize.width() || loadSize.height() > fullSize.height()) {
            loadSize = fullSize;
        }
    }

    if (loadSize != fullSize) {
        reader.setScaledSize(loadSize);
    }

    QImage image = reader.read();

    if (size != NULL) {
        *size = image.size();
    }

    return image;

}

