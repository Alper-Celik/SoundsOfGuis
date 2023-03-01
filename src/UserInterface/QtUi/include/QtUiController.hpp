#pragma once
#include "element_type.hpp"

#include <QGuiApplication>

#include <cstddef>
#include <qtreewidget.h>
#include <string>
#include <thread>
#include <vector>

namespace sog {
struct ElementDisplayInfo {
  sog::element_type detected_type;
  std::string detected_type_name;
  std::string native_type_name;
  std::string native_type_enum_name;
};

class QtUiController {
public:
  QApplication *app_ptr;
  QTreeWidget *tree_ptr;
  std::jthread gui_thread;
  std::mutex init_lock;

  QtUiController();
  ~QtUiController();

  void update_gui(std::vector<ElementDisplayInfo> added_elements,
                  std::size_t removed_elements = 0);
};
} // namespace sog
