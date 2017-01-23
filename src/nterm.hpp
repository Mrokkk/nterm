#pragma once

#include "terminal.hpp"
#include "config.hpp"

class nterm final {

    const config &global_config_;
    terminal terminal_;

    void connect_signals();
    static gboolean key_press_cb(VteTerminal *, GdkEventKey *event, nterm *list);
    static gboolean terminal_focus_cb(VteTerminal *vte, GdkEventKey *, nterm *list);

public:

    nterm(const config &conf)
            : global_config_(conf), terminal_(global_config_) {
        connect_signals();
        terminal_.grab_focus();
    }

    auto &get_terminal() {
        return terminal_;
    }

};

