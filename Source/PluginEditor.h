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
     
    // DELAY
    juce::Label _wetLabel;
    juce::Slider _wetSlider;
    std::unique_ptr<SliderAttachment> _wetAttachment;

    juce::Label _feedbackLabel;
    juce::Slider _feedbackSlider;
    std::unique_ptr<SliderAttachment> _feedbackAttachment;
    
    juce::Label _delayTimeLabel;
    juce::Slider _delayTimeSlider;
    std::unique_ptr<SliderAttachment> _delayTimeAttachment;

    // CHORUS
    juce::Label _wetV1Label;
    juce::Slider _wetV1Slider;
    std::unique_ptr<SliderAttachment> _wetV1Attachment;

    juce::Label _feedbackV1Label;
    juce::Slider _feedbackV1Slider;
    std::unique_ptr<SliderAttachment> _feedbackV1Attachment;

    juce::Label _frequencyV1Label;
    juce::Slider _frequencyV1Slider;
    std::unique_ptr<SliderAttachment> _frequencyV1Attachment;

    juce::Label _wetV2Label;
    juce::Slider _wetV2Slider;
    std::unique_ptr<SliderAttachment> _wetV2Attachment;

    juce::Label _feedbackV2Label;
    juce::Slider _feedbackV2Slider;
    std::unique_ptr<SliderAttachment> _feedbackV2Attachment;

    juce::Label _frequencyV2Label;
    juce::Slider _frequencyV2Slider;
    std::unique_ptr<SliderAttachment> _frequencyV2Attachment;

    juce::Image _background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BambooForestAudioProcessorEditor)
};
