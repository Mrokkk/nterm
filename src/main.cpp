#include "nterm.hpp"
#include <glibmm/miscutils.h>

int main(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv);
    config global_config(Glib::get_user_config_dir() + "/nterm/config");
    nterm nterm_instance(global_config);
    return app->run(nterm_instance);
}

