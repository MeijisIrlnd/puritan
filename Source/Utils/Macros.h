/*
  ==============================================================================

    Macros.h
    Created: 19 Nov 2022 5:55:42pm
    Author:  Syl

  ==============================================================================
*/

#pragma once

#define PURITAN_UNUSED [[maybe_unused]]

#ifdef _MSC_VER 
#define PURITAN_INLINE __forceinline
#else 
#define PURITAN_INLINE __attribute__((always_inline))
#endif