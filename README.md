# ESP32 Weather App

The project is a sort of weather app displayed on a ESP32. It fetches real-time data from SMHI open API data and presents the information on different tiles. The project uses the LVGL library with different tiles to show of different weather data such as temperatur, degrees, weather this week and so on. The goal is to have an small device showing you the accurate and necessary data for your localisation.

---

## Table of Contents
- [Overview](#overview)  
- [Features](#features)  
- [System Architecture](#system-architecture)  
- [Hardware Requirements](#hardware-requirements)  
- [Software Requirements](#software-requirements)  
- [Installation](#installation)  
- [Tile System](#tile-system)  
- [SMHI API Integration](#smhi-api-integration)  
- [Project Structure](#project-structure)  
- [Roadmap](#roadmap)  
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

## Hardware Requirements

- ESP32 module (with display)  
- USB-C cable (for downloading data to ESP32)  

---

## Software Requirements

- PlatformIO  
- C++  
- LVGL  

---

## Installation

1. Clone the repository  
2. Install PlatformIO on Visual Studio Code  
3. Set ESP32 in download mode (check ESP32 documentation for your ESP32)  
4. Use USB-C cabel (or other) to connect your computer and ESP32. Through PlatformIO build project  

**OBS before compiling:**  
- Change Wifi network and password to your own  

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

## Roadmap

- None

---

## Contact

**Author:** Group 18 (Mattias HL, George B, Gustav, Amin, Simon S)

**Email:** Mahc24@student.bth.se  

**GitHub:** https://github.com/Se-sSi/Weather-Data-Visualization
