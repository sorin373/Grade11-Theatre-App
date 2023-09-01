# Table of contents

- [Overview](#overview)
- [Installation](#installation)
    - [Windows](#windows)
    - [Unix (Debian)](#unix-debian)
    - [Unix (RPM-based)](#unix-rpm-based)
- [Building the executable binaries](#building-the-executable-binaries)
    - [Windows](#windows)
    - [Debian](#debian)
- [Project Status](#project-status)

# Overview
- This project was created by me and two other students from [Colegiul National Bilingv George Cosbuc](http://cosbucbilingv.ro/). 
- We have created a data storage system that makes use of files as its foundation. To represent the information from these files, we've developed several data structures.
- The program we've built runs on a console interface, presenting users with a Main Menu that grants access to various sub-menus. These sub-menus serve to modify the data stored within the files.
- Our choice of a static memory management system means that it isn't capable of adapting in real-time.

<details>
  <summary><strong>Demo Screenshots</strong></summary>

  ![Screenshot 1](Screenshots/S1.png)
  
  ![Screenshot 2](Screenshots/S2.png)
</details>

# Installation

## Windows

1. Download the Windows installer for the app from the [GitHub Releases](https://github.com/sorin373/Grade11-Theatre-App/releases/tag/v1.0.0) page.

2. Run the installer by double-clicking the downloaded file (`Grade11-Theatre-App-1.0.0-win64.exe`).

3. Follow the on-screen instructions to complete the installation.

4. Once installed, navigate to the installation folder (usually `C:\Program Files\Grade11-Theatre-App 1.0.0`) and find the `Grade11-Theatre-App.exe` file.

5. Double-click `Grade11-Theatre-App.exe` to launch the application.

## Unix (Debian)

1. Download the Debian package (`.deb` file) for the app from the [GitHub Releases](https://github.com/sorin373/Grade11-Theatre-App/releases/tag/v1.0.0) page.
2. Install the package using the software installer
3. By default, the app will be installed in the `/usr/bin` directory. To run the application, open your terminal here and execute:
```bash
$ ./Grade11-Theatre-App
```

## Unix (RPM-based)

1. Download the RPM package (`.rpm` file) for the app from the [GitHub Releases](https://github.com/sorin373/Grade11-Theatre-App/releases/tag/v1.0.0) page.
2. Install the package using the rpm command:
```bash
$ sudo rpm -i Grade11-Theatre-App-1.0.0-Linux.rpm
```
3. By default, the app will be installed in the `/usr/bin` directory. To run the application, open your terminal here and execute:
```bash
$ ./Grade11-Theatre-App
```

# Building the executable binaries

## Windows

- On Windows, you'll need to set up and initialize [CMake](https://cmake.org/download/)
- You can use either the [MSVC](https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options?view=msvc-170) compiler or the [MinGW](https://sourceforge.net/projects/mingw/) compiler

## Debian

- **Install** [CMake](https://cmake.org/download/)
```bash
$ sudo apt-get update && sudo apt-get upgrade
$ sudo snap install cmake --classic
```
- After acquiring the zip file containing the project files, open the folder in Visual Studio Code and use the CMake commands to build the application (or install the [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) and [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extensions).

# Project Status
- The project has been completed on the 10th of January 2023.




