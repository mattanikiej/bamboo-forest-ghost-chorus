/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BambooForestAudioProcessorEditor::BambooForestAudioProcessorEditor (BambooForestAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), _valueTreeState (vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    // Delay
    _wetLabel.setText ("Wet", juce::dontSendNotification);
    addAndMakeVisible (_wetLabel);
    
    addAndMakeVisible (_wetSlider);
    _wetSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    _wetSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    _wetSlider.setPopupDisplayEnabled (true, false, this);
    _wetSlider.setTextValueSuffix (" - Wet");
    _wetAttachment.reset (new SliderAttachment (_valueTreeState, "wet", _wetSlider));
    
    _feedbackLabel.setText ("Feedback", juce::dontSendNotification);
    addAndMakeVisible (_feedbackLabel);
    
    addAndMakeVisible (_feedbackSlider);
    _feedbackSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    _feedbackSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    _feedbackSlider.setPopupDisplayEnabled (true, false, this);
    _feedbackSlider.setTextValueSuffix (" - Feedback");
    _feedbackAttachment.reset (new SliderAttachment (_valueTreeState, "feedback", _feedbackSlider));
    
    _delayTimeLabel.setText ("Delay Time", juce::dontSendNotification);
    addAndMakeVisible (_delayTimeLabel);
    
    addAndMakeVisible (_delayTimeSlider);
    _delayTimeSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    _delayTimeSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    _delayTimeSlider.setPopupDisplayEnabled (true, false, this);
    _delayTimeSlider.setTextValueSuffix (" - Delay Time");
    _delayTimeAttachment.reset (new SliderAttachment (_valueTreeState, "delayTime", _delayTimeSlider));
    
    setSize (700, 400);
}

BambooForestAudioProcessorEditor::~BambooForestAudioProcessorEditor()
{
}

//==============================================================================
void BambooForestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Bamboo Forest", getLocalBounds(), juce::Justification::centred, 1);
}

void BambooForestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    _wetSlider.setBounds (40, 30, 20, getHeight() - 60);
    _feedbackSlider.setBounds (60, 30, 20, getHeight() - 60);
    _delayTimeSlider.setBounds (80, 30, 20, getHeight() - 60);
}
