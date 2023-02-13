#include "PluginProcessor.h"

DelayPlugin::DelayPlugin()
    : delayLine(44100.0f) // initialize the delay line with a sample rate of 44100 Hz
{
    // create the delay time parameter
    addParameter(delayTimeParam = new juce::AudioParameterFloat("delayTime", "Delay Time", 0.0f, 1.0f, 0.5f));

    // create the feedback parameter
    addParameter(feedbackParam = new juce::AudioParameterFloat("feedback", "Feedback", 0.0f, 1.0f, 0.5f));

    // create the wet level parameter
    addParameter(wetLevelParam = new juce::AudioParameterFloat("wetLevel", "Wet Level", 0.0f, 1.0f, 0.5f));
}

DelayPlugin::~DelayPlugin()
{
}

void DelayPlugin::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // set the sample rate of the delay line
    delayLine.prepare({ sampleRate, (juce::uint32)samplesPerBlock });
}

void DelayPlugin::releaseResources()
{
}

void DelayPlugin::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();

    // get the current value of the delay time parameter
    const float delayTime = delayTimeParam->get();

    // get the current value of the feedback parameter
    const float feedback = feedbackParam->get();

    // get the current value of the wet level parameter
    const float wetLevel = wetLevelParam->get();

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int i = 0; i < numSamples; ++i)
        {
            // get the delayed sample
            const float delayedSample = delayLine.popSample(channel);

            // compute the output sample as a combination of the original and delayed samples
            const float outputSample = channelData[i] + wetLevel * delayedSample;

            // push the output sample into the delay line
            delayLine.pushSample(channel, channelData[i] + feedback * delayedSample);

            // write the output sample back to the buffer
            channelData[i] = outputSample;
        }
    }
}

juce::AudioProcessorEditor* DelayPlugin::createEditor()
{
    // TODO: create a custom editor for the delay plugin
    return nullptr;
}

bool DelayPlugin::hasEditor() const
{
    return true;
}

const juce::String DelayPlugin::getName() const
{
    return "Delay Plugin";
}

int DelayPlugin::getNumPrograms()
{
    return 1;
}

int DelayPlugin::getCurrentProgram()
{
    return 0;
}

void DelayPlugin::setCurrentProgram(int index)
{
}

const juce::String DelayPlugin::getProgramName(int index)
{
    return {};
}

void DelayPlugin::changeProgramName(int index, const juce::String& newName)
{
}

void DelayPlugin::getStateInformation(juce::MemoryBlock& destData)
{
    // TODO: implement state saving for the delay plugin
}

void DelayPlugin::setStateInformation(const void* data, int sizeInBytes)
{
    // TODO: implement state loading for the delay plugin
}
