
#include <atspi/atspi.h>
int main() {

  atspi_init();
  auto desktop = atspi_get_desktop(
      0); // atspi-2 curruntly doesn't implement virtual desktops
  g_object_unref(desktop);
}
