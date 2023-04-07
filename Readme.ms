 ## VCPKG Visual Studio Integratiton
(Visual Studio integration)[https://learn.microsoft.com/en-us/vcpkg/users/buildsystems/msbuild-integration]

the second method using a nuget packate its been more reliable for me

Install-Package vcpkg.C.Users.fmend.vcpkg -Source "C:\Users\fmend\vcpkg\scripts\buildsystems"

### Hot Reload
When reloading the library I wont reload GLFW just the game logic
Realoading the window context its crashing the app