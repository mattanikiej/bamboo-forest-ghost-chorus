/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class BambooForestAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    BambooForestAudioProcessor();
    ~BambooForestAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setWet(float newWet);
    void setFeedback(float newFeedback);
    void setDelayInSamples(float newDelay);

private:
    
    juce::AudioProcessorValueTreeState _parameters;
    
    // delay
    std::atomic<float>* _wetParameter = nullptr;
    std::atomic<float>* _feedbackParameter  = nullptr;
    std::atomic<float>* _delayTimeParameter  = nullptr;

    float _wet;
    float _feedback;
    float _delayTime;
    
    juce::dsp::DelayLine<float> _delayLine;
    juce::dsp::IIR::Filter<float> _filter;
    std::array<juce::dsp::IIR::Filter<float>, 2> _filters;

    // chorus

    // ghost

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BambooForestAudioProcessor)
};
