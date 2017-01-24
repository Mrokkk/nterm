#pragma once

#include "terminal.hpp"
#include "config.hpp"
#include <gtkmm/window.h>

class nterm final : public Gtk::Window {

    const config &global_config_;
    terminal terminal_;

    bool focus_cb(GdkEventFocus *);
    void configure_window();

public:

    nterm(const config &conf);

};

