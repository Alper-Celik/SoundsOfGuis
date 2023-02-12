#pragma once
#include "GuiCollector.hpp"
#include <atspi/atspi.h>
#include <unordered_map>
namespace sog {

inline std::unordered_map<AtspiRole, sog::element_type> AtspiMapping{
    {AtspiRole::ATSPI_ROLE_INVALID, sog::element_type::unknown_element},

    {AtspiRole::ATSPI_ROLE_ACCELERATOR_LABEL,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_ALERT, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_ANIMATION, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_ARROW, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_CALENDAR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_CANVAS, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_CHECK_BOX, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_CHECK_MENU_ITEM, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_COLOR_CHOOSER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_COLUMN_HEADER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_COMBO_BOX, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DATE_EDITOR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DESKTOP_ICON, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DESKTOP_FRAME, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DIAL, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DIALOG, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DIRECTORY_PANE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DRAWING_AREA, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_FILE_CHOOSER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_FILLER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_FOCUS_TRAVERSABLE,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_FONT_CHOOSER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_FRAME, sog::element_type::window},
    // looks like window in most cases

    {AtspiRole::ATSPI_ROLE_GLASS_PANE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_HTML_CONTAINER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_ICON, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_IMAGE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_INTERNAL_FRAME, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_LABEL, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_LAYERED_PANE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_LIST, sog::element_type::list},

    {AtspiRole::ATSPI_ROLE_LIST_ITEM, sog::element_type::list_item},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_MENU, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_MENU_BAR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_MENU_ITEM, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_OPTION_PANE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_PAGE_TAB, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_PAGE_TAB_LIST, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_PANEL, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_PASSWORD_TEXT, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_POPUP_MENU, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_PROGRESS_BAR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_PUSH_BUTTON, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_RADIO_BUTTON, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_RADIO_MENU_ITEM, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_ROOT_PANE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_ROW_HEADER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_SCROLL_BAR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_SCROLL_PANE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_SEPARATOR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_SLIDER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_SPIN_BUTTON, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_SPLIT_PANE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_STATUS_BAR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TABLE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TABLE_CELL, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TABLE_COLUMN_HEADER,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TABLE_ROW_HEADER,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TEAROFF_MENU_ITEM,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TERMINAL, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TEXT, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TOGGLE_BUTTON, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TOOL_BAR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TOOL_TIP, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TREE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TREE_TABLE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_UNKNOWN, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_VIEWPORT, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_WINDOW, sog::element_type::window},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_EXTENDED, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_HEADER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_FOOTER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_PARAGRAPH, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_RULER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_APPLICATION, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_AUTOCOMPLETE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_EDITBAR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_EMBEDDED, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_ENTRY, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_CHART, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_CAPTION, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DOCUMENT_FRAME, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_HEADING, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_PAGE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_SECTION, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_REDUNDANT_OBJECT,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_FORM, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_LINK, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_INPUT_METHOD_WINDOW,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TABLE_ROW, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TREE_ITEM, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DOCUMENT_SPREADSHEET,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DOCUMENT_PRESENTATION,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DOCUMENT_TEXT, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DOCUMENT_WEB, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DOCUMENT_EMAIL, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_COMMENT, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_LIST_BOX, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_GROUPING, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_IMAGE_MAP, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_NOTIFICATION, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_INFO_BAR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_LEVEL_BAR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TITLE_BAR, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_BLOCK_QUOTE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_AUDIO, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_VIDEO, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DEFINITION, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_ARTICLE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_LANDMARK, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_LOG, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_MARQUEE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_MATH, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_RATING, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_TIMER, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_STATIC, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_MATH_FRACTION, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_MATH_ROOT, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_SUBSCRIPT, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_SUPERSCRIPT, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DESCRIPTION_LIST,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DESCRIPTION_TERM,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_DESCRIPTION_VALUE,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_FOOTNOTE, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_CONTENT_DELETION,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_CONTENT_INSERTION,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_MARK, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_SUGGESTION, sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_PUSH_BUTTON_MENU,
     sog::element_type::unknown_element},
    // TODO: add correct mapping

    {AtspiRole::ATSPI_ROLE_LAST_DEFINED, sog::element_type::unknown_element},
    // TODO: add correct mapping

};
}
