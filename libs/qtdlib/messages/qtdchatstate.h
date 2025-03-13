#ifndef QTDCHATSTATE
#define QTDCHATSTATE

#include <QObject>

class QTdChatState
{
    Q_GADGET
public:
    enum ChatState {
        Default,
        EditingMessage,
        ReplyingToMessage,
    };

    Q_ENUM(ChatState)
private:
    explicit QTdChatState();
};

#endif // QTDCHATSTATE
