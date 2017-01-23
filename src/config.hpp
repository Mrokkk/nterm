#pragma once

#include <experimental/optional>
#include <array>
#include <gtk/gtk.h>

class config_file final {

    std::string filename_;
    GKeyFile *key_file_;

public:

    template <typename T> using optional = std::experimental::optional<T>;

    config_file(const std::string &filename);
    ~config_file();

    template <typename T>
    optional<T> read(const char *, const char *) {
        return {};
    }

};

struct config final {

    struct options final {
        bool mouse_autohide;
        std::string font;
        bool cursor_blink;
        std::string cursor_shape;
    };

    struct colors final {
        using color = std::experimental::optional<GdkRGBA>;
        color foreground;
        color foreground_bold;
        color background;
        color cursor;
        color cursor_foreground;
        color highlight;
        std::array<GdkRGBA, 256> palette;
    };

    options options;
    colors colors;

    config(const std::string &config_file);

};

