#include "nterm.hpp"

nterm::nterm(const config &conf)
        : global_config_(conf), terminal_(global_config_) {
    configure_window();
    add(terminal_.widget());
    show_all();
    terminal_.widget().grab_focus();
}

void nterm::on_alpha_screen_changed(const Glib::RefPtr<Gdk::Screen> &) {
    auto screen = this->get_screen();
    auto visual = screen->get_rgba_visual();
    if (!visual)
        visual = screen->get_system_visual();
    gtk_widget_set_visual(GTK_WIDGET(gobj()), visual->gobj());
}

void nterm::configure_window() {
    signal_screen_changed().connect(sigc::mem_fun(*this, &nterm::on_alpha_screen_changed));
    signal_focus_in_event().connect(sigc::mem_fun(*this, &nterm::focus_cb));
    signal_focus_out_event().connect(sigc::mem_fun(*this, &nterm::focus_cb));
    set_decorated(false);
    set_title("nterm");
    on_alpha_screen_changed(Glib::RefPtr<Gdk::Screen>());
}

bool nterm::focus_cb(GdkEventFocus *) {
    set_urgency_hint(false);
    return false;
}

