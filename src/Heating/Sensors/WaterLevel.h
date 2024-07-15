/*
 * Water-Level.h
 *
 *  Created on: 16 Apr 2019
 *      Author: David
 */

#ifndef SRC_HEATING_SENSORS_WATERLEVELSENSOR_H_
#define SRC_HEATING_SENSORS_WATERLEVELSENSOR_H_

#include "SensorWithPort.h"

class WaterLevelSensor : public SensorWithPort
{
public:
	explicit WaterLevelSensor(unsigned int sensorNum) noexcept;

	GCodeResult Configure(GCodeBuffer& gb, const StringRef& reply, bool& changed) override THROWS(GCodeException);
#if SUPPORT_REMOTE_COMMANDS
	GCodeResult Configure(const CanMessageGenericParser& parser, const StringRef& reply) noexcept override;
#endif

	void Poll() noexcept override;
	const char *_ecv_array GetShortSensorType() const noexcept override { return TypeName; }

	static constexpr const char *_ecv_array TypeName = "waterlevel";

private:
	void CalcDerivedParameters() noexcept;

	// Configurable parameters
	float lowTemp, highTemp;
	bool filtered;

	// Derived parameters
	int adcFilterChannel;
	float WaterIncreasePerCount;

	static constexpr float DefaultLowTemp = 0.0;
	static constexpr float DefaultHighTemp = 100.0;
};

#endif /* SRC_HEATING_SENSORS_WATERLEVELSENSOR_H_ */
