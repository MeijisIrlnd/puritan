/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PuritanAudioProcessor* PuritanAudioProcessor::m_instance{ nullptr };
std::mutex PuritanAudioProcessor::m_mutex;


PuritanAudioProcessor::PuritanAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#else 
    :
#endif
m_tree(*this, nullptr, { "Params" }, createParameterLayout())
{
    m_formatManager.registerBasicFormats();
    for (auto i = 0; i < 16; i++) {
        m_padPlayers.emplace_back(new Puritan::Audio::PadPlayer(i));
    }
    registerParamListeners();
}

PuritanAudioProcessor::~PuritanAudioProcessor()
{

}

PuritanAudioProcessor* PuritanAudioProcessor::getInstance()
{
    std::scoped_lock<std::mutex> sl(m_mutex);
    if (m_instance == nullptr) {
        m_instance = new PuritanAudioProcessor();
    }
    return m_instance;
}


//==============================================================================
const juce::String PuritanAudioProcessor::getName() const
{
    return JucePlugin_Name;
    
}

bool PuritanAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PuritanAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PuritanAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PuritanAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PuritanAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PuritanAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PuritanAudioProcessor::setCurrentProgram (PURITAN_UNUSED int index)
{
}

const juce::String PuritanAudioProcessor::getProgramName (PURITAN_UNUSED int index)
{
    return {};
}

void PuritanAudioProcessor::changeProgramName (PURITAN_UNUSED int index, PURITAN_UNUSED const juce::String& newName)
{
}

//==============================================================================
void PuritanAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    m_sampleRate = sampleRate;
    m_previewPlayer.prepareToPlay(samplesPerBlock, sampleRate);
    for (auto& item : m_padPlayers)
    {
        item->prepareToPlay(samplesPerBlock, sampleRate);
    }
}


void PuritanAudioProcessor::releaseResources()
{
    m_previewPlayer.releaseResources();
    for (auto& item : m_padPlayers)
    {
        item->releaseResources();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PuritanAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void PuritanAudioProcessor::processBlock (PURITAN_UNUSED juce::AudioBuffer<float>& buffer, PURITAN_UNUSED juce::MidiBuffer& midiMessages)
{
    juce::AudioSourceChannelInfo bufferToFill(buffer);
    bufferToFill.clearActiveBufferRegion();
    m_previewPlayer.getNextAudioBlock(bufferToFill);
    for (auto i = 0; i < m_padPlayers.size(); i++)
    {
        m_padPlayers[i]->getNextAudioBlock(bufferToFill);
    }

}

//==============================================================================
bool PuritanAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PuritanAudioProcessor::createEditor()
{
    return new PuritanAudioProcessorEditor (*this);
}

//==============================================================================
void PuritanAudioProcessor::getStateInformation (PURITAN_UNUSED juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PuritanAudioProcessor::loadToPad(int padIndex, const juce::File& toLoad)
{
    m_padPlayers[padIndex]->setSample(toLoad);
}

void PuritanAudioProcessor::triggerPad(int padIndex)
{
    m_padPlayers[padIndex]->play();
}

void PuritanAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID.contains("Pad"))
    {
        int padNum = std::stoi(parameterID.substring(juce::String("Pad").length(), parameterID.indexOf("_")).toStdString());
        auto paramName = parameterID.substring(parameterID.indexOf("_") + 1);
        if (paramName == "StartTime") { m_padPlayers[padNum]->setStart(static_cast<double>(newValue)); }
        else if (paramName == "EndTime") { m_padPlayers[padNum]->setEnd(static_cast<double>(newValue)); }
        else if (paramName == "Pan") { m_padPlayers[padNum]->setPan(newValue); }
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout PuritanAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    for (auto i = 0; i < 16; i++)
    {
        layout.add(std::make_unique<juce::AudioParameterFloat>(fmt::format("Pad{}_StartTime", i), fmt::format("Pad{}_StartTime",i), juce::NormalisableRange<float>(0, 1, 0.001f), 0.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(fmt::format("Pad{}_EndTime", i), fmt::format("Pad{}_EndTime", i), juce::NormalisableRange<float>(0, 1, 0.001f), 1.0f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(fmt::format("Pad{}_Pan", i), fmt::format("Pad{}_Pan", i), juce::NormalisableRange<float>(0, 1, 0.01f), 0.5f));
    }
    return layout;
}

void PuritanAudioProcessor::registerParamListeners()
{
    for (auto i = 0; i < 16; i++)
    {
        m_tree.addParameterListener(fmt::format("Pad{}_StartTime", i), this);
        m_tree.addParameterListener(fmt::format("Pad{}_EndTime", i), this);
        m_tree.addParameterListener(fmt::format("Pad{}_Pan", i), this);
    }
}

void PuritanAudioProcessor::setStateInformation (PURITAN_UNUSED const void* data, PURITAN_UNUSED int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return PuritanAudioProcessor::getInstance();
}
