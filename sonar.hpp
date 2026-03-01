#pragma once

#include "config.hpp"
#include <NewPing.h>

void initSonar();

float updateSonar(NewPing *pSonar);