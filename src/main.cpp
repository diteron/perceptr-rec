#include "pch.h"

#include "ui/application.h"
#include "ui/main_window.h"

int main(int argc, char *argv[])
{
    const int wndWidth = 800, wndHeight = 650;
    Application app(argc, argv);
    MainWindow mainWnd;
    //mainWnd.setFixedSize(wndWidth, wndHeight);
    //mainWnd.setMaximumSize(wndWidth, wndHeight);
    mainWnd.show();
    int result = app.exec();

    return result;
}
