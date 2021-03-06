#include <load_plugins/PluginInterface.hpp>
#include <load_plugins/PluginServiceInterface.hpp>

#include <PluginFactory/MakePluginMethods.hpp>
#include <iostream>

namespace bar {
    
    // Plugin Bar will print "bar" to std::out,
    // and it will call PluginServiceInterface::barCalled()
    class BarPlugin : public load_plugins::MyPlugin
    {
    public:
        BarPlugin(void* service)
            : service_(static_cast<load_plugins::PluginServiceInterface*>(service))
        {
        }
        
        void do_stuff() override
        {
            std::cout << "bar" << std::endl;
            service_->barCalled();
        }
        
    private:
        load_plugins::PluginServiceInterface * const service_;
    };
    
}

MAKE_PLUGIN_METHODS(load_plugins::MyPlugin, bar::BarPlugin)
