#include "QtUiController.hpp"

#include <QMetaObject>
#include <QThread>
#include <QTreeWidget>
#include <Qt>
#include <gsl/gsl_util>
#include <qapplication.h>
#include <qwidget.h>

namespace sog {
QtUiController::QtUiController()
    : gui_thread([&] {
        auto argc = 0;
        char **argv = nullptr;
        app_ptr = new QApplication(argc, argv);
        auto free_app = gsl::finally(
            [&] { delete app_ptr; }); // not using smart pointer becouse i want
                                      // it to deleted in this thread
        tree_ptr = new QTreeWidget();
        auto free_tree = gsl::finally([&] { delete tree_ptr; });

        tree_ptr->setColumnCount(2);
        tree_ptr->setHeaderLabels({"platformun verdiği kodataki isim",
                                   "benim programımın algıladığı"});
        tree_ptr->show();

        app_ptr->exec();
      }) {}
QtUiController::~QtUiController() { app_ptr->quit(); }

void QtUiController::update_ui(std::vector<ElementDisplayInfo> added_elements,
                               std::size_t removed_elements) {
  QMetaObject::invokeMethod(
      app_ptr->thread(),
      [&] {
        for (std::size_t i = 0; i < removed_elements; i++) {
          auto item_to_remove =
              tree_ptr->itemAt(tree_ptr->topLevelItemCount() - 1, 0);
          tree_ptr->removeItemWidget(item_to_remove, 0);
          tree_ptr->removeItemWidget(item_to_remove, 1);
        }
        for (auto &&added_element : added_elements) {
          auto toqstr = [](auto str) { return QString::fromStdString(str); };
          auto item = new QTreeWidgetItem(
              tree_ptr, QStringList{toqstr(added_element.native_type_enum_name),
                                    toqstr(added_element.detected_type_name)});
          tree_ptr->addTopLevelItem(item);
        }
      },
      Qt::BlockingQueuedConnection);
}
} // namespace sog
