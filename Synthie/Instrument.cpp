#include "stdafx.h"
#include "Instrument.h"


CInstrument::CInstrument()
{
	std::fill(std::begin(m_effects), std::end(m_effects), false);
}
// Constructor to set the beats per minute
CInstrument::CInstrument(double bpm)
{
	std::fill(std::begin(m_effects), std::end(m_effects), false);
	m_bpm = bpm;
}

CInstrument::~CInstrument()
{
}
