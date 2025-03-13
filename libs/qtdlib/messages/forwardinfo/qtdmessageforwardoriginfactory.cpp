#include "qtdmessageforwardoriginfactory.h"
#include "qtdmessageforwardorigin.h"

QTdMessageForwardOrigin *QTdMessageForwardOriginFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    QTdMessageForwardOrigin *origin = Q_NULLPTR;
    if (type == "messageForwardOriginChannel") {
        origin = new QTdMessageForwardOriginChannel(parent);
    } else if (type == "messageForwardOriginChat") {
        origin = new QTdMessageForwardOriginChat(parent);
    } else if (type == "messageForwardOriginHiddenUser") {
        origin = new QTdMessageForwardOriginHiddenUser(parent);
    } else if (type == "messageForwardOriginUser") {
        origin = new QTdMessageForwardOriginUser(parent);
    }
    if (origin) {
        origin->unmarshalJson(json);
    }
    return origin;
}
