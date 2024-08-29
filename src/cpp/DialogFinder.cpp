#include "DialogFinder.h"
#include <QFileDialog>
#include <QStringList>
#include <QFileInfo>
#include <QDir>


QString DialogFinder::openFileDialog() {
    QFileDialog fileDialog(nullptr, "choose txt file", "", "(*.txt)");
    if (fileDialog.exec() == QFileDialog::Accepted) {
        QList selectedFiles = fileDialog.selectedFiles();
        if (!selectedFiles.empty()) {
            return selectedFiles.first();
        }
    }
    return "";  // Return empty string if no selection is made
}

QString DialogFinder::openDirDialog() {
    QString pathToDir = QFileDialog::getExistingDirectory(nullptr, "open directory with txt files", "");
    if (!pathToDir.isEmpty()) {
        pathToDir.push_back('*');
    }
    return pathToDir;
}
