/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
/**
*/
class BambooForestAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    BambooForestAudioProcessorEditor (BambooForestAudioProcessor& p, juce::AudioProcessorValueTreeState& vts);
    ~BambooForestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BambooForestAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& _valueTreeState;
     
    // Delay sliders
    juce::Label _wetLabel;
    juce::Slider _wetSlider;
    std::unique_ptr<SliderAttachment> _wetAttachment;

    juce::Label _feedbackLabel;
    juce::Slider _feedbackSlider;
    std::unique_ptr<SliderAttachment> _feedbackAttachment;
    
    juce::Label _delayTimeLabel;
    juce::Slider _delayTimeSlider;
    std::unique_ptr<SliderAttachment> _delayTimeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BambooForestAudioProcessorEditor)
};
