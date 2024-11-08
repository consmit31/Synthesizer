#pragma once
#include <vector>
class CFlange
{
public:
	CFlange(void);

	void setSampleRate(double s) { m_sampleRate = s; }

	void Process(double* frameIn, double* frameOut);
	void XmlLoad(IXMLDOMNode* xml);

private:
	double m_delay;
	double m_dry;
	double m_wet;
	double m_modRange;
	double m_modRate;
	double m_level;
	int m_wrloc;
	double m_sampleRate;

	std::vector<double> m_leftQ;
	std::vector<double> m_rightQ;

	std::vector<double> m_outL;
	std::vector<double> m_outR;
};

