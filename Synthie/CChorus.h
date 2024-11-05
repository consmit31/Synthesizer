#pragma once
#include <vector>
#include <algorithm>
class CChorus
{
public:
	CChorus(void);

	void SetSampleRate(double s);
	void Process(double* frame1, double* frame2);
	void XmlLoad(IXMLDOMNode* xml);

private:
	double m_delay;
	double m_dry;
	double m_wet;
	double m_modRange;
	double m_modRate;
	int m_wrloc;
	double m_sampleRate;

	std::vector<double> m_leftQ;
	std::vector<double> m_rightQ;

	double Clamp(double value, double minV, double maxV) {
		return (std::max)(minV, (std::min)(maxV, value));
	}
};

