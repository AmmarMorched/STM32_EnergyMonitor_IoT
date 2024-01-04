# IoT Energy Consumption Monitoring System

## Overview

This project utilizes the STM32F407VG microcontroller to create an intelligent energy consumption monitoring system for eco-friendly homes. The system incorporates various sensors, an LCD display, and WiFi communication for data logging and analysis on the ThingSpeak cloud platform.

## Features

- Real-time monitoring of energy consumption
- Automatic adjustment of ventilation based on temperature
- Smart lighting control using presence detection
- Alert system for energy consumption threshold breaches
- Efficient data transfer using DMA
- Manual system activation with an interrupt switch

## Hardware Components

- Microcontroller: STM32F407VG
- Sensors:
  - Electrical Consumption Sensor: LEM LTS 6-NP (Analog)
  - Temperature Sensor: Analog
  - Presence Sensor: Digital (1 for presence, 0 for no presence)
- Other Components:
  - LCD Display
  - LEDs (Blue for ventilation, Red for energy consumption alert, Green for normal state)
  - ESP8266 WiFi Shield for Cloud Communication (ThingSpeak)
  - Interrupt Switch for Manual Activation
  - ...

## Project Structure

- **/Src**: Contains the source code for the project.
- **/Inc**: Header files.
- **/Libraries**: External libraries if used.
- **/Docs**: Documentation and additional project information.
- **/Hardware_Schematics**: Schematics and diagrams for the hardware setup.

## Getting Started

1. **Setting up STM32 Development Environment**: Ensure you have the necessary tools installed for STM32 development.
2. **Clone the Repository**: `git clone https://github.com/yourusername/your-repository.git`
3. **Hardware Connections**: Refer to the hardware schematics for proper connections.
4. **Configure Project**: Adjust project settings, sensor calibration, and WiFi credentials as needed.
5. **Compile and Flash**: Build and flash the project to your STM32 microcontroller.
6. **Monitor and Analyze**: View real-time data on the LCD and check ThingSpeak for cloud-stored data.

## Contributing

If you'd like to contribute to the project, please follow the [Contributing Guidelines](CONTRIBUTING.md).

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

- Mention any external libraries or tools used.
- Give credit to contributors or sources of inspiration.

