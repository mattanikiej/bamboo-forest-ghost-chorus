/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using Track = juce::Grid::TrackInfo;
using Fr = juce::Grid::Fr;
using Px = juce::Grid::Px;

//==============================================================================
BambooForestAudioProcessorEditor::BambooForestAudioProcessorEditor (BambooForestAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), _valueTreeState (vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    BambooForestLAF::setDefaultLookAndFeel(&_laf);

    // DELAY
    _wetLabel.setText ("Wet", juce::dontSendNotification);
    _wetLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible (_wetLabel);
    
    addAndMakeVisible (_wetSlider);
    _wetSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    _wetSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _wetSlider.setTextValueSuffix (" - Wet");
    _wetSlider.setPopupDisplayEnabled(true, false, this);
    _wetSlider.addListener(this);
    _wetAttachment.reset (new SliderAttachment (_valueTreeState, "wet", _wetSlider));
    
    _feedbackLabel.setText ("Feedback", juce::dontSendNotification);
    _feedbackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible (_feedbackLabel);
    
    addAndMakeVisible (_feedbackSlider);
    _feedbackSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    _feedbackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _feedbackSlider.setPopupDisplayEnabled (true, false, this);
    _feedbackSlider.setTextValueSuffix (" - Feedback");
    _feedbackSlider.addListener(this);
    _feedbackAttachment.reset (new SliderAttachment (_valueTreeState, "feedback", _feedbackSlider));
    
    _delayTimeLabel.setText ("Delay Time", juce::dontSendNotification);
    _delayTimeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible (_delayTimeLabel);
    
    addAndMakeVisible (_delayTimeSlider);
    _delayTimeSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    _delayTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _delayTimeSlider.setPopupDisplayEnabled (true, false, this);
    _delayTimeSlider.setTextValueSuffix (" - Delay Time");
    _delayTimeSlider.addListener(this);
    _delayTimeAttachment.reset (new SliderAttachment (_valueTreeState, "delayTime", _delayTimeSlider));

    // CHORUS
    _wetV1Label.setText("Wet Voice 1", juce::dontSendNotification);
    _wetV1Label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_wetV1Label);

    addAndMakeVisible(_wetV1Slider);
    _wetV1Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _wetV1Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _wetV1Slider.setPopupDisplayEnabled(true, false, this);
    _wetV1Slider.setTextValueSuffix(" - Wet Voice 1");
    _wetV1Slider.addListener(this);
    _wetV1Attachment.reset(new SliderAttachment(_valueTreeState, "wetV1", _wetV1Slider));

    _feedbackV1Label.setText("Feedback Voice 1", juce::dontSendNotification);
    _feedbackV1Label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_feedbackV1Label);

    addAndMakeVisible(_feedbackV1Slider);
    _feedbackV1Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _feedbackV1Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _feedbackV1Slider.setPopupDisplayEnabled(true, false, this);
    _feedbackV1Slider.setTextValueSuffix(" - Feedback Voice 1");
    _feedbackV1Slider.addListener(this);
    _feedbackV1Attachment.reset(new SliderAttachment(_valueTreeState, "feedbackV1", _feedbackV1Slider));

    _frequencyV1Label.setText("Rate Voice 1", juce::dontSendNotification);
    _frequencyV1Label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_frequencyV1Label);

    addAndMakeVisible(_frequencyV1Slider);
    _frequencyV1Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _frequencyV1Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _frequencyV1Slider.setPopupDisplayEnabled(true, false, this);
    _frequencyV1Slider.setTextValueSuffix(" - Rate Voice 1");
    _frequencyV1Slider.addListener(this);
    _frequencyV1Attachment.reset(new SliderAttachment(_valueTreeState, "frequencyV1", _frequencyV1Slider));

    _wetV2Label.setText("Wet Voice 2", juce::dontSendNotification);
    _wetV2Label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_wetV2Label);

    addAndMakeVisible(_wetV2Slider);
    _wetV2Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _wetV2Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _wetV2Slider.setPopupDisplayEnabled(true, false, this);
    _wetV2Slider.setTextValueSuffix(" - Wet Voice 2");
    _wetV2Slider.addListener(this);
    _wetV2Attachment.reset(new SliderAttachment(_valueTreeState, "wetV2", _wetV2Slider));

    _feedbackV2Label.setText("Feedback Voice 2", juce::dontSendNotification);
    _feedbackV2Label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_feedbackV2Label);

    addAndMakeVisible(_feedbackV2Slider);
    _feedbackV2Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _feedbackV2Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _feedbackV2Slider.setPopupDisplayEnabled(true, false, this);
    _feedbackV2Slider.setTextValueSuffix(" - Feedback Voice 2");
    _feedbackV2Slider.addListener(this);
    _feedbackV2Attachment.reset(new SliderAttachment(_valueTreeState, "feedbackV2", _feedbackV2Slider));

    _frequencyV2Label.setText("Rate Voice 2", juce::dontSendNotification);
    _frequencyV2Label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_frequencyV2Label);

    addAndMakeVisible(_frequencyV2Slider);
    _frequencyV2Slider.setSliderStyle(juce::Slider::LinearBarVertical);
    _frequencyV2Slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _frequencyV2Slider.setPopupDisplayEnabled(true, false, this);
    _frequencyV2Slider.setTextValueSuffix(" - Rate Voice 2");
    _frequencyV2Slider.addListener(this);
    _frequencyV2Attachment.reset(new SliderAttachment(_valueTreeState, "frequencyV2", _frequencyV2Slider));

    // GHOST
    _ghostLabel.setText("Ghost", juce::dontSendNotification);
    _ghostLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_ghostLabel);

    addAndMakeVisible(_ghostSlider);
    _ghostSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    _ghostSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _ghostSlider.setPopupDisplayEnabled(true, false, this);
    _ghostSlider.setTextValueSuffix(" - Ghost");
    _ghostSlider.addListener(this);
    _ghostAttachment.reset(new SliderAttachment(_valueTreeState, "ghost", _ghostSlider));

    _dryLabel.setText("Dry", juce::dontSendNotification);
    _dryLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(_dryLabel);

    addAndMakeVisible(_drySlider);
    _drySlider.setSliderStyle(juce::Slider::LinearBarVertical);
    _drySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 30);
    _drySlider.setPopupDisplayEnabled(true, false, this);
    _drySlider.setTextValueSuffix(" - Dry");
    _drySlider.addListener(this);
    _dryAttachment.reset(new SliderAttachment(_valueTreeState, "dry", _drySlider));
    
    setSize (1050, 600);
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


    juce::Grid grid;
    float sliderWidth = 30.0f;

    grid.templateRows = { Track(Fr(1)), Track(Fr(1)), Track(Fr(5))};
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), Track(Fr(1)), };

    grid.justifyContent = juce::Grid::JustifyContent::center;
    grid.justifyItems = juce::Grid::JustifyItems::center;

    grid.alignContent = juce::Grid::AlignContent::center;
    grid.alignItems = juce::Grid::AlignItems::center;

    grid.items = {
        // r1
        juce::GridItem(),
        juce::GridItem(),
        juce::GridItem(),
        juce::GridItem(),
        juce::GridItem(),
        juce::GridItem(),
        juce::GridItem(),
        juce::GridItem(),
        juce::GridItem(),
        juce::GridItem(),
        juce::GridItem(),

        // r2
        // DELAY
        juce::GridItem(_wetLabel),
        juce::GridItem(_feedbackLabel),
        juce::GridItem(_delayTimeLabel),

        // CHORUS
        juce::GridItem(_wetV1Label),
        juce::GridItem(_feedbackV1Label),
        juce::GridItem(_frequencyV1Label),

        juce::GridItem(_wetV2Label),
        juce::GridItem(_feedbackV2Label),
        juce::GridItem(_frequencyV2Label),

        // GHOST
        juce::GridItem(_ghostLabel),
        juce::GridItem(_dryLabel),

        // r3
        // DELAY
        juce::GridItem(_wetSlider).withWidth(sliderWidth),
        juce::GridItem(_feedbackSlider).withWidth(sliderWidth),
        juce::GridItem(_delayTimeSlider).withWidth(sliderWidth),

        // CHORUS
        juce::GridItem(_wetV1Slider).withWidth(sliderWidth),
        juce::GridItem(_feedbackV1Slider).withWidth(sliderWidth),
        juce::GridItem(_frequencyV1Slider).withWidth(sliderWidth),

        juce::GridItem(_wetV2Slider).withWidth(sliderWidth),
        juce::GridItem(_feedbackV2Slider).withWidth(sliderWidth),
        juce::GridItem(_frequencyV2Slider).withWidth(sliderWidth),

        // GHOST
        juce::GridItem(_ghostSlider).withWidth(sliderWidth),
        juce::GridItem(_drySlider).withWidth(sliderWidth)
    };

    grid.performLayout(getLocalBounds());
}

void BambooForestAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    audioProcessor.setWet(_wetSlider.getValue(), _wetV1Slider.getValue(), _wetV2Slider.getValue());
    audioProcessor.setFeedback(_feedbackSlider.getValue(), _feedbackV1Slider.getValue(), _feedbackV2Slider.getValue());
    audioProcessor.setDelayInSamples(_delayTimeSlider.getValue());
}
