#pragma once
#include "AudioNode.h"
#include "Note.h"
#include <algorithm>

class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	CInstrument(double);
	virtual ~CInstrument();
	virtual void SetNote(CNote *note) = 0;

	bool hasEffect(int effect) { return m_effects[effect]; }
	void setEffect(int effect) { m_effects[effect] = true; }
	int getNumEffects() { return std::count(std::begin(m_effects), std::end(m_effects), true); }

private:
	bool m_effects[3];
};

