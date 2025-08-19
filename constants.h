#pragma once
#include <QStringList>

namespace Constants {
    // Component type order
    const inline QStringList TYPE_ORDER = {"Head", "Probe", "Module", "Tip"};

    // Styles
    const inline QString BUTTON_STYLE_PRIMARY =
        "padding: 12px; font-size: 14px; border-radius: 8px;"
        "background-color: #012f6c; color: white; border:none;";
    const inline QString BUTTON_STYLE_SECONDARY =
        "padding: 12px; font-size: 14px; border-radius: 8px;"
        "background-color: #e53c2d; color: white; border:none;";
    const inline QString BUTTON_STYLE_DEFAULT =
        "padding: 12px; font-size: 14px; border-radius: 8px;"
        "background-color: white; color: black; border:1px solid;";
}
