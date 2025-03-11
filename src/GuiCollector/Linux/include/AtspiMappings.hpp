#pragma once
#include "GuiElementAtspi2.hpp"
#include <atspi/atspi.h>
#include <unordered_map>
namespace sog {

inline std::unordered_map<AtspiRole, sog::element_type> AtspiMapping{
    {ATSPI_ROLE_PUSH_BUTTON, element_type::button},
    {ATSPI_ROLE_CHECK_BOX, element_type::checkbox},

    {ATSPI_ROLE_MENU_ITEM, element_type::menuitem},
    {ATSPI_ROLE_SEPARATOR, element_type::separator},

    {ATSPI_ROLE_LIST, element_type::list},
    {ATSPI_ROLE_LIST_ITEM, element_type::listitem},
    {ATSPI_ROLE_LIST_BOX, element_type::listbox},

    {ATSPI_ROLE_PAGE_TAB, element_type::tab},
    {ATSPI_ROLE_PAGE_TAB_LIST, element_type::tablist},

    {ATSPI_ROLE_LINK, element_type::link},

    {ATSPI_ROLE_TABLE, element_type::table},
    {ATSPI_ROLE_TABLE_CELL, element_type::cell},
    {ATSPI_ROLE_TABLE_ROW_HEADER, element_type::rowheader},
    {ATSPI_ROLE_ROW_HEADER, element_type::rowheader},
    {ATSPI_ROLE_TABLE_COLUMN_HEADER, element_type::columnheader},
    {ATSPI_ROLE_COLUMN_HEADER, element_type::columnheader}

};
} // namespace sog
