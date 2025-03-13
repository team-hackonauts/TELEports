#include "qtdchatreportreason.h"

QTdChatReportReason::QTdChatReportReason(QObject *parent)
    : QTdObject(parent)
{
}

QJsonObject QTdChatReportReason::marshalJson() {
    return QJsonObject{
        { "@type", m_type }
    };
}

QTdChatReportReasonChildAbuse::QTdChatReportReasonChildAbuse(QObject *parent)
    : QTdChatReportReason(parent)
{
    m_type = "chatReportReasonChildAbuse";
}

QTdChatReportReasonCopyright::QTdChatReportReasonCopyright(QObject *parent)
    : QTdChatReportReason(parent)
{
    m_type = "chatReportReasonCopyright";
}

QTdChatReportReasonCustom::QTdChatReportReasonCustom(QObject *parent)
    : QTdChatReportReason(parent)
{
    m_type = "chatReportReasonCustom";
}

QTdChatReportReasonFake::QTdChatReportReasonFake(QObject *parent)
    : QTdChatReportReason(parent)
{
    m_type = "chatReportReasonFake";
}

QTdChatReportReasonPornograhpy::QTdChatReportReasonPornograhpy(QObject *parent)
    : QTdChatReportReason(parent)
{
    m_type = "chatReportReasonPornography";
}

QTdChatReportReasonSpam::QTdChatReportReasonSpam(QObject *parent)
    : QTdChatReportReason(parent)
{
    m_type = "chatReportReasonSpam";
}

QTdChatReportReasonViolence::QTdChatReportReasonViolence(QObject *parent)
    : QTdChatReportReason(parent)
{
    m_type = "chatReportReasonViolence";
}

QTdChatReportReasonUnrelatedLocation::QTdChatReportReasonUnrelatedLocation(QObject *parent)
    : QTdChatReportReason(parent)
{
    m_type = "chatReportReasonUnrelatedLocation";
}


