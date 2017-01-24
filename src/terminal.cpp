#include "terminal.hpp"

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
    set_scroll_on_output(true);
    set_scroll_on_keystroke(true);
    set_audible_bell(false);
    set_allow_bold(true);
    search_set_wrap_around(true);
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
    env = g_environ_setenv(env, "TERM", term, TRUE);
    if (spawn_sync(VTE_PTY_DEFAULT, nullptr, default_argv, env, G_SPAWN_SEARCH_PATH, nullptr, nullptr, &child_pid_, nullptr, &error)) {
        watch_child(child_pid_);
    } else {
        g_printerr("Command failed to run: %s\n", error->message);
        return EXIT_FAILURE;
    }
    g_strfreev(env);
    return EXIT_SUCCESS;
}

void terminal::grab_focus() {
    gtk_widget_grab_focus(widget());
}

