#pragma once

#ifndef __linux__  // ---------------------- Windows, macOS impl. --------------------------// 

#include <QWidget>
#include <QWebEnginePage>

QT_BEGIN_NAMESPACE
class QScrollArea;
QT_END_NAMESPACE

namespace Robomongo
{
    // ------------------ WelcomeTab
    class WelcomeTab : public QWidget
    {
        Q_OBJECT
    public:
        WelcomeTab(QScrollArea* parent = nullptr);
        QScrollArea* getParent() const { return _parent; }
        void resize() { /* Not implemented for Windows and macOS */}

    private:
        QScrollArea* _parent;
    };

    // ------------------ MyWebPage
    class MyWebPage : public QWebEnginePage
    {
        Q_OBJECT
    public:
        MyWebPage(QObject* parent = nullptr) : QWebEnginePage(parent) {}
        bool acceptNavigationRequest(
            QUrl const& url, NavigationType type, bool /*isMainFrame*/) override;
    };
}

#else   // -------------------------------- Linux impl. ------------------------------------//

#include <QWidget>

QT_BEGIN_NAMESPACE
class QScrollArea;
QT_END_NAMESPACE

namespace Robomongo
{
    class WelcomeTab : public QWidget
    {
        Q_OBJECT

    public:
        WelcomeTab(QScrollArea *parent = nullptr);
        ~WelcomeTab();
        QScrollArea* getParent() const { return _parent; }
        void resize() {}

    private:
        QScrollArea* _parent;
    };

}

#endif // -------------------------------- end of Linux ------------------------------------// 
