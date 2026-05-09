#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class WillyGainAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit WillyGainAudioProcessorEditor (WillyGainAudioProcessor&);
    ~WillyGainAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    WillyGainAudioProcessor& audioProcessor;

    juce::Slider gainSlider;
    juce::Label  gainLabel;

    // Attachment keeps the slider and the APVTS parameter in sync automatically
    juce::AudioProcessorValueTreeState::SliderAttachment gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WillyGainAudioProcessorEditor)
};
