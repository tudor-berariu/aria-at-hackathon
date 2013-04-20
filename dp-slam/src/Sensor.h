class Sensor
{
 public:
  virtual ~Sensor() {}

  // Sensors must provide odometric data
  virtual OdometricData readData() {}
};
