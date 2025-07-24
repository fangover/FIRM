#include <basicstdlib.h>
#include <eresultvalue.h>
#include "core/include/globalEnum.h"

#include "../include/detector.h"

using namespace ScalpingM1;

Detector::~Detector() = default;

EResultValue<Signal> Detector::detect() const
{

    LOG_ENTRY;

    Signal signal;
    signal.direction = Direction::Buy;
    signal.reason = "Nani";
    return EResultValue<Signal>::ok(signal);
}