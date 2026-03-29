#include "robomongo/gui/widgets/workarea/WelcomeTab.h"

#ifndef __linux__  // --------------------- Windows, macOS impl --------------------------// 

#include <QtWebEngineWidgets>
#include <QDesktopServices>

namespace Robomongo {

    // ------------------ WelcomeTab
    WelcomeTab::WelcomeTab(QScrollArea *parent) :
        QWidget(parent), _parent(parent)
    {
        auto webView = new QWebEngineView(this);
        QUrl const URL {
            "http://files.studio3t.com/rm-feed_3t_io/1.4.3/index.html"        
        };
        webView->setPage(new MyWebPage(this));
        webView->page()->setUrl(URL);
        webView->setContextMenuPolicy(Qt::NoContextMenu);
        webView->page()->triggerAction(QWebEnginePage::WebAction::ReloadAndBypassCache);
        webView->page()->profile()->setHttpCacheType(QWebEngineProfile::HttpCacheType::NoCache);

        auto mainLayout = new QHBoxLayout;
        mainLayout->setContentsMargins(-10, -10, -1, -1);
        mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
        mainLayout->addWidget(webView);
        setLayout(mainLayout);
    }

    // ------------------ MyWebPage
    bool MyWebPage::acceptNavigationRequest(
        QUrl const& url, NavigationType type, bool /*isMainFrame*/)
    {
        if (NavigationTypeLinkClicked == type) {
            QDesktopServices::openUrl(url);
            return false;
        }
        return true;
    }

}

#else   // -------------------------------- Linux impl. ------------------------------------//

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>

namespace Robomongo
{

/* ------------------------------------- Welcome Tab --------------------------------------- */

    WelcomeTab::WelcomeTab(QScrollArea *parent) :
        QWidget(parent), _parent(parent)
    {
        auto titleLabel = new QLabel(
            "<h2 style='color:#2a82da;'>RoboTo</h2>"
        );

        auto subtitleLabel = new QLabel(
            "<p style='color:#aaaaaa;'>Community fork of <b>Robo 3T 1.4.4</b> — picking up where the original left off.</p>"
        );
        subtitleLabel->setWordWrap(true);

        auto changesLabel = new QLabel(
            "<h3>What's new in RoboTo 1.0.0</h3>"
            "<ul>"
            "<li><b>Dark mode</b> — default theme with instant switching in Preferences</li>"
            "<li>Theme-aware tab bar, table view and empty-cell colours</li>"
            "<li>Builds on modern Linux (GCC 15, Qt 5.15, OpenSSL 3.x, CMake 4.x)</li>"
            "<li>Fixed build failures introduced by glibc 2.34+, SCons 4.9+ and GCC 15</li>"
            "</ul>"
        );
        changesLabel->setWordWrap(true);
        changesLabel->setTextFormat(Qt::RichText);

        auto baseLabel = new QLabel(
            "<h3>Base project</h3>"
            "<p>RoboTo is based on <b>Robo 3T 1.4.4</b>, the last official release from Studio 3T "
            "before the project was discontinued. The embedded MongoDB shell version remains <b>4.2</b>.</p>"
            "<p>Original source: <a href='https://github.com/Studio3T/robomongo'>"
            "github.com/Studio3T/robomongo</a></p>"
        );
        baseLabel->setWordWrap(true);
        baseLabel->setTextFormat(Qt::RichText);
        baseLabel->setOpenExternalLinks(true);

        auto layout = new QVBoxLayout;
        layout->setContentsMargins(30, 30, 30, 30);
        layout->setSpacing(12);
        layout->addWidget(titleLabel);
        layout->addWidget(subtitleLabel);
        layout->addSpacing(8);
        layout->addWidget(changesLabel);
        layout->addWidget(baseLabel);
        layout->addStretch();
        setLayout(layout);
    }

    WelcomeTab::~WelcomeTab() {}

}

#endif // -------------------------------- end of Linux impl. ------------------------------------// 
