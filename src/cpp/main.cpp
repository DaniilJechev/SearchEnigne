#include <iostream>

#include <QObject>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>
#include <QAbstractListModel>
#include <QtQuickControls2/QQuickStyle>

#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include "JsonGuard.h"
#include "globals.h"

class MyClass : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE void search() {
        InvertedIndex idx;
        idx.UpdateDocumentBase(ConverterJSON::getTextDocuments(global::jsonDir,
                                                               global::resourcesDir));
        SearchServer server(idx);
        auto answers = server.search(ConverterJSON::getRequests(global::jsonDir),
                                     ConverterJSON::getResponsesLimit(global::jsonDir));
        ConverterJSON::putAnswers(answers, global::jsonDir);
    }
};

int main(int argc, char **argv) {

    std::string runMode = ConverterJSON::getRunMode(global::jsonDir);
    MyClass myClass;
    if (runMode == "console") {
        try {
            checkConfig();
            checkRequests();
            checkAnswers();
        } catch (const std::exception &e) {
            std::cerr << e.what();
            return -1;
        }
        myClass.search();
        return 0;
    } else {
        QQuickStyle::setStyle("Universal");
        QGuiApplication app(argc, argv);
        QQmlApplicationEngine engine;
        QString mainQmlPath = QString::fromStdString(global::mainQmlFile.string());
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

        engine.rootContext()->setContextProperty("myClass", &myClass);
        engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
        engine.addImportPath(":/");
        engine.load(url);

        try {
            checkConfig();
            checkRequests();
            checkAnswers();
        } catch (const std::exception &e) {
            std::cerr << e.what();
            return -1;
        }

        if (engine.rootObjects().isEmpty()) {
            return -1;
        }

        return app.exec();
    }
}

#include "main.moc"
