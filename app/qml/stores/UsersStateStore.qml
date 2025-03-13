import QtQuick 2.4
import QuickFlux 1.1
import QTelegram 1.0
import "../actions"

Store {

    property alias me: usersStore.me
    property alias model: usersStore.model
    property alias contactsmodel: contactsStore.model

    Users {
        id: usersStore
    }

    Contacts {
        id: contactsStore
    }

    Filter {
        type: UserStateKey.deleteUser
        onDispatched: {
            usersStore.deleteUser(message.userId)
        }
    }

    Filter {
        type: UserStateKey.addUser
        onDispatched: {
            usersStore.addUser(message.userName, message.firstName, message.lastName)
        }
    }

    Filter {
        type: UserStateKey.addContact
        onDispatched: {
            usersStore.addContact(message.phoneNumber, message.firstName, message.lastName, message.userId)
        }
    }
}
