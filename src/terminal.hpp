#pragma once

#include "vte_terminal.hpp"
#include "config.hpp"

class terminal final : public vte::terminal {

    constexpr static const char *term = "xterm";
    const config &config_;
    int child_pid_;

    static char *get_shell();
    void load_theme();

public:

    terminal(const config &config);

    const config &get_config() const {
        return config_;
    }

    int connect_shell();
    void grab_focus();

};

