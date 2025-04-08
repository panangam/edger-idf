idf_component_register(
    SRCS
        "main.cpp"
        "ArousalMonitor.cpp"
        "device/ADS1115.cpp"
        "device/Rotary.cpp"
        "device/Button.cpp"
        "ui/tamzen_12.c"
        "ui/view.cpp"
        "ui/actions.cpp"
        "ui/GraphPage.cpp"
        "ui/eez_ui/screens.c"
        "ui/eez_ui/styles.c"
        "ui/eez_ui/ui_font_tamzen_12.c"
        "ui/eez_ui/ui.c"
        "EdgingController.cpp"
        "MotorController.cpp"
    INCLUDE_DIRS
        "."
)

# Suppress -Wmissing-field-initializers warnings
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-missing-field-initializers)
