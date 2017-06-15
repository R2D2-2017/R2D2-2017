/**
 * \file      enum.hh
 * \brief     Enum class Note can be used to get a specified note frequency.
 * \author    Robbie Valkenburg
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#ifndef GAS_ENUM_HH
#define GAS_ENUM_HH

/**
 * Enum class that contains specified notes
 */
enum class Note {
    highNote = 880,
    lowNote = 698,
};

enum class ConfigStorage {
	warningThreshold = 105,
	dangerThreshold = 100,
	mq5BaseValue = 100,
	measureFrequency = 1000,
};

#endif //GAS_ENUM_HH