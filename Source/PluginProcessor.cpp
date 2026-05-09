#include "PluginProcessor.h"
#include "PluginEditor.h"

WillyGainAudioProcessor::WillyGainAudioProcessor()
    : AudioProcessor (BusesProperties()
                        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "Parameters", createParameterLayout())
{
}

WillyGainAudioProcessor::~WillyGainAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout WillyGainAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // One parameter: gain in dB. Range -60 to +12, default 0.
    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { "gain", 1 },
        "Gain",
        juce::NormalisableRange<float> (-60.0f, 12.0f, 0.1f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel ("dB")
    ));

    return layout;
}

//==============================================================================
// Boilerplate — every plugin needs these

const juce::String WillyGainAudioProcessor::getName() const { return JucePlugin_Name; }
bool WillyGainAudioProcessor::acceptsMidi()  const          { return false; }
bool WillyGainAudioProcessor::producesMidi() const          { return false; }
bool WillyGainAudioProcessor::isMidiEffect() const          { return false; }
double WillyGainAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int  WillyGainAudioProcessor::getNumPrograms()                              { return 1; }
int  WillyGainAudioProcessor::getCurrentProgram()                           { return 0; }
void WillyGainAudioProcessor::setCurrentProgram (int)                       {}
const juce::String WillyGainAudioProcessor::getProgramName (int)            { return {}; }
void WillyGainAudioProcessor::changeProgramName (int, const juce::String&)  {}

//==============================================================================

void WillyGainAudioProcessor::prepareToPlay (double /*sampleRate*/, int /*samplesPerBlock*/)
{
    // Nothing to prepare for a simple gain plugin.
    // More complex plugins initialise filters, delay lines, etc. here.
}

void WillyGainAudioProcessor::releaseResources() {}

//==============================================================================
// The hot path — called ~every 5–20ms while audio is running

void WillyGainAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                       juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals; // prevents CPU spikes from denormal floats

    auto gainDb     = apvts.getRawParameterValue ("gain")->load();
    auto gainLinear = juce::Decibels::decibelsToGain (gainDb);

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        buffer.applyGain (ch, 0, buffer.getNumSamples(), gainLinear);
}

//==============================================================================

bool WillyGainAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* WillyGainAudioProcessor::createEditor()
{
    return new WillyGainAudioProcessorEditor (*this);
}

//==============================================================================
// Preset save/load — serialise the parameter tree to XML

void WillyGainAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void WillyGainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName (apvts.state.getType()))
        apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// Entry point — the DAW calls this to instantiate the plugin

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WillyGainAudioProcessor();
}
