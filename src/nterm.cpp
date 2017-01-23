#include "nterm.hpp"

void nterm::connect_signals() {
    g_signal_connect(terminal_.vte(), "key-press-event", G_CALLBACK(key_press_cb), this);
    g_signal_connect(terminal_.vte(), "focus-in-event",  G_CALLBACK(terminal_focus_cb), this);
}

gboolean nterm::key_press_cb(VteTerminal *, GdkEventKey *event, nterm *nterm_instance) {
    auto &vte = nterm_instance->get_terminal();
    const auto modifiers = event->state & gtk_accelerator_get_default_mod_mask();
    if (modifiers == (GDK_CONTROL_MASK | GDK_SHIFT_MASK)) {
        switch (gdk_keyval_to_lower(event->keyval)) {
            case GDK_KEY_c:
                vte.copy_clipboard();
                return true;
            case GDK_KEY_v:
                vte.paste_clipboard();
                return true;
        }
    }
    return false;
}

gboolean nterm::terminal_focus_cb(VteTerminal *, GdkEventKey *, nterm *) {
    return false;
}

