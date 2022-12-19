#pragma once
#include "GuiCollector_impl.hpp"
namespace sog {

class GuiCollector {
private:
  sog::GuiCollector_data data{};

public:
  GuiCollector();
  ~GuiCollector();

  GuiCollector(const GuiCollector &) = delete;
  GuiCollector &operator=(const GuiCollector &) = delete;
};

} // namespace sog
