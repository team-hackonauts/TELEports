// pageutils.js
.pragma library

function isFinishedTransferAfter(fileName, importFileStatus) {
    importFileStatus.set(fileName, true);
    let result = true;
    for (let [ _, value ] of importFileStatus.entries()) {
        if (value !== true) {
            result = false;
            break;
        }
    }
    return result;
}