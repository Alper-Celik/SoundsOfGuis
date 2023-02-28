#pragma once
namespace sog {
enum class
    element_type { // mostly based on ARIA roles see
                   // https://www.w3.org/TR/wai-aria-1.1/#roles_categorization
      unknown_element,

      window,

      button,
      checkbox,
      link,
      menuitem,
      menuitemcheckbox,
      menuitemradio,

      listitem,
      list,
      listbox

    };
} // namespace sog
