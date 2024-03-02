/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BambooForestAudioProcessor::BambooForestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),

        _parameters (*this, nullptr, juce::Identifier ("BambooForest"),
                      {
                        // DELAY PARAMS
                        std::make_unique<juce::AudioParameterFloat> ("wet",             // parameterID
                                                                     "Wet",             // parameter name
                                                                     0.0f,              // minimum value
                                                                     10.0f,             // maximum value
                                                                     9.0f),             // default value
            
                        std::make_unique<juce::AudioParameterFloat> ("feedback",        // parameterID
                                                                     "Feedback",        // parameter name
                                                                     0.0f,              // minimum value
                                                                     10.0f,             // maximum value
                                                                     7.5f),             // default value
            
                        std::make_unique<juce::AudioParameterFloat> ("delayTime",       // parameterID
                                                                     "Delay Time",      // parameter name
                                                                     0.0f,              // minimum value
                                                                     10.0f,             // maximum value
                                                                     5.0f),             // default value
                        
                        // CHORUS PARAMS
                        // Voice 1
                        std::make_unique<juce::AudioParameterFloat>("wetV1",                   // parameterID
                                                                     "Wet Voice 1",            // parameter name
                                                                     0.0f,                     // minimum value
                                                                     10.0f,                    // maximum value
                                                                     9.0f),                    // default value

                        std::make_unique<juce::AudioParameterFloat>("feedbackV1",              // parameterID
                                                                     "Feedback Voice 1",       // parameter name
                                                                     0.0f,                     // minimum value
                                                                     10.0f,                    // maximum value
                                                                     7.5f),                    // default value

                        std::make_unique<juce::AudioParameterFloat>("frequencyV1",             // parameterID
                                                                     "Frequency Voice 1",      // parameter name
                                                                     0.1f,                     // minimum value
                                                                     10.0f,                    // maximum value
                                                                     5.0f),                    // default value
                        
                        // Voice 2
                        std::make_unique<juce::AudioParameterFloat>("wetV2",                   // parameterID
                                                                     "Wet Voice 2",            // parameter name
                                                                     0.0f,                     // minimum value
                                                                     10.0f,                    // maximum value
                                                                     9.0f),                    // default value

                        std::make_unique<juce::AudioParameterFloat>("feedbackV2",              // parameterID
                                                                     "Feedback Voice 2",       // parameter name
                                                                     0.1f,                     // minimum value
                                                                     10.0f,                    // maximum value
                                                                     7.5f),                    // default value

                        std::make_unique<juce::AudioParameterFloat>("frequencyV2",             // parameterID
                                                                     "Frequency Voice 2",      // parameter name
                                                                     0.0f,                     // minimum value
                                                                     10.0f,                    // maximum value
                                                                     5.0f),                    // default value
                      })
#endif
        
{

    _wetParameter = _parameters.getRawParameterValue("wet");
    _feedbackParameter = _parameters.getRawParameterValue("feedback");
    _delayTimeParameter = _parameters.getRawParameterValue("delayTime");

    _wetV1Parameter = _parameters.getRawParameterValue("wetV1");
    _feedbackV1Parameter = _parameters.getRawParameterValue("feedbackV1");
    _fqV1Parameter = _parameters.getRawParameterValue("frequencyV1");

    _wetV2Parameter = _parameters.getRawParameterValue("wetV2");
    _feedbackV2Parameter = _parameters.getRawParameterValue("feedbackV2");
    _fqV2Parameter = _parameters.getRawParameterValue("frequencyV2");

    setWet(*_wetParameter, *_wetV1Parameter, *_wetV2Parameter);
    setFeedback(*_feedbackParameter, *_feedbackV1Parameter, *_feedbackV2Parameter);
}

BambooForestAudioProcessor::~BambooForestAudioProcessor()
{
}

//==============================================================================
const juce::String BambooForestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BambooForestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BambooForestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BambooForestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BambooForestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BambooForestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BambooForestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BambooForestAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BambooForestAudioProcessor::getProgramName (int index)
{
    return {};
}

void BambooForestAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BambooForestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    _sampleRate = sampleRate;

    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();

    // DELAY
    _delayLine.reset();
    _delayLine.prepare(spec);
    _delayLine.setMaximumDelayInSamples(sampleRate * 2);
    setDelayInSamples(*_delayTimeParameter);

    auto filterCoefs = juce::dsp::IIR::Coefficients<float>::makeFirstOrderHighPass(sampleRate, 500);

    for (auto& f : _filters)
    {
        f.prepare(spec);
        f.coefficients = filterCoefs;
    }

    // CHORUS
    auto pf1 = juce::dsp::IIR::Coefficients<float>::makeAllPass(sampleRate, *_fqV1Parameter);
    auto pf2 = juce::dsp::IIR::Coefficients<float>::makeAllPass(sampleRate, *_fqV2Parameter);

    // voice 1 15ms delay
    _delayLineV1.reset();
    _delayLineV1.prepare(spec);
    _delayLineV1.setMaximumDelayInSamples(sampleRate);
    float delayV1 = sampleRate * 0.015;
    _delayLineV1.setDelay(delayV1);
    for (auto& f : _filtersV1)
    {
        f.prepare(spec);
        f.coefficients = pf1;
    }

    // voice 2 35ms delay
    _delayLineV2.reset();
    _delayLineV2.prepare(spec);
    _delayLineV2.setMaximumDelayInSamples(sampleRate);
    float delayV2 = sampleRate * 0.035;
    _delayLineV2.setDelay(delayV2);
    for (auto& f : _filtersV2)
    {
        f.prepare(spec);
        f.coefficients = pf1;
    }
}

void BambooForestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BambooForestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BambooForestAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        auto& filter = _filters[channel];
        auto& filterV1 = _filtersV1[channel];
        auto& filterV2 = _filtersV2[channel];

        for (size_t sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            auto inputSample = channelData[sample];

            // CHORUS
            auto chorusDelayedSampleV1 = filterV1.processSample(_delayLineV1.popSample(channel));
            auto dlineInputSampleV1 = std::tanh(inputSample + _feedbackV1 * chorusDelayedSampleV1);
            _delayLineV1.pushSample(channel, dlineInputSampleV1);

            auto chorusDelayedSampleV2 = filterV2.processSample(_delayLineV2.popSample(channel));
            auto dlineInputSampleV2 = std::tanh(inputSample + _feedbackV2 * chorusDelayedSampleV2);
            _delayLineV2.pushSample(channel, dlineInputSampleV2);

            auto chorusSample = _wetV1 * chorusDelayedSampleV1 + _wetV2 * chorusDelayedSampleV2;

            // DELAY
            auto delayedSample = filter.processSample(_delayLine.popSample(channel));                                               
            auto dlineInputSample = std::tanh(chorusSample + _feedback * delayedSample);
            _delayLine.pushSample(channel, dlineInputSample);
            
            delayedSample *= _wet;

            auto outputSample = inputSample + delayedSample;

            channelData[sample] = outputSample;   
        }
    }

}

//==============================================================================
bool BambooForestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BambooForestAudioProcessor::createEditor()
{
    return new BambooForestAudioProcessorEditor (*this, _parameters);
}

//==============================================================================
void BambooForestAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = _parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void BambooForestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (_parameters.state.getType()))
            _parameters.replaceState (juce::ValueTree::fromXml (*xmlState));

    setWet(*_wetParameter, *_wetV1Parameter, *_wetV2Parameter);
    setFeedback(*_feedbackParameter, *_feedbackV1Parameter, *_feedbackV2Parameter);
    setDelayInSamples(*_delayTimeParameter);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BambooForestAudioProcessor();
}

void BambooForestAudioProcessor::setWet(float newWet, float newWetV1, float newWetV2)
{
    _wet = juce::jmap(newWet, 0.0f, 10.0f, 0.0f, 1.0f);
    _wetV1 = juce::jmap(newWetV1, 0.0f, 10.0f, 0.0f, 1.0f);
    _wetV2 = juce::jmap(newWetV2, 0.0f, 10.0f, 0.0f, 1.0f);
}

void BambooForestAudioProcessor::setFeedback(float newFeedback, float newFeedbackV1, float newFeedbackV2)
{
    _feedback = juce::jmap(newFeedback, 0.0f, 10.0f, 0.0f, 1.0f);
    _feedbackV1 = juce::jmap(newFeedbackV1, 0.0f, 10.0f, 0.0f, 1.0f);
    _feedbackV2 = juce::jmap(newFeedbackV2, 0.0f, 10.0f, 0.0f, 1.0f);
}

void BambooForestAudioProcessor::setDelayInSamples(float newDelay)
{   
    float maxDelay = _delayLine.getMaximumDelayInSamples();
    _delayTime = juce::jmap(newDelay, 0.0f, 10.0f, 0.0f, maxDelay);
    _delayLine.setDelay(_delayTime);
}

void BambooForestAudioProcessor::setFrequency(float fqV1, float fqV2)
{
    auto pf1 = juce::dsp::IIR::Coefficients<float>::makeAllPass(_sampleRate, fqV1);
    auto pf2 = juce::dsp::IIR::Coefficients<float>::makeAllPass(_sampleRate, fqV2);

    for (auto& f : _filtersV1)
    {
        f.coefficients = pf1;
    }

    for (auto& f : _filtersV2)
    {
        f.coefficients = pf1;
    }
}
