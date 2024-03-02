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
    
    // DELAY
    _wetLabel.setText ("Wet", juce::dontSendNotification);
    addAndMakeVisible (_wetLabel);
    
    addAndMakeVisible (_wetSlider);
    _wetSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    _wetSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    _wetSlider.setPopupDisplayEnabled (true, false, this);
    _wetSlider.setTextValueSuffix (" - Wet");
    _wetSlider.addListener(this);
    _wetAttachment.reset (new SliderAttachment (_valueTreeState, "wet", _wetSlider));
    
    _feedbackLabel.setText ("Feedback", juce::dontSendNotification);
    addAndMakeVisible (_feedbackLabel);
    
    addAndMakeVisible (_feedbackSlider);
    _feedbackSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    _feedbackSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    _feedbackSlider.setPopupDisplayEnabled (true, false, this);
    _feedbackSlider.setTextValueSuffix (" - Feedback");
    _feedbackSlider.addListener(this);
    _feedbackAttachment.reset (new SliderAttachment (_valueTreeState, "feedback", _feedbackSlider));
    
    _delayTimeLabel.setText ("Delay Time", juce::dontSendNotification);
    addAndMakeVisible (_delayTimeLabel);
    
    addAndMakeVisible (_delayTimeSlider);
    _delayTimeSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    _delayTimeSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    _delayTimeSlider.setPopupDisplayEnabled (true, false, this);
    _delayTimeSlider.setTextValueSuffix (" - Delay Time");
    _delayTimeSlider.addListener(this);
    _delayTimeAttachment.reset (new SliderAttachment (_valueTreeState, "delayTime", _delayTimeSlider));

    // CHORUS
    _wetV1Label.setText("Wet Voice 1", juce::dontSendNotification);
    addAndMakeVisible(_wetV1Label);

    addAndMakeVisible(_wetV1Slider);
    _wetV1Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _wetV1Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    _wetV1Slider.setPopupDisplayEnabled(true, false, this);
    _wetV1Slider.setTextValueSuffix(" - Wet Voice 1");
    _wetV1Slider.addListener(this);
    _wetV1Attachment.reset(new SliderAttachment(_valueTreeState, "wetV1", _wetV1Slider));

    _feedbackV1Label.setText("Feedback Voice 1", juce::dontSendNotification);
    addAndMakeVisible(_feedbackV1Label);

    addAndMakeVisible(_feedbackV1Slider);
    _feedbackV1Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _feedbackV1Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    _feedbackV1Slider.setPopupDisplayEnabled(true, false, this);
    _feedbackV1Slider.setTextValueSuffix(" - Feedback Voice 1");
    _feedbackV1Slider.addListener(this);
    _feedbackV1Attachment.reset(new SliderAttachment(_valueTreeState, "feedbackV1", _feedbackV1Slider));

    _frequencyV1Label.setText("Rate Voice 1", juce::dontSendNotification);
    addAndMakeVisible(_frequencyV1Label);

    addAndMakeVisible(_frequencyV1Slider);
    _frequencyV1Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _frequencyV1Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    _frequencyV1Slider.setPopupDisplayEnabled(true, false, this);
    _frequencyV1Slider.setTextValueSuffix(" - Rate Voice 1");
    _frequencyV1Slider.addListener(this);
    _frequencyV1Attachment.reset(new SliderAttachment(_valueTreeState, "frequencyV1", _frequencyV1Slider));

    _frequencyV1Label.setText("Wet Voice 2", juce::dontSendNotification);
    addAndMakeVisible(_frequencyV1Label);

    addAndMakeVisible(_wetV2Slider);
    _wetV2Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _wetV2Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    _wetV2Slider.setPopupDisplayEnabled(true, false, this);
    _wetV2Slider.setTextValueSuffix(" - Wet Voice 2");
    _wetV2Slider.addListener(this);
    _wetV2Attachment.reset(new SliderAttachment(_valueTreeState, "wetV2", _wetV2Slider));

    _feedbackV2Label.setText("Feedback Voice 2", juce::dontSendNotification);
    addAndMakeVisible(_feedbackV2Label);

    addAndMakeVisible(_feedbackV2Slider);
    _feedbackV2Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _feedbackV2Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    _feedbackV2Slider.setPopupDisplayEnabled(true, false, this);
    _feedbackV2Slider.setTextValueSuffix(" - Feedback Voice 2");
    _feedbackV2Slider.addListener(this);
    _feedbackV2Attachment.reset(new SliderAttachment(_valueTreeState, "feedbackV2", _feedbackV2Slider));

    _frequencyV2Label.setText("Rate Voice 2", juce::dontSendNotification);
    addAndMakeVisible(_frequencyV2Label);

    addAndMakeVisible(_frequencyV2Slider);
    _frequencyV2Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _frequencyV2Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    _frequencyV2Slider.setPopupDisplayEnabled(true, false, this);
    _frequencyV2Slider.setTextValueSuffix(" - Rate Voice 2");
    _frequencyV2Slider.addListener(this);
    _frequencyV2Attachment.reset(new SliderAttachment(_valueTreeState, "frequencyV2", _frequencyV2Slider));
    
    setSize (700, 400);
}

BambooForestAudioProcessorEditor::~BambooForestAudioProcessorEditor()
{
}

//==============================================================================
void BambooForestAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(_background, 0, 0);
}

void BambooForestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    _wetSlider.setBounds (40, 30, 20, getHeight() - 60);
    _feedbackSlider.setBounds (60, 30, 20, getHeight() - 60);
    _delayTimeSlider.setBounds (80, 30, 20, getHeight() - 60);

    _wetV1Slider.setBounds(120, 30, 20, getHeight() - 60);
    _feedbackV1Slider.setBounds(140, 30, 20, getHeight() - 60);
    _frequencyV1Slider.setBounds(160, 30, 20, getHeight() - 60);

    _wetV2Slider.setBounds(200, 60, 20, getHeight() - 70);
    _feedbackV2Slider.setBounds(220, 60, 20, getHeight() - 70);
    _frequencyV2Slider.setBounds(240, 60, 20, getHeight() - 70);
}

void BambooForestAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    audioProcessor.setWet(_wetSlider.getValue(), _wetV1Slider.getValue(), _wetV2Slider.getValue());
    audioProcessor.setFeedback(_feedbackSlider.getValue(), _feedbackV1Slider.getValue(), _feedbackV2Slider.getValue());
    audioProcessor.setDelayInSamples(_delayTimeSlider.getValue());
}
