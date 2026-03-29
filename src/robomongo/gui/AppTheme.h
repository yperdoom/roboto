#pragma once

#include <QPalette>
#include <QString>
#include <QStringList>

namespace Robomongo
{
    enum class ThemeName {
        Dark,
        Light
    };

    namespace AppThemeUtils
    {
        void initTheme();
        void applyTheme(const QString &themeName);
        QStringList getSupportedThemes();
        QPalette darkPalette();
        QPalette lightPalette();

        // Returns the active theme's base background color, for use in
        // widgets that cannot rely solely on QPalette.
        QColor queryBackground();
        QColor panelBackground();
    }
}
