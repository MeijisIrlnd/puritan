/*
  ==============================================================================

    NoiseShader.h
    Created: 4 Dec 2022 5:39:30pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <UI/Shaders/Shader.h>
#include <UI/LF.h>
namespace Puritan::UI::Shaders
{
    template<int W, int H>
    class NoiseShader : public Shader
    {
    public:
        NoiseShader<W, H>(const int probablitity, const double alpha) : Shader(W, H), m_probability(probablitity), m_alpha(alpha) {
            setInterceptsMouseClicks(false, false);
        }
        ~NoiseShader() override { }

        void paint(juce::Graphics& g) override
        {
            m_backBuffer = m_frontBuffer.createCopy();
            m_backBuffer.clear(getLocalBounds());
            for (auto col = 0; col < W; col++)
            {
                for (auto row = 0; row < H; row++) {
                    bool draw = (std::rand() % 100) < m_probability;
                    if (draw) {
                        int colSelection = std::rand() % 3;
                        juce::Colour colour = colSelection == 0 ? LF::getPaletteColour(LF::PALETTE_COLOUR::ORANGE_A) :
                            (colSelection == 1 ? LF::getPaletteColour(LF::PALETTE_COLOUR::TURQUOISE_A) : LF::getPaletteColour(LF::PALETTE_COLOUR::BLUE_A));
                        colour = colour.withAlpha(static_cast<float>(m_alpha));
                        m_backBuffer.setPixelAt(col, row, colour);
                    }
                }
            }
            g.drawImage(m_backBuffer.rescaled(getWidth(), getHeight(), juce::Graphics::ResamplingQuality::lowResamplingQuality), getLocalBounds().toFloat());
            m_frontBuffer = m_backBuffer;
        }

    private: 
        const int m_probability;
        const double m_alpha;
    };
}