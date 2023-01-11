
#include <QApplication>
#include <Qt>
#include <QtQml>
#include <catch2/catch_test_macros.hpp>
#include <qdesktopwidget.h>
#include <qscreen.h>
#include <thread>

struct gui_wrapper {
  std::unique_lock<std::mutex> lock;
  std::jthread gui_thread;
  QApplication *app_ptr;

  gui_wrapper(const char *qml_code, std::mutex &mutex)
      : lock(mutex), gui_thread([&] {
          int temp = 0;
          QApplication app(temp, nullptr);
          app_ptr = &app;
          QQmlApplicationEngine engine;
          engine.loadData(qml_code);
          QMetaObject::invokeMethod(
              app.thread(), [&] { lock.unlock(); }, Qt::QueuedConnection);
          app.exec();
        }) {}
  ~gui_wrapper() { app_ptr->quit(); }
};
TEST_CASE() {
  std::mutex gui_init_lock;
  gui_wrapper s(R"(
import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: root
    visible: true
    visibility:Window.FullScreen

    Rectangle
    {
        width: parent.width;
        height: parent.height / 2;
        color: "red"
        anchors.centerIn: parent

        Accessible.role: Accessible.List
        Rectangle
        {
            width: parent.width;
            height: parent.height / 2;
            color: "blue"
            anchors.centerIn: parent
            Accessible.role: Accessible.ListItem
        }

    }
}
  )",
                gui_init_lock);
  std::unique_lock<std::mutex> test_lock{gui_init_lock};
  QScreen *screen =
      QApplication::primaryScreen(); // TODO: am i leaking memory ?

  screen->geometry().bottom();

  gui_init_lock.lock();
}
