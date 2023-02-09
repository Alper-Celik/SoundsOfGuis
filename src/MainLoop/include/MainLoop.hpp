#pragma once
#include "GuiCollector.hpp"
#include "SoundCode.hpp"
#include <deque>
namespace sog
{
class MainLoop
{
    sog::GuiCollector gui_collector;
    sog::SoundManager sound_manger;

  public:
    std::deque<sog::GuiElement> old_element_tree;
    std::deque<sog::GuiElement> added_elements;
    int removed_element_count{0};

    void update_gui_tree();
    void update_sounds();
};
} // namespace sog
