#include "common_data_structures.hpp"

void DetectionResult::clear()
{
    this->locations.clear();
    this->histograms.clear();
}
