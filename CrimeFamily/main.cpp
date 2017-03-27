#include "crimetreewindow.h"
#include <QApplication>
#include <QFile>

#include "log.h"
#include "settings.h"

Settings g_settings;

//!
//! \brief initSettings
//! \return
//!
bool initSettings()
{
    if (g_settings.loadSettings())
        return true;
    return false;
}

//!
//! \brief initStylesheet
//! \return
//!
bool initStylesheet()
{
    // Load file
    QFile file_stylesheet(":/qss/style.css");
    // Open file
    if (file_stylesheet.open(QFile::ReadOnly))
    {
        QString style_sheet = QLatin1String(file_stylesheet.readAll());
        qApp->setStyleSheet(style_sheet);
        file_stylesheet.close();
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load settings
    initSettings();

    // Init style
    initStylesheet();

    CrimeTreeWindow w;
    w.showMaximized();

    return a.exec();
}
