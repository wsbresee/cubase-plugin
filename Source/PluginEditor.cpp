#include "PluginProcessor.h"
#include "PluginEditor.h"

GainAudioProcessorEditor::GainAudioProcessorEditor (GainAudioProcessor& p)
    : AudioProcessorEditor (&p),
      audioProcessor (p),
      gainAttachment (p.apvts, "gain", gainSlider)  // binds slider <-> parameter
{
    gainSlider.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    gainSlider.setTextValueSuffix (" dB");
    addAndMakeVisible (gainSlider);

    gainLabel.setText ("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType (juce::Justification::centred);
    gainLabel.setFont (juce::FontOptions (14.0f));
    addAndMakeVisible (gainLabel);

    setSize (280, 220);
}

GainAudioProcessorEditor::~GainAudioProcessorEditor() {}

void GainAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Dark background matching the portfolio's Palenight palette
    g.fillAll (juce::Colour (0xff1a1b26));

    g.setColour (juce::Colour (0xffa78bfa)); // violet accent
    g.setFont (juce::FontOptions (20.0f, juce::Font::bold));
    g.drawFittedText ("GAIN", getLocalBounds().removeFromTop (44),
                      juce::Justification::centred, 1);
}

void GainAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (20);
    area.removeFromTop (30);          // title space
    gainLabel.setBounds (area.removeFromBottom (24));
    gainSlider.setBounds (area);
}
