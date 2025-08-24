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

## References
- [vcpkg Documentation](https://vcpkg.io/en/index.html)
- [CMake Documentation](https://cmake.org/documentation/)
- [SFML Documentation](https://www.sfml-dev.org/documentation/3.0.1/)
- [GIMP](https://www.gimp.org/)
- [GitHub Copilot Free](https://github.com/features/copilot)