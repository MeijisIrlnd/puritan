/*
  ==============================================================================

    SmokeShader.h
    Created: 4 Dec 2022 4:52:42pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <UI/Shaders/Shader.h>
namespace Puritan::UI::Shaders
{
    template<int NPixels>
    class SmokeShader : public Shader
    {
    public: 
        SmokeShader<NPixels>()
        {
            setInterceptsMouseClicks(false, false);
            m_backgroundTexture = juce::Image(juce::Image::PixelFormat::ARGB, NPixels, NPixels, true);
        }

        void paint(juce::Graphics& g) override
        {
            auto backBuffer = renderSmoke(m_backgroundTexture);
            g.drawImage(backBuffer.rescaled(getWidth(), getHeight(), juce::Graphics::ResamplingQuality::highResamplingQuality), getLocalBounds().toFloat());
            m_backgroundTexture = backBuffer;

        }


    private: 
        juce::Image renderSmoke(juce::Image& buffer)
        {
            buffer.clear(buffer.getBounds());
            juce::Image backBuffer = buffer.createCopy();
            // Percentage chance to render new smoke, maybe 10%? 
            bool newSmokeSource = juce::jmap<int>(std::rand(), 0, INT_MAX, 0, 100) > 10;
            if (newSmokeSource) {
                // set a particular pixel in the diffusion matrix to full? 
            }
            // Dissapate regardless.. 
            for (auto col = 0; col < NPixels; col++) {
                for (auto row = 0; row < NPixels; row++) {
                    bool draw = (std::rand() % 100) < 10;
                    if (draw) {
                        backBuffer.setPixelAt(col, row, juce::Colour(0xFF7F7F7F));
                    }
                }
            }
            return backBuffer;
        }

        juce::Image m_backgroundTexture;
    };
}