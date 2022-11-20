/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <mutex>
#include <JuceHeader.h>
#include <Audio/FilePreviewPlayer.h>
#include <Audio/PadPlayer.h>

//==============================================================================
/**
*/
class PuritanAudioProcessor  : public juce::AudioProcessor
{
protected:
    //==============================================================================
    PuritanAudioProcessor();
    ~PuritanAudioProcessor() override;
public: 
    static PuritanAudioProcessor* getInstance();
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void triggerPad(int padIndex);
    PURITAN_INLINE juce::AudioFormatManager* getFormatManager() { return &m_formatManager; }
    PURITAN_INLINE Puritan::Audio::FilePreviewPlayer* getPreviewPlayer() { return &m_previewPlayer; }
private:
    static std::mutex m_mutex;
    static PuritanAudioProcessor* m_instance;
    juce::AudioFormatManager m_formatManager;
    //std::vector<std::unique_ptr<Puritan::PadInfo> > m_pads;
    Puritan::Audio::FilePreviewPlayer m_previewPlayer;
    std::vector<std::unique_ptr<Puritan::Audio::PadPlayer> > m_padPlayers;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PuritanAudioProcessor)
};
