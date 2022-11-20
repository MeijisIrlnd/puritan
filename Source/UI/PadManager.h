/*
  ==============================================================================

    PadManager.h
    Created: 19 Nov 2022 6:28:36pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <UI/Pad.h>
namespace Puritan::UI
{
    class PadManager : public juce::Component, public Pad::Listener
    {
    public: 
        PadManager();
        ~PadManager() override;
        void paint(PURITAN_UNUSED juce::Graphics& g) override;
        void resized() override;

        void onPadClicked(PURITAN_UNUSED const Pad& clickedPad) override;
        void fileDroppedOnPad(Pad& pad, const juce::File& f) override;
        PURITAN_INLINE Pad* at(int row, int column)
        {
            int index = (row * 4) + column;
            return m_pads[index].get();
        }

    private: 
        // Pads should be a 4x4 grid 
        std::vector<std::unique_ptr<Pad> > m_pads;
    };
}