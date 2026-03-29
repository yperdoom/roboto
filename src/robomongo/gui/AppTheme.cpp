#include "robomongo/gui/AppTheme.h"

#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QPalette>
#include <QColor>

#include "robomongo/core/AppRegistry.h"
#include "robomongo/core/settings/SettingsManager.h"

namespace Robomongo
{
    namespace AppThemeUtils
    {
        QPalette darkPalette()
        {
            QPalette p;
            QColor base(42, 42, 42);
            QColor altBase(50, 50, 50);
            QColor window(53, 53, 53);
            QColor windowText(220, 220, 220);
            QColor text(220, 220, 220);
            QColor button(60, 60, 60);
            QColor buttonText(220, 220, 220);
            QColor highlight(42, 130, 218);
            QColor highlightedText(255, 255, 255);
            QColor mid(40, 40, 40);
            QColor dark(35, 35, 35);
            QColor shadow(20, 20, 20);
            QColor disabledText(128, 128, 128);
            QColor link(42, 170, 218);
            QColor toolTipBase(50, 50, 50);
            QColor toolTipText(220, 220, 220);

            p.setColor(QPalette::Window, window);
            p.setColor(QPalette::WindowText, windowText);
            p.setColor(QPalette::Base, base);
            p.setColor(QPalette::AlternateBase, altBase);
            p.setColor(QPalette::ToolTipBase, toolTipBase);
            p.setColor(QPalette::ToolTipText, toolTipText);
            p.setColor(QPalette::Text, text);
            p.setColor(QPalette::Button, button);
            p.setColor(QPalette::ButtonText, buttonText);
            p.setColor(QPalette::BrightText, Qt::red);
            p.setColor(QPalette::Highlight, highlight);
            p.setColor(QPalette::HighlightedText, highlightedText);
            p.setColor(QPalette::Mid, mid);
            p.setColor(QPalette::Dark, dark);
            p.setColor(QPalette::Shadow, shadow);
            p.setColor(QPalette::Link, link);
            p.setColor(QPalette::LinkVisited, link.darker(120));
            p.setColor(QPalette::Disabled, QPalette::Text, disabledText);
            p.setColor(QPalette::Disabled, QPalette::ButtonText, disabledText);
            p.setColor(QPalette::Disabled, QPalette::WindowText, disabledText);
            return p;
        }

        QPalette lightPalette()
        {
            // Return Qt's default light palette
            return QApplication::style()->standardPalette();
        }

        QColor queryBackground()
        {
            QString theme = AppRegistry::instance().settingsManager()->currentTheme();
            if (theme == "Dark")
                return QColor(42, 42, 42);
            return QColor(231, 229, 228); // original #E7E5E4
        }

        QColor panelBackground()
        {
            QString theme = AppRegistry::instance().settingsManager()->currentTheme();
            if (theme == "Dark")
                return QColor(53, 53, 53);
            return QApplication::palette().color(QPalette::Window);
        }

        void applyTheme(const QString &themeName)
        {
            // Always use Fusion so QPalette is fully honoured
            QApplication::setStyle(QStyleFactory::create("Fusion"));

            if (themeName == "Dark") {
                QApplication::setPalette(darkPalette());
                // Extra stylesheet to cover a few details that QPalette misses
                qApp->setStyleSheet(
                    "QToolTip { color: #dcdcdc; background-color: #323232; border: 1px solid #555; }"
                    "QMenu::separator { background: #555555; height: 1px; }"
                );
            } else {
                QApplication::setPalette(lightPalette());
                qApp->setStyleSheet("");
            }
        }

        QStringList getSupportedThemes()
        {
            return QStringList() << "Dark" << "Light";
        }

        void initTheme()
        {
            QString theme = AppRegistry::instance().settingsManager()->currentTheme();
            applyTheme(theme);
        }
    }
}
