#include "nterm.hpp"

int main(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.nterm.base");
    config global_config(std::string{g_get_user_config_dir()} + "/nterm/config");
    nterm nterm_instance(global_config);
    return app->run(nterm_instance);
}

