import QtQuick 2.9

MessageActionItem {

    function autoDeleteTimeToPrettyPrint(seconds) {
        const SECONDS_IN_A_DAY = 86400;
        const SECONDS_IN_A_MONTH = 2592000;
        const SECONDS_IN_A_YEAR = 31536000;

        var result = "";

        if (seconds >= SECONDS_IN_A_DAY && seconds < SECONDS_IN_A_MONTH) {
            let days = Math.floor(seconds / SECONDS_IN_A_DAY);
            result = i18n.tr("%1 day", "%1 days", days).arg(days);
        } else if (seconds >= SECONDS_IN_A_MONTH && seconds < SECONDS_IN_A_YEAR) {
            let months = Math.floor(seconds / SECONDS_IN_A_MONTH);
            result = i18n.tr("%1 month", "%1 months", months).arg(months);
        } else if (seconds >= SECONDS_IN_A_YEAR) {
            let years = Math.floor(seconds / SECONDS_IN_A_YEAR);
            result = i18n.tr("%1 year", "%1 years", years).arg(years);
        } else {
            result = i18n.tr("%1 second", "% seconds", seconds).arg(seconds);
        }

        return i18n.tr("Auto-delete timer was set to <b>%1</b>").arg(result);

    }

    text: autoDeleteTimeToPrettyPrint(content.messageAutoDeleteTime)
}
