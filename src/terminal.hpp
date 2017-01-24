#pragma once

#include "vte_terminal.hpp"
#include "config.hpp"

class terminal final : public vte::terminal {

    constexpr static const char *term = "xterm";
    const config &config_;
    int child_pid_;

    static char *get_shell();
    void load_theme();
    int connect_shell();
    static bool key_press_cb(VteTerminal *, GdkEventKey *event, terminal *term);

public:

    terminal(const config &config);

};

