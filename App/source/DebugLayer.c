#include "DebugLayer.h"

#include <Core/Base.h>
#include <Core/Log.h>

#include <Graphics/Renderer.h>

#include <UI/UI.h>
#include <nuklear.h>

static void Template()
{
    if (nk_begin(UI.context, "Demo", nk_rect(450, 150, 230, 250),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        enum
        {
            EASY,
            HARD
        };
        static int op = EASY;
        static int property = 20;

        nk_layout_row_static(UI.context, 30, 80, 1);
        if (nk_button_label(UI.context, "button"))
            INFO("Button pressed!");
        nk_layout_row_dynamic(UI.context, 30, 2);
        if (nk_option_label(UI.context, "easy", op == EASY))
            op = EASY;
        if (nk_option_label(UI.context, "hard", op == HARD))
            op = HARD;
        nk_layout_row_dynamic(UI.context, 22, 1);
        nk_property_int(UI.context, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(UI.context, 20, 1);
        nk_label(UI.context, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(UI.context, 25, 1);

        static struct nk_colorf clearColor = {0.f, 0.f, 0.f, 1.f};
        if (nk_combo_begin_color(UI.context, nk_rgb_cf(clearColor), nk_vec2(nk_widget_width(UI.context), 400)))
        {

            nk_layout_row_dynamic(UI.context, 120, 1);
            clearColor = nk_color_picker(UI.context, clearColor, NK_RGBA);

            nk_layout_row_dynamic(UI.context, 25, 1);
            clearColor.r = nk_propertyf(UI.context, "#R:", 0, clearColor.r, 1.0f, 0.01f, 0.005f);
            clearColor.g = nk_propertyf(UI.context, "#G:", 0, clearColor.g, 1.0f, 0.01f, 0.005f);
            clearColor.b = nk_propertyf(UI.context, "#B:", 0, clearColor.b, 1.0f, 0.01f, 0.005f);
            clearColor.a = nk_propertyf(UI.context, "#A:", 0, clearColor.a, 1.0f, 0.01f, 0.005f);

            nk_combo_end(UI.context);

            v4 finalClearColor = (v4){clearColor.r, clearColor.g, clearColor.b, clearColor.a};
            Renderer.clearColor = NormalizedToColor(&finalClearColor);
        }
    }
    nk_end(UI.context);
}

void DrawDebugMenu()
{
    static struct nk_colorf clearColor = {0.f, 0.f, 0.f, 1.f};
    nk_begin(UI.context, "Debug Menu", nk_rect(450, 150, 230, 250),
             NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE);
    {
        nk_layout_row_dynamic(UI.context, 20, 1);
        nk_label(UI.context, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(UI.context, 25, 1);

        static struct nk_colorf clearColor = {0.f, 0.f, 0.f, 1.f};
        if (nk_combo_begin_color(UI.context, nk_rgb_cf(clearColor), nk_vec2(nk_widget_width(UI.context), 400)))
        {

            nk_layout_row_dynamic(UI.context, 120, 1);
            clearColor = nk_color_picker(UI.context, clearColor, NK_RGBA);

            nk_layout_row_dynamic(UI.context, 25, 1);
            clearColor.r = nk_propertyf(UI.context, "#R:", 0, clearColor.r, 1.0f, 0.01f, 0.005f);
            clearColor.g = nk_propertyf(UI.context, "#G:", 0, clearColor.g, 1.0f, 0.01f, 0.005f);
            clearColor.b = nk_propertyf(UI.context, "#B:", 0, clearColor.b, 1.0f, 0.01f, 0.005f);
            clearColor.a = nk_propertyf(UI.context, "#A:", 0, clearColor.a, 1.0f, 0.01f, 0.005f);

            nk_combo_end(UI.context);

            v4 finalClearColor = (v4){clearColor.r, clearColor.g, clearColor.b, clearColor.a};
            Renderer.clearColor = NormalizedToColor(&finalClearColor);
        }
    }
    nk_end(UI.context);
}
