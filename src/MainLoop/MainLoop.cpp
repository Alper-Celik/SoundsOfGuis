#include "MainLoop.hpp"
#include "ExceptionUtils.hpp"

#include <boost/predef.h>

#include <deque>
#include <fstream>

namespace fs = std::filesystem;
namespace sog
{
MainLoop::MainLoop()
{
}

void make_dir_if_not_exists(const fs::path &dir)
{
    if (not fs::exists(dir))
    {
        fs::create_directory(dir);
        return;
    }
    if (not fs::is_directory(dir))
    {
        sog::throw_with_trace(std::runtime_error(fmt::format(
            "\"{}\" is not a directory or not exists", dir.string())));
    }
    return;
}
void create_file_if_not_exists(const fs::path &file)
{
    if (not fs::exists(file))
    {
        {
            {
                try
                {
                    std::ofstream create_file(file);
                }
                catch (const std::ios_base::failure &err)
                {
                    sog::throw_with_trace(std::runtime_error(
                        fmt::format("cannot create file at \"{}\"\n"
                                    "with error code: {}\n"
                                    "with low level message: {}\n"
                                    "with high level message: {}",
                                    file.string(), err.code().value(),
                                    err.code().message(), err.what())));
                }
            }
            if (fs::is_regular_file(file))
            {
                return;
            }
            else
            {
                sog::throw_with_trace(std::runtime_error(fmt::format(
                    "cannot create file at \"{}\"", file.string())));
            }
        }
    }
    if (not fs::is_regular_file(file))
    {
        sog::throw_with_trace(std::runtime_error(
            fmt::format("\"{}\" is not a file or not exists", file.string())));
    }
}
fs::path MainLoop::get_config_file()
{
    if (BOOST_OS_LINUX)
    {
        std::optional<fs::path> default_config_file;

        auto xdg_config_dir_ptr = std::getenv("XDG_CONFIG_HOME");
        if (xdg_config_dir_ptr != nullptr and
            std::string_view(xdg_config_dir_ptr) != "")
        {
            fs::path xdg_config_dir{xdg_config_dir_ptr};

            if (not fs::exists(xdg_config_dir))
            {
                sog::throw_with_trace(
                    std::runtime_error("$XDG_CONFIG_HOME does not exist"));
            }
            if (not fs::is_directory(xdg_config_dir))
            {
                sog::throw_with_trace(std::runtime_error(
                    "$XDG_CONFIG_HOME is not a directinoary"));
            }

            make_dir_if_not_exists(xdg_config_dir / sog::program_name);

            fs::path config_file =
                xdg_config_dir / sog::program_name /
                (std::string(sog::config_file_name) + ".toml");

            create_file_if_not_exists(config_file);
            return config_file;
        }

        // TODO: implment multiple dir version of xdg base dir

        char *home_dir_ptr = std::getenv("HOME");
        if (home_dir_ptr == nullptr)
        {
            sog::throw_with_trace(
                std::runtime_error("$HOME enviroment variable is not set"));
        }
        else
        {
            fs::path config_dir = fs::path{home_dir_ptr} / ".config";
            make_dir_if_not_exists(config_dir);
            make_dir_if_not_exists(config_dir / sog::program_name);

            fs::path config_file =
                config_dir / sog::program_name /
                (std::string(sog::config_file_name) + ".toml");
            create_file_if_not_exists(config_file);
            return config_file;
        }
    }

    std::terminate();
}

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
    removed_element_count = old_element_tree.size(); // all elements removed
subtree:
    added_elements = new_added_elements;
    for (int i = 0; i < removed_element_count; i++)
    {
        old_element_tree.pop_back();
    }
    old_element_tree.insert(end(old_element_tree), begin(added_elements),
                            std::end(added_elements));
};

void MainLoop::update_sounds()
{
}

} // namespace sog
