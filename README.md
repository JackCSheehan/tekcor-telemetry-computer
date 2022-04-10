## TEKCOR at UT Dallas
## Model Rocket Telemetry Computer (Fall 2021 - Spring 2022)
---
## Overview
TEKCOR is a division of AIAA at UT Dallas. TEKCOR is a student-led program to build and fly a model rocket from scratch. The rocket is powered by a class H model rocket motor and flies with a small electronics payload designed to collect telemetry data during the flight. This repository contains the code that collects and records the flight telemetry data.

The code reads from a BMP180 to collect pressure, temperature, and altitude and writes that data to a .csv file using a microSD reader/writer module.

After the flight, the data is visualized using the [TEKCOR Telemetry Tool](https://github.com/JackCSheehan/tekcor-telemetry-tool), a Streamlit application to plot each of the telemetry items over time during the flight.
