#include "motor.hh"

struct motorCommands{
	forwardLeft = 0x08;
	backwardLeft = 0x0A;
	forwardRight = 0x0C;
	backwardRight = 0x0E;
} motorCommands;

class motorController{
private:
	motor leftMotor;
	motor rightMotor;
public:
	motorController(std::string portName, int baud);

	void forward(int speed);

	void backward(int speed);

	void left(int speed);

	void right(int speed);

	void stop();

}