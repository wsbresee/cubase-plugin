#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class GainAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit GainAudioProcessorEditor (GainAudioProcessor&);
    ~GainAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    GainAudioProcessor& audioProcessor;

    juce::Slider gainSlider;
    juce::Label  gainLabel;

    // Attachment keeps the slider and the APVTS parameter in sync automatically
    juce::AudioProcessorValueTreeState::SliderAttachment gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainAudioProcessorEditor)
};
