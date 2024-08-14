#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>

#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include "JsonGuard.h"
#include "globals.h"

int main(int argc, char **argv) {
    try {
        setPaths();
        checkConfig();
        checkRequests();
        checkAnswers();
    } catch (const std::exception &e) {
        std::cerr << e.what();
        return -1;
    }

    InvertedIndex idx;
    idx.UpdateDocumentBase(ConverterJSON::getTextDocuments(jsonDir, resourcesDir));
    SearchServer server(idx);
    auto answers = server.search(ConverterJSON::getRequests(jsonDir), ConverterJSON::getResponsesLimit(jsonDir));
    ConverterJSON::putAnswers(answers, jsonDir);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QString mainQmlPath = QString::fromStdString(mainQmlFile.string());
    const QUrl url = QUrl::fromLocalFile(mainQmlPath);
    QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreated,
            &app,
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);


    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
