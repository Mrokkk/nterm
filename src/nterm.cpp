#include "nterm.hpp"

nterm::nterm(const config &conf)
        : global_config_(conf), terminal_(global_config_) {
    configure_window();
    add(terminal_.widget());
    show_all();
    terminal_.widget().grab_focus();
}

void nterm::configure_window() {
    signal_focus_in_event().connect(sigc::mem_fun(*this, &nterm::focus_cb));
    signal_focus_out_event().connect(sigc::mem_fun(*this, &nterm::focus_cb));
    set_decorated(false);
    set_title("nterm");
}

bool nterm::focus_cb(GdkEventFocus *) {
    set_urgency_hint(false);
    return false;
}

