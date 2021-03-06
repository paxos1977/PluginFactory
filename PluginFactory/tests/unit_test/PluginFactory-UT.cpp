#include "./ut_support/UnitTestSupport.hpp"

#include <PluginFactory/PluginFactory.hpp>
#include <PluginFactory/Exceptions.hpp>

#include <vector>

namespace {

    class PluginInterface
    {
    public:
        virtual ~PluginInterface(){}
        virtual void foo() = 0;
    };

    struct PluginFactoryFixture
    {
        using PluginFactory = PluginFactory::PluginFactory<PluginInterface>;
        
        PluginFactoryFixture()
            : factory("./")
        {
        }
        
        PluginFactory factory;
    };
    
    TEST_FIXTURE(PluginFactoryFixture, verifyPluginFactoryInstantiation)
    {
    }
    
    TEST(verifyPluginFactoryInstantiationThrowsOnPathDoesntExist)
    {
        CHECK_THROW(PluginFactory::PluginFactory<PluginInterface> factory("/ThisPath/Doesnt/Exist"), PluginFactory::PluginPathDoesntExist);
    }
    
    TEST(verifyPluginFactoryInstantiationThrowsOnAPathWhichIsntDirectory)
    {
        CHECK_THROW(PluginFactory::PluginFactory<PluginInterface> factory("./cmake_install.cmake"), PluginFactory::PluginPathIsntDirectory);
    }
    
    TEST(verifyPluginFactoryConstructionWithArguments)
    {
        PluginFactory::PluginFactory<PluginInterface> factory("./", 1, "abc", 0.0f);
    }
    
    TEST_FIXTURE(PluginFactoryFixture, verifyLoad)
    {
        auto plugins = factory.availablePlugins();
        CHECK_EQUAL(0U, plugins.size());
    }
    
    /////////////////////////////////////////////////////
    //
    // The tests below here don't proove anything, merely
    // ensure the class template methods are instantiated.
    //
    
    TEST_FIXTURE(PluginFactoryFixture, callLoad)
    {
        factory.load();
    }
    
    TEST(callLoadWithPath)
    {
        PluginFactory::PluginFactory<PluginInterface> factory(".");
        CHECK_THROW(factory.load("path/to/plugin"), PluginFactory::PluginLoaderException);
    }
    
    TEST_FIXTURE(PluginFactoryFixture, callUnload)
    {
        factory.unload();
    }
    
    TEST_FIXTURE(PluginFactoryFixture, callUnloadWithPath)
    {
        factory.unload("path/to/plugin");
    }
    
    TEST_FIXTURE(PluginFactoryFixture, callCreatePlugin)
    {
        CHECK_THROW(factory.instance("something"), ::PluginFactory::PluginNotFoundException);
    }
}
