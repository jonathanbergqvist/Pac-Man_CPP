# Pac-Man_CPP
Repo for learning more C++ by recreating Pac-Man.

## Configuration with vcpkg and CMake
This project uses vcpkg for package management and CMake for building.

### CMakeUserPresets.json
```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "Path\\to\\vcpkg"
      }
    }
  ]
}
```