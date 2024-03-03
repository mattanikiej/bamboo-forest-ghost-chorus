/*
  ==============================================================================

    BambooForestLAF.h
    Created: 3 Mar 2024 9:58:09am
    Author:  matta

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BambooForestLAF  : public juce::LookAndFeel_V4
{
public:
    BambooForestLAF();

private:
    // colors
    juce::Colour _green = juce::Colour(114, 186, 63);
    juce::Colour _white = juce::Colour(255, 255, 255);

    // typefaces
    juce::Font _assassinNinja = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::AssassinNinja7BYyR_ttf, BinaryData::AssassinNinja7BYyR_ttfSize));

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BambooForestLAF)
};
