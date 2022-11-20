/*
  ==============================================================================

    LF.h
    Created: 19 Nov 2022 5:58:28pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Utils/Macros.h>
namespace Puritan::UI
{
    class LF : public juce::LookAndFeel_V4
    {
    public:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4369)
#endif
        enum class PALETTE_COLOUR
        {
            PURPLE_A = 0xFF5E315A,
            PURPLE_B = 0xFF8B3F5D,
            BURNT_SIENNA = 0xFFB96155,
            ORANGE_A = 0xFFF3A65E,
            YELLOW = 0xFFFFE577,
            LIME_A = 0xFFCFFE70,
            LIME_B = 0xFF8FDE5E,
            TURQUOISE_A = 0xFF3CA270,
            TURQUOISE_B = 0xFF3D6F70,
            GREY_BLUE = 0xFF323D4F,
            PURPLE_C = 0xFF322946,
            PURPLE_D = 0xFF473C78,
            LILAC_A = 0xFF4A5BAB,
            BLUE_A = 0xFF4DA6FF,
            BRIGHT_BLUE = 0xFF66FFE3,
            CREAM = 0xFFFFFFEB,
            GREY_A = 0xFFC3C2D0,
            GREY_B = 0xFF7F7E8E,
            GREY_C = 0xFF616070,
            GREY_D = 0xFF43434F,
            BLACK = 0xFF282735,
            PURPLE_E = 0xFF3E2346,
            WINE_A = 0xFF572A4B,
            WINE_B = 0xFF964252,
            ORANGE_B = 0xFFE36856,
            ORANGE_C = 0xFFFFB470,
            ORANGE_D = 0xFFFE9166,
            ORANGE_E = 0xFFEA564A,
            PINK_A = 0xFFAF305B,
            PURPLE_F = 0xFF74275D,
            PURPLE_G = 0xFF422544,
            PURPLE_H = 0xFF59265E,
            PURPLE_I = 0xFF80366B,
            PINK_B = 0xFFBE4882,
            PINK_C = 0xFFFE6B97,
            SALMON = 0xFFFFB5B6
        };
#ifdef _MSC_VER
#pragma warning(pop)
#endif
        LF();
        ~LF() override;
        void drawFileBrowserRow(juce::Graphics& g, int width, int height,
            const juce::File& file, const juce::String& filename, juce::Image* icon,
            const juce::String& fileSizeDescription,
            const juce::String& fileTimeDescription,
            bool isDirectory, bool isItemSelected,
            int itemIndex, juce::DirectoryContentsDisplayComponent& dcc) override;

        void layoutFileBrowserComponent(juce::FileBrowserComponent& browserComp,
            juce::DirectoryContentsDisplayComponent* fileListComponent,
            juce::FilePreviewComponent* previewComp,
            juce::ComboBox* currentPathBox,
            juce::TextEditor* filenameBox,
            juce::Button* goUpButton) override;

        PURITAN_INLINE juce::Font getLabelFont(juce::Label& l) override {
            return m_font.withHeight(static_cast<float>(l.getHeight() / 1.5));
        }
        PURITAN_INLINE juce::Font getComboBoxFont(juce::ComboBox& c) override {
            return m_font.withHeight(static_cast<float>(c.getHeight()));
        }

        PURITAN_INLINE juce::Font getPopupMenuFont() override {
            return m_font;
        }

        PURITAN_INLINE static juce::Colour getPaletteColour(PALETTE_COLOUR p)
        {
            return juce::Colour(static_cast<int>(p));
        }

    private: 
        static juce::Font m_font;
        static std::unordered_map<PALETTE_COLOUR, juce::Colour> m_palette;
        juce::Colour m_primaryBackgroundColour, m_primaryHighlightColour, m_primaryTextColour;
    };
}