#include <common/globalEnum.h>

#include "detector.h"

using namespace ExampleStrat;

Detector::~Detector() = default;

EResultValue<Signal> Detector::detect() const
{
    LOG_ENTRY;

    Signal signal;
    signal.direction = Direction::Buy;
    signal.reason = "Nani";
    return EResultValue<Signal>::ok(signal);
}