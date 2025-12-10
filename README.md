# ESP32 Weather App

## Introduction
The project is a weather app displayed on a ESP32. It fetches real-time data from SMHI open API data and presents the information on different tiles. The project uses the LVGL library with different tiles to show of different weather data such as temperature, weather this week and so on. In addition, it also uses PlatformThe goal was to have an small device showing you the accurate and necessary data for your localisation.

---

## Table of Contents
- [ESP32 Weather App](#esp32-weather-app)
  - [Introduction](#introduction)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Features](#features)
  - [System Architecture](#system-architecture)
  - [Getting started](#getting-started)
    - [Hardware Requirements](#hardware-requirements)
    - [Software Requirements](#software-requirements)
    - [Installation](#installation)
  - [Building and running](#building-and-running)
  - [Tile System](#tile-system)
  - [SMHI API Integration](#smhi-api-integration)
  - [Features](#features-1)
  - [Contact](#contact)

---

## Overview

The ESP32 fetches data from SMHI's free open API. The information is displayed on different UI-Tiles. Each tile has different functions and logic. The system can refresh and load in the newest data. It has an option tile making it able to change different options.

---

## Features

- Integration with SMHI Open Data API  
- Tile-based UI for displaying forecast data  
- Real-time data fetching  
- ESP32-based implementation (WiFi enabled)  
- Support for multiple weather variables such as temperature, wind speed, humidity, precipitation, and cloudiness  
- Easily expandable tile framework  
- Icons for weather conditions  
- Different colours for night/day mode  

---

## System Architecture

- **ESP32 Controller:** Handles network requests, JSON parsing, tile updates, and display logic.  
- **SMHI API Client Module:** Fetches forecast data and returns structured weather objects.  
- **Tile Rendering Engine:** Renders visual tiles, each responsible for one weather attribute.  
  - Base Tile (shared properties and functions to child tiles)  
  - Child Tiles (7-Day-Forecast tile, Historical-Data tile, Option tile, etc.)

---

## Getting started

---

### Hardware Requirements

- ESP32 module (with display)  
- USB-C cable (for downloading data to ESP32)  

---

### Software Requirements

- PlatformIO  
- C++  
- LVGL  

---

### Installation

1. Clone the repository  
2. Install PlatformIO on Visual Studio Code  
3. Set ESP32 in download mode (check ESP32 documentation for your ESP32)  
4. Use USB-C cabel (or other) to connect your computer and ESP32. Through PlatformIO build project  

**OBS before compiling:**  
- Change Wifi network and password to your own  

---

## Building and running

To build you first must connect the esp with the help of the connector. After the connection has been made and the esp has power, it should be set to download mode so it can receive the data. The last step is to upload all from platformIO interface and after it has succeeded just reset the power on the esp and it should now be updated. 

You should start on the starting tile where you can see the title of our project, our group number and the current version. A swipe up should get you to the options menu, here you find a button which you can use to reset to the default city and see the currently selected city. One swipe left of the starting tile you can see the 7-day forecast tile. You can swipe up and down in this tile to be able to see the 7-day forecast on the selected city.

A swipe to the right of the starting tile is where you can see the historical data tile. Here you have a dropdown menu where you can select a parameter, and you also have a slider to interact with the data!

---

## Tile System

Uses a parent based tile system  
- Base Tile (shared properties and functions to child tiles)  
- Child Tiles include (7-Day-Forecast tile, Historical-Data tile, Option tile, etc.)  

Each tile uses self created function that fetches SMHI API data to reduse the amount of api data  
Has a Tile manager, making it esay to remove or add tiles  
Has a timer set to when to update and fetch new API data  

---

## SMHI API Integration

- Uses a SMHI URL to get the API data  
- Self made function is used to fetches some of the API data needed to reduse the loading time.

---

## Features

- [x] US1.1: As a user, I want to see a starting screen to display the current program version and group number.
- [x] US1.2: As a user, I want to see the weather forecast for the next 7 days for the selected city on the second screen in terms of temperature and weather conditions with symbols (e.g., clear sky, rain, snow, thunder) per day at 12:00.
- [x] US1.3: As a user, I want to have a screen to view weather forecast data.
- [x] US2.1: As a user, I want to be able to navigate between different screens (like forecast screen) by sliding a finger over the touch screen
- [x] US3.1: As a user, I want to have a screen to view historical weather data.
- [x] US3.2: As a user, on the third screen I want to view the latest months (SMHI API period: latest-months) of historical hourly data for selected weather parameter in the selected city, using a slider to interact with the historical graph by scrolling where a depleted slider corresponds to the oldest datapoint and a full slider corresponds to the latest datapoint.
- [ ] US4.2: As a user, I want to select weather parameters (e.g., temperature, humidity, wind speed), using a dropdown list, to customize the historical graph.
- [ ] US4.4: As a user, I want to reset the selected city and weather parameter to default using a button.

---

## Contact

**Author:** Group 18 (Mattias HL, George B, Gustav, Amin, Simon S)

**Email:** Mahc24@student.bth.se, gebo24@studen.bth.se 

**GitHub:** https://github.com/Se-sSi/Weather-Data-Visualization
