project(qtdlib C CXX)
cmake_minimum_required(VERSION 3.0.0)

set(DEVICE_MODEL "Ubuntu Touch")
set(SYSTEM_VERSION "unknown")

if (DEFINED ENV{SDK_FRAMEWORK})
    string(REGEX MATCH "[0-9]+\\.[0-9]+" SYSTEM_VERSION  $ENV{SDK_FRAMEWORK})
endif()

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Td 1.8.11 REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Positioning REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

pkg_search_module(THUMBNAILER REQUIRED liblomiri-thumbnailer-qt)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QTDLIB "QTdlib")

set(
    SRC
    # todo
    # messages/content/qtdmessageexpiredphoto.cpp
    # messages/content/qtdmessageexpiredvideo.cpp
    # messages/content/qtdmessagegame.cpp
    # messages/content/qtdmessagegamescore.cpp
    # messages/content/qtdmessageinvoice.cpp
    # messages/content/qtdmessagepassportdatareceived.cpp
    # messages/content/qtdmessagepassportdatasent.cpp
    # messages/content/qtdmessagepaymentsuccessful.cpp
    # messages/content/qtdmessagepaymentsuccessfulbot.cpp
    # messages/content/qtdmessagevenue.cpp
    # messages/content/qtdmessagewebsiteconnected.cpp
    # messages/requests/content/qtdinputmessageanimation.cpp
    # messages/requests/content/qtdinputmessageaudio.cpp
    # messages/requests/content/qtdinputmessagecontact.cpp
    # messages/requests/content/qtdinputmessagedocument.cpp
    # messages/requests/content/qtdinputmessageforwarded.cpp
    # messages/requests/content/qtdinputmessagegame.cpp
    # messages/requests/content/qtdinputmessageinvoice.cpp
    # messages/requests/content/qtdinputmessagesticker.cpp
    # messages/requests/content/qtdinputmessagevenue.cpp
    # messages/requests/content/qtdinputmessagevideo.cpp
    # messages/requests/content/qtdinputmessagevideoNote.cpp
    # messages/requests/content/qtdinputmessagevoiceNote.cpp
	# end todo
    auth/qtdauthcode.cpp
    auth/qtdauthmanager.cpp
    auth/qtdauthparams.cpp
    auth/qtdauthstate.cpp
    auth/qtdauthstatefactory.cpp
    auth/requests/qtdauthcoderesponse.cpp
    auth/requests/qtdauthregistrationresponse.cpp
    auth/requests/qtdauthdeleteaccountresponse.cpp
    auth/requests/qtdauthencryptionkeyresponse.cpp
    auth/requests/qtdauthlogoutresponse.cpp
    auth/requests/qtdauthparametersresponse.cpp
    auth/requests/qtdauthpasswordresponse.cpp
    auth/requests/qtdauthphonenumberresponse.cpp
    auth/requests/qtdauthresendcoderequest.cpp
    call/qtdcalldiscardreason.cpp
    chat/qtdbasicgroupchat.cpp
    chat/qtdchat.cpp
    chat/qtdchatadministratorrights.cpp
    chat/qtdchataction.cpp
    chat/qtdchatactionbar.cpp
    chat/qtdchatactionfactory.cpp
    chat/qtdchatlistmodel.cpp
    chat/qtdchatlistsortfiltermodel.cpp
    chat/qtdchatmember.cpp
    chat/qtdchatmemberstatus.cpp
    chat/qtdchatpermissions.cpp
    chat/qtdchattype.cpp
    chat/qtdchattypefactory.cpp
    chat/qtdchatlist.cpp
    chat/qtdsecretchat.cpp
    chat/qtdsecretchatstate.cpp
    chat/qtdsupergroupchat.cpp
    chat/qtdchatinvitelinkinfo.cpp
    chat/qtdchatposition.cpp
    chat/requests/qtdclosechatrequest.cpp
    chat/requests/qtdclosesecretchatrequest.cpp
    chat/requests/qtdcreateprivatechatrequest.cpp
    chat/requests/qtdcreatenewsecretchatrequest.cpp
    chat/requests/qtddeletechathistoryrequest.cpp
    chat/requests/qtdgetbasicgrouprequest.cpp
    chat/requests/qtdgetchatrequest.cpp
    chat/requests/qtdgetchatsrequest.cpp
    chat/requests/qtdgetsecretchatrequest.cpp
    chat/requests/qtdgetsupergroupfullinforequest.cpp
    chat/requests/qtdgetsupergrouprequest.cpp
    chat/requests/qtdleavechatrequest.cpp
    chat/requests/qtdloadchatsrequest.cpp
    chat/requests/qtdopenchatrequest.cpp
    chat/requests/qtdreportchatrequest.cpp
    chat/requests/qtdsendchatactionrequest.cpp
    chat/requests/qtdsetchatdraftrequest.cpp
    chat/requests/qtdsetchattitlerequest.cpp
    chat/requests/qtdsetpinnedchatsrequest.cpp
    chat/requests/qtdforwardmessagesrequest.cpp
    chat/requests/qtdclosesecretchatrequest.cpp
    chat/requests/qtdsetchatnotificationsettings.cpp
    chat/requests/qtdsearchpublicchatrequest.cpp
    chat/requests/qtdjoinchatrequest.cpp
    chat/requests/qtdcheckchatinvitelinkrequest.cpp
    chat/requests/qtdjoinchatbyinvitelinkrequest.cpp
    chat/requests/qtdsetchatmessagettlrequest.cpp
    chat/requests/qtdchatreportreason.cpp
    client/qtdclient.cpp
    client/qtdhandle.cpp
    client/qtdthread.cpp
    client/requests/qtdcloserequest.cpp
    common/qabstractint64id.cpp
    common/qabstracttdobject.cpp
    common/qtdhelpers.cpp
    common/qtdint.cpp
    common/qtdrequest.cpp
    common/qtdresponse.cpp
    connections/qtdconnectionstate.cpp
    connections/qtdconnectionstatefactory.cpp
    connections/qtdconnectionmanager.cpp
    files/qtdanimation.cpp
    files/qtdaudio.cpp
    files/qtddocument.cpp
    files/qtddownloadfilerequest.cpp
    files/qtdfile.cpp
    files/qtdlocalfile.cpp
    files/qtdphoto.cpp
    files/qtdphotos.cpp
    files/qtdphotosize.cpp
    files/qtdremotefile.cpp
    files/qtdsticker.cpp
    files/qtdvideo.cpp
    files/qtdvideonote.cpp
    files/qtdvoicenote.cpp
    files/qtdthumbnailformat.cpp
    files/qtdthumbnail.cpp
    files/qtdminithumbnail.cpp
    files/sticker/qtdstickertype.cpp
    files/sticker/qtdstickerformat.cpp
    messages/content/qtdformattedtext.cpp
    messages/content/qtdmessageanimation.cpp
    messages/content/qtdmessageunreadlabel.cpp
    messages/content/qtdmessageaudio.cpp
    messages/content/qtdmessagebasicgroupchatcreate.cpp
    messages/content/qtdmessagecall.cpp
    messages/content/qtdmessagechatchangetitle.cpp
    messages/content/qtdmessagechataddmembers.cpp
    messages/content/qtdmessagechatchangephoto.cpp
    messages/content/qtdmessagechatdeletemember.cpp
    messages/content/qtdmessagechatdeletephoto.cpp
    messages/content/qtdmessagechatjoinbylink.cpp
    messages/content/qtdmessagechatsetmessageautodeletetime.cpp
    messages/content/qtdmessagechatupgradefrom.cpp
    messages/content/qtdmessagechatupgradeto.cpp
    messages/content/qtdmessagecustomserviceaction.cpp
    messages/content/qtdmessagecontactregistered.cpp
    messages/content/qtdmessagedate.cpp
    messages/content/qtdmessagedocument.cpp
    messages/content/qtdmessagelocation.cpp
    messages/content/qtdmessagephoto.cpp
    messages/content/qtdmessagepoll.cpp
    messages/content/qtdmessagesticker.cpp
    messages/content/qtdmessagesupergroupchatcreate.cpp
    messages/content/qtdmessagetext.cpp
    messages/content/qtdmessagevideo.cpp
    messages/content/qtdmessagevideonote.cpp
    messages/content/qtdmessagevoicenote.cpp
    messages/content/qtdpoll.cpp
    messages/content/qtdpolloption.cpp
    messages/content/qtdpolltype.cpp
    messages/content/qtdtextentity.cpp
    messages/content/qtdtextentitytype.cpp
    messages/content/qtdlocation.cpp
    messages/content/qtdwebpage.cpp
    messages/content/qtdmessagecontact.cpp
    messages/content/qtdmessageunsupported.cpp
    messages/content/qtdmessagescreenshottaken.cpp
    messages/content/qtdmessagepinmessage.cpp
    messages/qtdchatstate.cpp
    messages/qtddraftmessage.cpp
    messages/qtdmessage.cpp
    messages/qtdmessagecontent.cpp
    messages/qtdmessagecontentfactory.cpp
    messages/qtdmessageinteractioninfo.cpp
    messages/qtdmessagelink.cpp
    messages/qtdmessagesender.cpp
    messages/qtdmessagesenderuser.cpp
    messages/qtdmessagesenderchat.cpp
    messages/qtdmessagelistmodel.cpp
    messages/qtdmessagesendingstate.cpp
    messages/qtdmessageschedulingstate.cpp
    messages/replymarkup/qtdkeyboardbutton.cpp
    messages/replymarkup/qtdkeyboardbuttontype.cpp
    messages/replymarkup/qtdreplymarkup.cpp
    messages/forwardinfo/qtdmessageforwardinfo.cpp
    messages/forwardinfo/qtdmessageforwardorigin.cpp
    messages/forwardinfo/qtdmessageforwardoriginfactory.cpp
    messages/requests/content/qtdinputthumbnail.cpp
    messages/requests/content/qtdinputmessagedocument.cpp
    messages/requests/content/qtdinputmessagephoto.cpp
    messages/requests/content/qtdinputmessagecontact.cpp
    messages/requests/content/qtdinputmessagevideo.cpp
    messages/requests/content/qtdinputmessageaudio.cpp
    messages/requests/content/qtdinputmessagetext.cpp
    messages/requests/content/qtdinputmessageaudio.cpp
    messages/requests/content/qtdinputmessagevideo.cpp
    messages/requests/content/qtdinputmessagevoicenote.cpp
    messages/requests/content/qtdinputmessagelocation.cpp
    messages/requests/content/qtdinputmessagesticker.cpp
    messages/requests/qtddeletemessagesrequest.cpp
    messages/requests/qtdgetchathistoryrequest.cpp
    messages/requests/qtdeditmessagecaptionrequest.cpp
    messages/requests/qtdeditmessagetextrequest.cpp
    messages/requests/qtdgetmessagerequest.cpp
    messages/requests/qtdgetmessagelinkrequest.cpp
    messages/requests/qtdinputmessagecontent.cpp
    messages/requests/qtdinputmessagecontentattachmentcaption.cpp
    messages/requests/qtdinputmessagecontentfactory.cpp
    messages/requests/qtdsendmessagerequest.cpp
    messages/requests/qtdviewmessagesrequest.cpp
    messages/requests/qtdopenmessagecontentrequest.cpp
    messages/requests/qtdmessagesendoptions.cpp
    messages/requests/qtdsetpollanswerrequest.cpp
    messages/requests/qtdsendmessagealbumrequest.cpp
    models/QmlObjectListModel.cpp
    models/QmlVariantListModel.cpp
    network/qtdnetworktype.cpp
    network/requests/qtdsetnetworktype.cpp
    notifications/qtdenablenotifications.cpp
    notifications/qtdnotificationsettings.cpp
    notifications/qtdregisterdevicerequest.cpp
    quick/plugin.cpp
    quick/users.cpp
    quick/contacts.cpp
    settings/qtdproxy.cpp
    settings/qtdproxytype.cpp
    settings/qtdsettings.cpp
    settings/requests/qtdgetproxiesrequest.cpp
    settings/requests/qtdaddproxyrequest.cpp
    settings/requests/qtdeditproxyrequest.cpp
    settings/requests/qtdenableproxyrequest.cpp
    settings/requests/qtddisableproxyrequest.cpp
    settings/requests/qtdpingproxyrequest.cpp
    settings/requests/qtdremoveproxyrequest.cpp
    stickers/qtdstickersets.cpp
    stickers/qtdstickerset.cpp
    user/qtdemojistatus.cpp
    user/qtdprofilephoto.cpp
    user/qtduser.cpp
    user/qtdcontact.cpp
    user/qtduserfullinfo.cpp
    user/qtdusernames.cpp
    user/qtdusers.cpp
    user/qtduserstatus.cpp
    user/qtduserstatusfactory.cpp
    user/qtdusertype.cpp
    user/requests/qtdblockuserrequest.cpp
    user/requests/qtdgetuserrequest.cpp
    user/requests/qtdimportcontactsrequest.cpp
    user/requests/qtdremovecontactsrequest.cpp
    user/requests/qtdgetcontactsrequest.cpp
    user/requests/qtdgetuserfullinforequest.cpp
    user/requests/qtdsearchuserbyphonenumberrequest.cpp
    utils/qtdtextformatter.cpp
    utils/qtdmediatools.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_library(${QTDLIB} SHARED ${SRC})
target_link_libraries(${QTDLIB} Qt5::Core Qt5::Quick Qt5::Widgets Qt5::Qml Qt5::Concurrent Qt5::Positioning Qt5::Multimedia Td::tdjson Td::tdapi auxdb)
target_include_directories(${QTDLIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${THUMBNAILER_INCLUDE_DIRS})
target_link_libraries(${QTDLIB} ${THUMBNAILER_LIBRARIES})
get_filename_component(QTDLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

target_compile_definitions(${QTDLIB} PRIVATE -DDEVICE_MODEL="${DEVICE_MODEL}")
target_compile_definitions(${QTDLIB} PRIVATE -DSYSTEM_VERSION="${SYSTEM_VERSION}")

if(DEFINED ENV{TDLIB_DEBUG})
    target_compile_definitions(${QTDLIB} PRIVATE TDLIB_DEBUG)
endif()

install(TARGETS ${QTDLIB} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
