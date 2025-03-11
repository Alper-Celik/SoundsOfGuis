from conan import ConanFile
from conan.tools.cmake import cmake_layout


class SOGRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain", "PkgConfigDeps"
    # tool_requires = "pkgconf/2.2.0"  # Specify the version of pkgconf

    def build_requirements(self):
        # Ensure pkgconf is available during build time
        self.tool_requires("pkgconf/2.2.0")

    def requirements(self):
        self.requires("openal-soft/1.23.1")
        self.requires("libsndfile/1.2.2")
        self.requires("fmt/11.0.2")
        self.requires("boost/1.86.0")
        self.requires("ms-gsl/4.1.0")
        self.requires("magic_enum/0.9.7")
        self.requires("cli11/2.4.2")

        self.requires("tomlplusplus/3.4.0")
        self.requires("yaml-cpp/0.8.0")
        self.requires("qt/6.7.3")

        if self.settings.os == "Linux":
            self.requires("at-spi2-core/2.53.1")
