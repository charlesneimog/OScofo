#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <m_pd.h>

// FFT
#include <fftw3.h>

#ifndef TWO_PI
#define TWO_PI (2 * M_PI)
#endif

#define DEBUG true
#define DEBUGDSP false

class OScofo;
using PitchTemplateArray = std::vector<double>;
