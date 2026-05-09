cmake_minimum_required(VERSION 3.22)
project(GainPlugin VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

# Download JUCE automatically — no separate install needed
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        8.0.4
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(GainPlugin
    COMPANY_NAME                "WillyBresee"
    PLUGIN_MANUFACTURER_CODE    Wbrs
    PLUGIN_CODE                 Gain
    FORMATS                     VST3 AU Standalone
    IS_SYNTH                    FALSE
    NEEDS_MIDI_INPUT            FALSE
    NEEDS_MIDI_OUTPUT           FALSE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD     TRUE          # auto-installs to ~/Library/Audio/Plug-Ins/
    PRODUCT_NAME                "Gain"
)

juce_generate_juce_header(GainPlugin)

target_sources(GainPlugin
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
)

target_compile_definitions(GainPlugin
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(GainPlugin
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
