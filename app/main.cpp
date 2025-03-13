#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QJsonObject>
#include <QDebug>
#include <QQmlContext>
#include <QuickFlux>
#include <quick/plugin.h>
#include <QtQuickControls2/QQuickStyle>
#include "messagedelegatemap.h"
#include "messagecontentdelegatemap.h"
#include <libintl.h>
#include <locale.h>
#include <utils/i18n.h>
#include <ui-tools/offloadingimageprovider.h>
#include <QQuickView>

#define QUICK_FLUX_DISABLE_AUTO_QML_REGISTER

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qSetMessagePattern("%{time} %{type} %{if-category}%{category}: %{endif}(%{function}) %{message}");
    QQuickStyle::setStyle("Suru");

    QCoreApplication::setApplicationName(QStringLiteral("teleports.ubports"));
    QCoreApplication::setOrganizationName(QStringLiteral("teleports.ubports"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("teleports.ubports"));
    QGuiApplication::setApplicationDisplayName(QStringLiteral("TELEports"));

    registerQuickFluxQmlTypes();
    QTdLib::registerQmlTypes();

    setlocale(LC_ALL, "");
    bindtextdomain("teleports.ubports", "/opt/click.ubuntu.com/teleports.ubports/current/share/locale");
    bind_textdomain_codeset("teleports.ubports", "UTF-8");
    textdomain(GETTEXT_DOMAIN.toStdString().c_str());

    MessageDelegateMap delegateMap;
    MessageContentDelegateMap contentDelegateMap;

    QQuickView *view = new QQuickView();

    view->rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    view->rootContext()->setContextProperty(QStringLiteral("delegateMap"), &delegateMap);
    view->rootContext()->setContextProperty(QStringLiteral("contentDelegateMap"), &contentDelegateMap);

    //Inject versioning strings from CI
    QCoreApplication::setApplicationVersion(QStringLiteral(BUILD_VERSION));
    view->rootContext()->setContextProperty(QStringLiteral("devBuildHash"), QStringLiteral(GIT_HASH));
    QQmlEngine *engine = view->engine();
    engine->addImageProvider(QLatin1String("photo"), new OffloadingImageProvider());
    view->setSource(QUrl(QStringLiteral("qrc:/Main.qml")));
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->show();

    int exitCode;
    try
    {
        exitCode = app.exec();
    }
    catch(std::exception& e)
    {
        qWarning() << e.what();
        return -99;
    }
    return exitCode;
}
