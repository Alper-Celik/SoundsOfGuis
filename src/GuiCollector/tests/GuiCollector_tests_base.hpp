#pragma once
#include "GuiElement.hpp"
#include "point2.hpp"
#include <Qt>
#include <QtQml>
#include <mutex>
#include <qapplication.h>
#include <qqmlapplicationengine.h>
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
struct Gui_test_fixture {
  sog::GuiCollector collector;
  std::mutex gui_init_lock;
  gui_wrapper s;
  sog::Point2<int> window_pos, list_pos, list_item_pos;
  Gui_test_fixture()
      : s(R"(
import QtQuick 2.15
import QtQuick.Controls 2.15
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
        anchors.top: parent

        Accessible.role: Accessible.List
        Text
        {
          text: "List"
          anchors.centerIn: parent
        }

        Rectangle
        {
            width: parent.width;
            height: parent.height / 2 ;
            color: "blue"
            anchors.top: parent
            Accessible.role: Accessible.ListItem
            opacity: 1 / 3;

            Text
            {
              text: "ListItem"
              anchors.centerIn: parent
            }
        }

    }
}                         )",
          gui_init_lock) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds{800}); // let the  gui initilize
    std::unique_lock<std::mutex> test_lock{gui_init_lock};
    QScreen *screen =
        QApplication::primaryScreen(); // TODO: am i leaking memory ?

    auto center = screen->geometry().center().x();

    window_pos =
        sog::Point2<int>{.x = center, .y = screen->geometry().bottom() - 20};
    list_pos = sog::Point2<int>{window_pos / sog::Point2<int>{1, 2}};
    list_item_pos = sog::Point2<int>{list_pos / sog::Point2<int>{1, 2}};

    // getting positions is hacky better solutioun can be used
    // for example getting location data from gui using id's of elements

    sog::GuiCollector collector;
  }
};
