# PluginFactory

A small interface-driven toolkit for adding plugins to C++ applications. 

### Quick Tour

The following code snippet shows how to use the PluginFactory.

    PluginFactory::PluginFactory<MyPluginInterface, MyAppInterface> factory("plugins/");
    
    factory.load();

    // store for instantiated plugins
    using MyPlugin = std::unique_ptr<MyPluginInterface>;
    std::deque<MyPlugin> plugins;

    // list all available plugins
    auto availablePlugins = factory.availablePlugins();

    // instantiate all available plugins
    for(const auto& pluginName : availablePlugins)
    {
    	plugins.emplace_back(factory.instance(pluginName));
    }

    // invoke MyPluginInterface::foo() on all loaded plugins
    for(auto& plugin : plugins)
    {
    	plugin->foo();
    }

#### Creating a plugin

    // TODO: implement a small example demonstrating how to implement a plugin. 

NOTE: generally speaking it is good advice that memory shouldn't pass a process/shared-lib
boundary because they may have been compiled with different allocators.

We're going to ignore that advice and instead REQUIRE the plugins to be compiled
with the same settings as the main process. It greatly simplifies working with
the shared libs at the expense of being less flexible. Because of this choice, plugins
compiled with different versions of compiler tool chains may fail to load. 

#### Compiling your plugin on POSIX 

On POSIX systems, you'll most likely have to supply linker arguments to get the symbols in your shared library exported. (e.g. GCC on Linux and clang on Mac support the --export-dynamic to export symbols.)

#### Compiling your plugin on Windows 

On Windows, you'll need to use a compiler intrinsic attribute to indicate which symbols you want exported. 

    __declspec(dllexport) MyPlugin* createPlugin(PluginServiceInterface&);

### Dependencies 

- c++11
- [boost](http://boost.org). Uses boost::filesystem::path.

Used for unit testing on all platforms:

- [UnitTest++](https://github.com/unittest-cpp/unittest-cpp). Unit test framework.

Windows Platforms:

- Visual Leak Detector (VLD). Used on windows to detect memory leaks in unit tests)

### Contributors 

Austin Gilbert <ceretullis@gmail.com>

### License

4-Clause BSD license, see [LICENSE.md](LICENSE.md) for details. Other licensing available upon request. 

### Related Projects 

- plexx
- [CPF](http://sourceforge.net/projects/cpp-plugin/)
- [3xc](https://github.com/rhcad/x3c)
- Qt provides plugin capabilities as well
