#pragma once

#include <map>
#include <stdint.h>

uint32_t roll_sample(const uint32_t dice_in_roll, const uint32_t die_faces,
                     const uint32_t sample_size);
uint32_t computation(const uint32_t faces);
