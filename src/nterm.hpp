#pragma once

#include "terminal.hpp"
#include "config.hpp"

class nterm final : public Gtk::Window {

    const config &global_config_;
    terminal terminal_;

    void connect_signals();
    static gboolean key_press_cb(VteTerminal *, GdkEventKey *event, nterm *list);
    static gboolean terminal_focus_cb(VteTerminal *vte, GdkEventKey *, nterm *list);
    bool focus_cb(GdkEventFocus *);
    void configure_window();

public:

    nterm(const config &conf)
            : global_config_(conf), terminal_(global_config_) {
        configure_window();
        connect_signals();
        Gtk::Widget *vte_widget = Glib::wrap(terminal_.widget());
        add(*vte_widget);
        show_all();
        vte_widget->grab_focus();
    }

    auto &get_terminal() {
        return terminal_;
    }

};

