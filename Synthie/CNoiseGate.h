#pragma once
#include <algorithm>
class CNoiseGate
{
public:
	CNoiseGate::CNoiseGate();
	void XmlLoad(IXMLDOMNode* xml);
	void Process(double* frame1, double* frame2);

private:
	double m_threshold;

	double m_dry;
	double m_wet;

	double m_leftGate;
	double m_rightGate;

	double m_attack;
	double m_release;

	double Clamp(double value, double min, double max) { return (std::max)(min, (std::min)(max, value)); }
};

