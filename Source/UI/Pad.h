/*
  ==============================================================================

    Pad.h
    Created: 19 Nov 2022 5:52:59pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <UI/Behaviours/AnimatedComponent.h>
#include <Utils/Macros.h>
#include <Utils/PuritanMath.h>
#include <Types/PadInfo.h>
#include <JuceHeader.h>
namespace Puritan::UI
{
    class Pad : public Behaviours::AnimatedComponent, public AnimatedGIF::Listener, public juce::DragAndDropTarget
    {
    public: 
        struct Listener
        {
            virtual ~Listener() { }
            virtual void onPadClicked(const Pad& clickedPad) = 0;
            virtual void fileDroppedOnPad(const Pad& pad, const juce::File& f) = 0;
        };

        Pad(const int midiNote, const int index);
        ~Pad() override;

        PURITAN_INLINE void addListener(Listener* newListener) {
            m_listener = newListener;
        }
        void gifPlaybackFinished() override;
        bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) override;
        void itemDropped(const SourceDetails& dragSourceDetails) override;

        void mouseUp(PURITAN_UNUSED const juce::MouseEvent& ev) override;
        void paint(juce::Graphics& g) override;
        void resized() override;

        void set(const std::shared_ptr<PadInfo> padInfo);
        PURITAN_INLINE std::shared_ptr<PadInfo> getInfo() { return m_associatedPadInfo; }
        PURITAN_INLINE const int getIndex() const { return m_index; }
        PURITAN_INLINE const int getMidiNote() const { return m_midiNote; }
    private: 
        Listener* m_listener{ nullptr };
        std::shared_ptr<PadInfo> m_associatedPadInfo;
        const int m_index;
        const int m_midiNote;
        juce::Label m_nameDisplay;
        juce::Image m_padSprite;
        AnimatedGIF m_gif;
    };
}
