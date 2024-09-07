#include <iostream>

#include <QObject>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QString>
#include <QIcon>
#include <QtQuickControls2/QQuickStyle>

#include "ConverterJSON.h"
#include "JsonGuard.h"
#include "globals.h"
#include "myWindowListModel.h"
#include "SearchHandler.h"
#include "AlertModel.h"
#include "DialogFinder.h"

int main(int argc, char **argv) {
    std::string runMode = ConverterJSON::getRunMode(global::jsonDir);
    SearchHandler searchHandler;
    GuardWrapper guardWrapper;

    if (runMode == "console") {
        std::string alert = guardWrapper.checkData().toStdString();
        if (!alert.empty()) {
            std::cerr << alert;
            return -1;
        }
        searchHandler.search();
        return 0;

    } else {
        QQuickStyle::setStyle("Universal");
        QApplication app(argc, argv);
        app.setWindowIcon(QIcon(":/icons/appIcon"));

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
        DialogFinder dialogFinder;
        engine.rootContext()->setContextProperty("dialogFinder", &dialogFinder);
        engine.rootContext()->setContextProperty("searchHandler", &searchHandler);
        engine.rootContext()->setContextProperty("guardWrapper", &guardWrapper);
        qmlRegisterSingletonType<ConverterJSON>("ConverterJSON", 1, 0, "ConverterJSON",
                                                [](QQmlEngine *, QJSEngine *) -> QObject * {
                                                    return ConverterJSON::getInstance();
                                                });
        qmlRegisterType<MyWindowListModel>("MyWindowListModel", 1, 0, "WindowListModel");
        qmlRegisterType<AlertModel>("MyAlertModel", 1, 0, "AlertModel");
        // register 2 enum classes
        qmlRegisterUncreatableMetaObject(
            AlertStates::staticMetaObject,
            "AlertStates",
            1, 0,
            "AlertStates",
            "Enum is uncreatable"
        );
        qmlRegisterUncreatableMetaObject(
            ListModelType::staticMetaObject,
            "ListModelType",
            1, 0,
            "ListModelType",
            "Enum is uncreatable"
            );

        engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
        engine.addImportPath(":/");
        engine.load(url);

        return app.exec();
    }
}

