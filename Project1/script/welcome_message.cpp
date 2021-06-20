#include <gazebo/gazebo.hh>

namespace gazebo {

class WelcomeMessage : public WorldPlugin {
  public: WelcomeMessage() : WorldPlugin() {
    printf("Welcome to my world!");
  }

  public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) {}
};

GZ_REGISTER_WORLD_PLUGIN(WelcomeMessage)

} //namespace gazebo

