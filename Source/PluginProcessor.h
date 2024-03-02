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

    void setWet(float newWet, float newWetV1, float newWetV2);
    void setFeedback(float newFeedback, float newFeedbackV1, float newFeedbackV2);
    void setDelayInSamples(float newDelay);
    void setFrequency(float fqV1, float fqV2);

private:
    
    juce::AudioProcessorValueTreeState _parameters;
    float _sampleRate = 0.0f;
    
    // DELAY
    std::atomic<float>* _wetParameter = nullptr;
    std::atomic<float>* _feedbackParameter  = nullptr;
    std::atomic<float>* _delayTimeParameter  = nullptr;

    float _wet;
    float _feedback;
    float _delayTime;
    
    juce::dsp::DelayLine<float> _delayLine;
    juce::dsp::IIR::Filter<float> _filter;
    std::array<juce::dsp::IIR::Filter<float>, 2> _filters;

    // CHORUS
    std::atomic<float>* _wetV1Parameter = nullptr;
    std::atomic<float>* _feedbackV1Parameter = nullptr;
    std::atomic<float>* _fqV1Parameter = nullptr;

    float _wetV1;
    float _feedbackV1;

    juce::dsp::DelayLine<float> _delayLineV1;
    juce::dsp::IIR::Filter<float> _filterV1;
    std::array<juce::dsp::IIR::Filter<float>, 2> _filtersV1;

    std::atomic<float>* _wetV2Parameter = nullptr;
    std::atomic<float>* _feedbackV2Parameter = nullptr;
    std::atomic<float>* _fqV2Parameter = nullptr;

    float _wetV2;
    float _feedbackV2;

    juce::dsp::DelayLine<float> _delayLineV2;
    juce::dsp::IIR::Filter<float> _filterV2;
    std::array<juce::dsp::IIR::Filter<float>, 2> _filtersV2;


    // GHOST

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BambooForestAudioProcessor)
};
