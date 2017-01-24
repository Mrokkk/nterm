#pragma once

#include <gtkmm.h>
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
        auto _vte_widget = vte_terminal_new();
        vte_ = VTE_TERMINAL(_vte_widget);
    }

    auto widget() {
        return GTK_WIDGET(vte_);
    }

    auto vte() {
        return vte_;
    }

    VTE_TERMINAL_METHOD(GType, get_type)
    VTE_TERMINAL_METHOD(VtePty *, pty_new_sync)
    VTE_TERMINAL_METHOD(void, watch_child)
    VTE_TERMINAL_METHOD(gboolean, spawn_sync)
    VTE_TERMINAL_METHOD(void, connect_pty_read)
    VTE_TERMINAL_METHOD(void, disconnect_pty_read)
    VTE_TERMINAL_METHOD(void, copy_clipboard)
    VTE_TERMINAL_METHOD(void, paste_clipboard)
    VTE_TERMINAL_METHOD(void, copy_primary)
    VTE_TERMINAL_METHOD(void, paste_primary)
    VTE_TERMINAL_METHOD(void, select_all)
    VTE_TERMINAL_METHOD(void, unselect_all)
    VTE_TERMINAL_METHOD(gboolean, get_selection_block_mode)
    VTE_TERMINAL_METHOD(void, set_selection_block_mode)
    VTE_TERMINAL_METHOD(void, set_audible_bell)
    VTE_TERMINAL_METHOD(void, set_size)
    VTE_TERMINAL_METHOD(void, set_font_scale)
    VTE_TERMINAL_METHOD(gdouble, get_font_scale)
    VTE_TERMINAL_METHOD(gboolean, get_audible_bell)
    VTE_TERMINAL_METHOD(void, set_scroll_on_output)
    VTE_TERMINAL_METHOD(void, set_scroll_on_keystroke)
    VTE_TERMINAL_METHOD(void, set_rewrap_on_resize)
    VTE_TERMINAL_METHOD(gboolean, get_rewrap_on_resize)
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
    VTE_TERMINAL_METHOD(VteCursorBlinkMode, get_cursor_blink_mode)
    VTE_TERMINAL_METHOD(void, set_cursor_shape)
    VTE_TERMINAL_METHOD(VteCursorShape, get_cursor_shape)
    VTE_TERMINAL_METHOD(void, set_scrollback_lines)
    VTE_TERMINAL_METHOD(void, set_font)
    VTE_TERMINAL_METHOD(const PangoFontDescription *, get_font)
    VTE_TERMINAL_METHOD(void, set_allow_bold)
    VTE_TERMINAL_METHOD(gboolean, get_allow_bold)
    VTE_TERMINAL_METHOD(gboolean, get_has_selection)
    VTE_TERMINAL_METHOD(void, set_backspace_binding)
    VTE_TERMINAL_METHOD(void, set_delete_binding)
    VTE_TERMINAL_METHOD(void, set_mouse_autohide)
    VTE_TERMINAL_METHOD(gboolean, get_mouse_autohide)
    VTE_TERMINAL_METHOD(void, reset)

    // Disabled
    //VTE_TERMINAL_METHOD(void, feed)
    //VTE_TERMINAL_METHOD(void, feed_child)
    //VTE_TERMINAL_METHOD(void, feed_child_binary)
    //VTE_TERMINAL_METHOD(void, select_text)
    //VTE_TERMINAL_METHOD(char *, get_selection)
    //VTE_TERMINAL_METHOD(void, set_word_char_exceptions)
    //VTE_TERMINAL_METHOD(const char *, get_word_char_exceptions)
    //VTE_TERMINAL_METHOD(char *, get_text)
    //VTE_TERMINAL_METHOD(char *, get_text_include_trailing_spaces)
    //VTE_TERMINAL_METHOD(char *, get_text_range)
    //VTE_TERMINAL_METHOD(void, get_cursor_position)
    //VTE_TERMINAL_METHOD(void, set_cursor_position)
    //VTE_TERMINAL_METHOD(int, match_add_regex)
    //VTE_TERMINAL_METHOD(void, match_set_cursor_type)
    //VTE_TERMINAL_METHOD(void, match_set_cursor_name)
    //VTE_TERMINAL_METHOD(void, match_remove)
    //VTE_TERMINAL_METHOD(void, match_remove_all)
    //VTE_TERMINAL_METHOD(char *, match_check_event)
    //VTE_TERMINAL_METHOD(gboolean, event_check_regex_simple)
    //VTE_TERMINAL_METHOD(void, search_set_regex)
    //VTE_TERMINAL_METHOD(VteRegex *, search_get_regex)
    //VTE_TERMINAL_METHOD(void, search_set_wrap_around)
    //VTE_TERMINAL_METHOD(gboolean, search_get_wrap_around)
    //VTE_TERMINAL_METHOD(gboolean, search_find_previous)
    //VTE_TERMINAL_METHOD(gboolean, search_find_next)
    //VTE_TERMINAL_METHOD(gboolean, set_encoding)
    //VTE_TERMINAL_METHOD(const char *, get_encoding)
    //VTE_TERMINAL_METHOD(void, set_cjk_ambiguous_width)
    //VTE_TERMINAL_METHOD(int, get_cjk_ambiguous_width)
    //VTE_TERMINAL_METHOD(void, set_pty)
    //VTE_TERMINAL_METHOD(VtePty *, get_pty)
    //VTE_TERMINAL_METHOD(glong, get_char_width)
    //VTE_TERMINAL_METHOD(glong, get_char_height)
    //VTE_TERMINAL_METHOD(glong, get_row_count)
    //VTE_TERMINAL_METHOD(glong, get_column_count)
    //VTE_TERMINAL_METHOD(const char *, get_window_title)
    //VTE_TERMINAL_METHOD(const char *, get_icon_title)
    //VTE_TERMINAL_METHOD(const char *, get_current_directory_uri)
    //VTE_TERMINAL_METHOD(const char *, get_current_file_uri)
    //VTE_TERMINAL_METHOD(void, set_input_enabled)
    //VTE_TERMINAL_METHOD(gboolean, get_input_enabled)
    //VTE_TERMINAL_METHOD(void, get_geometry_hints)
    //VTE_TERMINAL_METHOD(void, set_geometry_hints_for_window)
    //VTE_TERMINAL_METHOD(gboolean, write_contents_sync)

};

} // namespace vte

