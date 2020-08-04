# UWPDumper [![Build status](https://ci.appveyor.com/api/projects/status/ys3yvpv0bdel15sx?svg=true)](https://ci.appveyor.com/project/Wunkolo/uwpdumper) [![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/Wunkolo/UWPDumper/master/LICENSE)

---
DLL and Injector for dumping UWP applications at run-time to bypass encrypted file system protection.


Run `UWPInjector.exe` and enter valid UWP Process ID to inject into.
App file system will be dumped into:

`C:\Users\(Username)\AppData\Local\Packages\(Package Family Name)\TempState\DUMP`

List of commands:

`UWPInjector.exe --pid`
`UWPInjector.exe --path`

UWPDumper requires the [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk) to be compiled.
