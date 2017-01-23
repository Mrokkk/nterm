#include "nterm.hpp"

namespace {

void exit_success(VteTerminal *) {
    gtk_main_quit();
    exit(EXIT_SUCCESS);
}

gboolean focus_cb(GtkWindow *window) {
    gtk_window_set_urgency_hint(window, false);
    return false;
}

void on_alpha_screen_changed(GtkWindow *window, GdkScreen *, void *) {
    GdkScreen *screen = gtk_widget_get_screen(GTK_WIDGET(window));
    GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
    if (!visual)
        visual = gdk_screen_get_system_visual(screen);
    gtk_widget_set_visual(GTK_WIDGET(window), visual);
}

void configure_window(GtkWindow *window) {
    g_signal_connect(window, "destroy", G_CALLBACK(exit_success), nullptr);
    g_signal_connect(window, "focus-in-event",  G_CALLBACK(focus_cb), nullptr);
    g_signal_connect(window, "focus-out-event", G_CALLBACK(focus_cb), nullptr);
    g_signal_connect(window, "screen-changed", G_CALLBACK(on_alpha_screen_changed), nullptr);
    gtk_window_set_decorated(window, false);
    gtk_window_set_title(window, "nterm");
    on_alpha_screen_changed(window, nullptr, nullptr);
}

void parse_argv(int argc, char **argv) {
    GError *error = nullptr;
    gboolean version = false;
    auto context = g_option_context_new(nullptr);
    const GOptionEntry entries[] = {
        {"version", 'v', 0, G_OPTION_ARG_NONE, &version, "Version info", nullptr},
        {nullptr, 0, 0, G_OPTION_ARG_NONE, nullptr, nullptr, nullptr}
    };
    g_option_context_add_main_entries(context, entries, nullptr);
    g_option_context_add_group(context, gtk_get_option_group(true));
    if (!g_option_context_parse(context, &argc, &argv, &error)) {
        g_printerr("Failed to parse: %s\n", error->message);
        g_clear_error (&error);
        exit(EXIT_FAILURE);
    }
    g_option_context_free(context);
    if (version) {
        g_print("nterm %s\n", NTERM_VERSION);
        exit(EXIT_SUCCESS);
    }
}

} // namespace anon

int main(int argc, char **argv) {
    parse_argv(argc, argv);
    auto window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    std::string config_file{g_get_user_config_dir()};
    config_file += "/nterm/config";
    config global_config(config_file);
    configure_window(GTK_WINDOW(window));
    nterm nterm_instance(global_config);
    gtk_container_add(GTK_CONTAINER(window), nterm_instance.get_terminal().widget());
    gtk_widget_show_all(window);
    gtk_main();
    return EXIT_FAILURE;
}

