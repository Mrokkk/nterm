#include "terminal.hpp"
#include <gtkmm/accelgroup.h>

void terminal::load_theme() {
    set_colors(nullptr, nullptr, config_.colors.palette.data(), config_.colors.palette.size());
    if (config_.colors.foreground) {
        set_color_foreground(&*config_.colors.foreground);
        set_color_bold(&*config_.colors.foreground);
    }
    if (config_.colors.foreground_bold) {
        set_color_bold(&*config_.colors.foreground_bold);
    }
    if (config_.colors.cursor) {
        set_color_cursor(&*config_.colors.cursor);
    }
    if (config_.colors.background) {
        set_color_background(&*config_.colors.background);
    }
    if (config_.colors.cursor_foreground) {
        set_color_cursor_foreground(&*config_.colors.cursor_foreground);
    }
    if (config_.colors.highlight) {
        set_color_highlight(&*config_.colors.highlight);
    }
}

terminal::terminal(const config &config)
        : config_(config) {
    connect_shell();
    g_signal_connect(vte(), "key-press-event", G_CALLBACK(key_press_cb), this);
    set_scroll_on_output(true);
    set_scroll_on_keystroke(true);
    set_audible_bell(false);
    set_allow_bold(true);
    set_scrollback_lines(0);
    set_mouse_autohide(config.options.mouse_autohide);
    if (!config.options.font.empty()) {
        auto font = pango_font_description_from_string(config.options.font.c_str());
        set_font(font);
        pango_font_description_free(font);
    }
    set_cursor_blink_mode(VTE_CURSOR_BLINK_ON); // FIXME
    if (config.options.cursor_shape == "block") {
        set_cursor_shape(VTE_CURSOR_SHAPE_BLOCK);
    } else if (config.options.cursor_shape == "ibeam") {
        set_cursor_shape(VTE_CURSOR_SHAPE_IBEAM);
    } else if (config.options.cursor_shape == "underline") {
        set_cursor_shape(VTE_CURSOR_SHAPE_UNDERLINE);
    }
    load_theme();
}

char *terminal::get_shell() {
    if (const char *_env = g_getenv("SHELL"))
        return g_strdup(_env);
    if (char *command = vte_get_user_shell())
        return command;
    return g_strdup("/bin/sh");
}

int terminal::connect_shell() {
    GError *error = nullptr;
    char *default_argv[] = {get_shell(), nullptr};
    auto env = g_get_environ();
    env = g_environ_setenv(env, "TERM", term_, TRUE);
    if (spawn_sync(VTE_PTY_DEFAULT, nullptr, default_argv, env, G_SPAWN_SEARCH_PATH, nullptr, nullptr, &child_pid_, nullptr, &error)) {
        watch_child(child_pid_);
    } else {
        g_printerr("Command failed to run: %s\n", error->message);
        return EXIT_FAILURE;
    }
    g_strfreev(env);
    return EXIT_SUCCESS;
}

bool terminal::key_press_cb(VteTerminal *, GdkEventKey *event, terminal *term) {
    const auto modifiers = event->state & Gtk::AccelGroup::get_default_mod_mask();
    if (modifiers == (Gdk::CONTROL_MASK | Gdk::SHIFT_MASK)) {
        switch (gdk_keyval_to_lower(event->keyval)) {
            case GDK_KEY_c:
                term->copy_clipboard();
                return true;
            case GDK_KEY_v:
                term->paste_clipboard();
                return true;
        }
    }
    return false;
}

