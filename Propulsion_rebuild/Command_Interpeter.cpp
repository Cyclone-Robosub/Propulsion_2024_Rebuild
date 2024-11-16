// William Barber
#include "Command_Interpreter.h"
#include <iostream>
#include <utility>

//// When compiling for non-RPI devices which cannot run wiringPi library,  
//// use -MOCK_RPI flag to enable mock functions
//#ifndef MOCK_RPI
//#include <wiringPi.h>  // Include wiringPi library by default
//
//#else
//#define PWM_OUTPUT 1
//#define OUTPUT 0
//#define HIGH 1
//#define LOW 0
//
//int wiringPiSetupGpio() {
//    std::cout << "[Mock] wiringPi GPIO set up!" << std::endl;
//    return 0;
//}
//
//void pinMode(int pinNumber, int mode) {
//    std::cout << "[Mock] pinMode: pin " << pinNumber << " set to mode " << mode << std::endl;
//}
//
//void digitalWrite(int pinNumber, int voltage) {
//    std::cout << "[Mock] digitalWrite: pin " << pinNumber << ", voltage " << voltage << std::endl;
//}
//
//void pwmWrite(int pinNumber, int pwm) {
//    std::cout << "[Mock] pwmWrite: pin " << pinNumber << ", PWM " << pwm << std::endl;
//}
//
//#endif
//
//DigitalPin::DigitalPin(int gpioNumber, EnableType enableType) : Pin(gpioNumber), pinStatus(Disabled), enableType(enableType) {}
//
//void DigitalPin::initialize() {
//    pinMode(gpioNumber, OUTPUT);
//}
//
//void DigitalPin::enable() {
//    switch (enableType) {
//    case ActiveHigh:
//        digitalWrite(gpioNumber, HIGH);
//        break;
//    case ActiveLow:
//        digitalWrite(gpioNumber, LOW);
//        break;
//    default:
//        std::cerr << "Impossible pin mode!" << std::endl; //throw exception?
//    }
//    pinStatus = Enabled;
//}
//
//void DigitalPin::disable() {
//    switch (enableType) {
//    case ActiveHigh:
//        digitalWrite(gpioNumber, LOW);
//        break;
//    case ActiveLow:
//        digitalWrite(gpioNumber, HIGH);
//        break;
//    default:
//        std::cerr << "Impossible pin mode!" << std::endl; //throw exception?
//    }
//    pinStatus = Disabled;
//}
//
//bool DigitalPin::enabled() {
//    return pinStatus == Enabled;
//}
//
//
//PwmPin::PwmPin(int gpioNumber) : Pin(gpioNumber), currentPwm(0) {}
//
//void PwmPin::initialize() {
//    pinMode(gpioNumber, PWM_OUTPUT);
//}
//
//void PwmPin::enable() { //TODO: check pwm range (currently assuming 0-255)
//    setPowerAndDirection(255, Forwards);
//    currentPwm = 255;
//}
//
//void PwmPin::disable() { //TODO: check pwm range (currently assuming 0-255)
//    setPowerAndDirection(0, Forwards);
//    currentPwm = 255;
//}
//
//bool PwmPin::enabled() {
//    return currentPwm != 0;
//}
//
//void PwmPin::setPowerAndDirection(int pwmValue, Direction direction) {
//    //TODO: set direction (not sure how to do this w/ pwm. High/low?)
//    pwmWrite(gpioNumber, pwmValue);
//    currentPwm = pwmValue;
//}
//
//
//
//Command_Interpreter_RPi5::Command_Interpreter_RPi5() : thrusterPins(std::vector<PwmPin*>{}), digitalPins(std::vector<DigitalPin*>{}) {}
//Command_Interpreter_RPi5::Command_Interpreter_RPi5(std::vector<PwmPin*> thrusterPins, std::vector<DigitalPin*> digitalPins) :
//    thrusterPins(std::move(thrusterPins)), digitalPins(std::move(digitalPins)) {
//    allPins = std::vector<Pin*>{};
//    allPins.insert(allPins.end(), thrusterPins.begin(), thrusterPins.end());
//    allPins.insert(allPins.end(), digitalPins.begin(), digitalPins.end());
//}
//
//void Command_Interpreter_RPi5::initializePins() {
//    if (wiringPiSetupGpio() == -1) {
//        std::cerr << "Failure to configure GPIO pins through wiringPi!" << std::endl; //throw exception?
//    }
//    for (Pin* pin : allPins) {
//        pin->initialize();
//    }
//}
//
//int Command_Interpreter_RPi5::convertPwmValue(int pwmFrequency) { // converts frequency into range(0, 1023)
//    /*
//     * Converts a pwm frequency between 1100 and 1900 into a magnitude range between 0 and 1023.
//     * @param pwmFrequency: a pwm frequency between 1100 and 1900
//     * @return: a pwm magnitude between 0 and 1023
//     */
//    if (pwmFrequency == 0) {
//        return 0;
//    }
//    const int maxPwmValue = 1900;
//    const int minPwmValue = 1099; // slightly less than 1100 so that a pwm value of 1100 isn't stopped
//    int pwmMagnitude = pwmFrequency - minPwmValue;
//    pwmMagnitude *= (int)((double)(1023) / (double)(maxPwmValue - minPwmValue));
//    return pwmMagnitude;
//}
//
//void Command_Interpreter_RPi5::execute(const Command& command) {
//    for (int i = 0; i < 8; i++) {
//        thrusterPins[i]->setPowerAndDirection(convertPwmValue(command.thruster_pwms[i]), Forwards);
//    }
//    //TODO: duration
//}