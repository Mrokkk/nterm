#pragma once

#include <gtkmm/widget.h>
#include <vte/vte.h>
#include <utility>

namespace vte {

class terminal {

    VteTerminal *vte_;

public:

#define VTE_TERMINAL_METHOD(ret_type, name) \
    template <typename ...Params> \
    ret_type name(Params &&...params) { \
        return vte_terminal_##name(vte_, std::forward<Params>(params)...); \
    }

    terminal() {
        vte_ = VTE_TERMINAL(vte_terminal_new());
    }

    auto &widget() {
        return *Glib::wrap(&vte_->widget);
    }

    auto vte() {
        return vte_;
    }

    VTE_TERMINAL_METHOD(void, watch_child)
    VTE_TERMINAL_METHOD(gboolean, spawn_sync)
    VTE_TERMINAL_METHOD(void, copy_clipboard)
    VTE_TERMINAL_METHOD(void, paste_clipboard)
    VTE_TERMINAL_METHOD(void, set_selection_block_mode)
    VTE_TERMINAL_METHOD(void, set_audible_bell)
    VTE_TERMINAL_METHOD(void, set_font_scale)
    VTE_TERMINAL_METHOD(void, set_scroll_on_output)
    VTE_TERMINAL_METHOD(void, set_scroll_on_keystroke)
    VTE_TERMINAL_METHOD(void, set_rewrap_on_resize)
    VTE_TERMINAL_METHOD(void, set_color_bold)
    VTE_TERMINAL_METHOD(void, set_color_foreground)
    VTE_TERMINAL_METHOD(void, set_color_background)
    VTE_TERMINAL_METHOD(void, set_color_cursor)
    VTE_TERMINAL_METHOD(void, set_color_cursor_foreground)
    VTE_TERMINAL_METHOD(void, set_color_highlight)
    VTE_TERMINAL_METHOD(void, set_color_highlight_foreground)
    VTE_TERMINAL_METHOD(void, set_colors)
    VTE_TERMINAL_METHOD(void, set_default_colors)
    VTE_TERMINAL_METHOD(void, set_cursor_blink_mode)
    VTE_TERMINAL_METHOD(void, set_cursor_shape)
    VTE_TERMINAL_METHOD(void, set_scrollback_lines)
    VTE_TERMINAL_METHOD(void, set_font)
    VTE_TERMINAL_METHOD(void, set_allow_bold)
    VTE_TERMINAL_METHOD(void, set_backspace_binding)
    VTE_TERMINAL_METHOD(void, set_mouse_autohide)
    VTE_TERMINAL_METHOD(void, reset)

};

} // namespace vte

