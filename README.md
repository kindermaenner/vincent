Vincent
=======

Overview
--------
Vincent is a small network-based messaging tool originally developed around the year 2000 to enable communication between students working within a company environment.

At a time when modern messaging platforms did not yet exist in their current form, Vincent provided a simple way to stay connected using a lightweight UDP-based protocol and a Windows tray application.

This repository contains a modernized version of the original Visual Studio 6 MFC application, updated to build with current MSVC toolchains while preserving its original behaviour.

## Project background and purpose

Vincent was born out of a very simple situation.

At the time, we (Abraquax and Spex) were both working in the same company — one as a student, the other as an apprentice — sharing an office with several other students. As it often happens in such environments, people came and went. Projects changed, schedules shifted, and in a large organization it was easy to lose track of each other. 

We wanted a simple way to stay in touch. So instead of relying on external tools (which were limited or non-existent in this form at the time), we built our own. And that was the moment Vincent was created.

Key features
------------
- UDP-based messaging (broadcast/peer-to-peer) on a configurable port (default 5078)
- System tray icon with context menu and notification handling
- Simple user login/logout and message routing protocol (single-character markers)
- Local logging with automatic rotation when file size exceeds a configured threshold
- About dialog showing product version read from PE version resource

Project layout
--------------
- src/                — application source (.cpp)
- include/            — public headers and resource.h
- res/                — icons, cursor and resource snippets (Vincent.rc2)
- Vincent.vcxproj      — Visual Studio project (configured for MSVC toolset v145)
- Vincent.sln          — Visual Studio solution
- build/              — build output (created by build steps)

Technical notes
---------------
- Language: C++ with MFC (Win32 dialog application)
- Charset: Multi-Byte Character Set (MBCS) for compatibility with original code
- Precompiled header: pch.h (StdAfx/Precompiled header model)
- Logging: CLogFile (uses CStdioFile) with rotation; default filename "Vincent.log"
- Networking: CDgramSocket (CAsyncSocket) — receives UDP datagrams and forwards payload to UI
- Tray: CTrayIcon wrapper (original sample code by Paul DiLascia)
- Version info: uses Windows Version APIs (linked with version.lib)

Configuration
-------------
The application uses an .INI-style profile filename (set at startup to <exe>.ini). Configuration keys read from the profile include:

- Section: "Network"
  - Port (default 5078)
  - Server / ServerToUse (list of server addresses used for routing)
  - PingTime (default 10000 ms)
  - PingTimeout (default 20000 ms)

- Section: "Misc"
  - MessageStackLength (default 10)
  - ShowMessageBox (default TRUE)
  - BeepOnMessage (default TRUE)

- Section: "Log"
  - FileName (default "vincent.log")
  - MaxFileSize (default 1024000)

Defaults are embedded in the source (see constants in src/VincentDlg.cpp and src/LogFile.cpp).

Build instructions
------------------
Prerequisites:
- Windows (Win32)
- Visual Studio 2022/2026 with "Desktop development with C++" and MFC support installed

Using Visual Studio IDE:
1. Open Vincent\Vincent.sln
2. Select configuration (Debug or Release) and platform Win32
3. Build the solution

Using command line (MSBuild):
  msbuild .\Vincent\Vincent.sln /p:Configuration=Release

Notes: the project is configured for the MSVC v145 toolset and targets 32-bit (x86) Win32.

CMake build (alternative)
-------------------------
This repository includes a CMake configuration that allows building the project with CMake generators (Visual Studio or Ninja).

1. Create an out-of-source build directory, configure and generate (example using Visual Studio 2026 generator):

   cmake -S . -B build -G "Visual Studio 18 2026" -A Win32

2. Build the Release configuration:

   cmake --build build --config Release

Notes:
- Use an appropriate generator name for your Visual Studio installation if the above generator is not available (e.g. "Visual Studio 17 2022" or adjust to your environment). For Visual Studio Community 2026 use "Visual Studio 18 2026".
- CMake >= 3.16 is recommended to enable target_precompile_headers. If your CMake is older, the build will still work but precompiled headers are not configured automatically.

Runtime behaviour / usage
-------------------------
- On startup the app registers a profile (.ini) next to the executable and reads network and UI settings.
- The app creates a UDP socket and (by default) sends a login broadcast; it periodically pings peers.
- Messages use simple markers defined in source (e.g. '#' for login, '-' for logout, '*' for user messages).
- The app places an icon in the system tray and supports showing/hiding the main dialog, opening the log file, and changing user name.

Known issues & compatibility
---------------------------
- This is a modernized port of a VS6 application. Some legacy code patterns remain (use of C-style string APIs, manual memory management in older modules).
- Target is Win32/MFC; building for x64 or non-MFC toolchains requires additional changes.

License
-------
This project is licensed under the [MIT License](LICENSE).
