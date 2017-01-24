#pragma once

#include "terminal.hpp"
#include "config.hpp"

class nterm final : public Gtk::Window {

    const config &global_config_;
    terminal terminal_;

    void connect_signals();
    static gboolean key_press_cb(VteTerminal *, GdkEventKey *event, nterm *list);
    static gboolean terminal_focus_cb(VteTerminal *vte, GdkEventKey *, nterm *list);

public:

    bool focus_cb(GdkEventFocus *) {
        set_urgency_hint(false);
        return false;
    }

    //void on_alpha_screen_changed(GtkWindow *window, GdkScreen *, void *) {
        //GdkScreen *screen = gtk_widget_get_screen(GTK_WIDGET(window));
        //GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
        //if (!visual)
            //visual = gdk_screen_get_system_visual(screen);
        //gtk_widget_set_visual(GTK_WIDGET(window), visual);
    //}

    void configure_window() {
        //g_signal_connect(window, "screen-changed", G_CALLBACK(on_alpha_screen_changed), nullptr);
        signal_focus_in_event().connect(sigc::mem_fun(*this, &nterm::focus_cb));
        signal_focus_out_event().connect(sigc::mem_fun(*this, &nterm::focus_cb));
        set_decorated(false);
        set_title("nterm");
        //on_alpha_screen_changed(window->gobj(), nullptr, nullptr);
    }

    nterm(const config &conf)
            : global_config_(conf), terminal_(global_config_) {
        configure_window();
        connect_signals();
        Gtk::Widget *vte_widget = Glib::wrap(terminal_.widget());
        add(*vte_widget);
        show_all();
        terminal_.grab_focus();
    }

    auto &get_terminal() {
        return terminal_;
    }

};

