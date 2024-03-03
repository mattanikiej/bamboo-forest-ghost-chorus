/*
  ==============================================================================

    BambooForestLAF.cpp
    Created: 3 Mar 2024 9:58:09am
    Author:  matta

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BambooForestLAF.h"

//==============================================================================
BambooForestLAF::BambooForestLAF()
{
    // sliders
    setColour(juce::Slider::ColourIds::trackColourId, _green);

    // default window settings
    juce::Colour c = juce::Colour(255, 255, 255);
    setColour(juce::ResizableWindow::backgroundColourId, c);

    // labels
    setColour(juce::Label::textColourId, _white);

    setDefaultSansSerifTypeface(_assassinNinja.getTypefacePtr());

}

