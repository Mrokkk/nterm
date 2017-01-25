#include "config.hpp"

config_file::config_file(const std::string &filename)
        : filename_(filename) {
    key_file_.load_from_file(filename);
}

template <>
config_file::optional<bool> config_file::read(const char *section, const char *key) {
    try {
        bool b = key_file_.get_boolean(section, key);
        return b;
    } catch (Glib::KeyFileError) {
        return {};
    }
}

template <>
config_file::optional<std::string> config_file::read(const char *section, const char *key) {
    try {
        auto b = key_file_.get_string(section, key);
        return b;
    } catch (Glib::KeyFileError) {
        return {};
    }
}

template <>
config_file::optional<GdkRGBA> config_file::read(const char *section, const char *key) {
    if (auto str_color = read<std::string>(section, key)) {
        GdkRGBA color;
        if (gdk_rgba_parse(&color, (*str_color).c_str())) {
            return color;
        }
    }
    return {};
}

config::config(const std::string &filename) {
    config_file file(filename);
    options.mouse_autohide = file.read<bool>("options", "mouse_autohide").value_or(true);
    options.font = file.read<std::string>("options", "font").value_or(std::string{"Monospace 10"});
    options.cursor_blink = file.read<bool>("options", "cursor_blink").value_or(true);
    options.cursor_shape = file.read<std::string>("options", "cursor_shape").value_or("block");
    colors.foreground = file.read<GdkRGBA>("colors", "foreground");
    colors.foreground_bold = file.read<GdkRGBA>("colors", "foreground_bold");
    colors.background = file.read<GdkRGBA>("colors", "background");
    colors.cursor = file.read<GdkRGBA>("colors", "cursor");
    colors.cursor_foreground = file.read<GdkRGBA>("colors", "cursor_foreground");
    colors.highlight = file.read<GdkRGBA>("colors", "highlight");
    char color_key[] = "color000";
    for (unsigned i = 0; i < colors.palette.size(); i++) {
        snprintf(color_key, sizeof(color_key), "color%u", i);
        if (auto color = file.read<GdkRGBA>("colors", color_key)) {
            colors.palette[i] = *color;
        } else if (i < 16) {
            colors.palette[i].blue = (((i & 4) ? 0xc000 : 0) + (i > 7 ? 0x3fff: 0)) / 65535.0;
            colors.palette[i].green = (((i & 2) ? 0xc000 : 0) + (i > 7 ? 0x3fff : 0)) / 65535.0;
            colors.palette[i].red = (((i & 1) ? 0xc000 : 0) + (i > 7 ? 0x3fff : 0)) / 65535.0;
            colors.palette[i].alpha = 0;
        } else if (i < 232) {
            const unsigned j = i - 16;
            const unsigned r = j / 36, g = (j / 6) % 6, b = j % 6;
            const unsigned red =   (r == 0) ? 0 : r * 40 + 55;
            const unsigned green = (g == 0) ? 0 : g * 40 + 55;
            const unsigned blue =  (b == 0) ? 0 : b * 40 + 55;
            colors.palette[i].red   = (red | red << 8) / 65535.0;
            colors.palette[i].green = (green | green << 8) / 65535.0;
            colors.palette[i].blue  = (blue | blue << 8) / 65535.0;
            colors.palette[i].alpha = 0;
        } else if (i < 256) {
            const unsigned shade = 8 + (i - 232) * 10;
            colors.palette[i].red = colors.palette[i].green = colors.palette[i].blue = (shade | shade << 8) / 65535.0;
            colors.palette[i].alpha = 0;
        }
    }
}

