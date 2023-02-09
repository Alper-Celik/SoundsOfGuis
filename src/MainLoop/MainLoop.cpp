#include "MainLoop.hpp"

#include <deque>
namespace sog
{

void MainLoop::update_gui_tree()
{
    point2<int> mouse_pos = gui_collector.get_mouse_pos();
    std::optional<GuiElement> element_under_cursor =
        gui_collector.get_control_at_pos(mouse_pos);

    std::deque<sog::GuiElement>
        new_added_elements; // create new deque to protect classes
                            // integrity in case of exception

    for (auto last_element = element_under_cursor; last_element.has_value();
         last_element = last_element->get_parent())
    {
        auto match_iter = std::find(begin(old_element_tree),
                                    end(old_element_tree), *last_element);
        if (match_iter == end(old_element_tree)) // does not contains
        {
            new_added_elements.push_front(*last_element);
        }
        else
        {
            auto old_last_element_iter = end(old_element_tree) - 1;
            removed_element_count = old_last_element_iter - match_iter;
            goto subtree;
        }
    }
    removed_element_count = old_element_tree.size();
subtree:
    added_elements = new_added_elements;
    for (int i = 0; i < removed_element_count; i++)
    {
        old_element_tree.pop_back();
    }
    old_element_tree.insert(end(old_element_tree), begin(added_elements),
                            std::end(added_elements));
};

} // namespace sog
