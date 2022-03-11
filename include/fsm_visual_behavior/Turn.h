#ifndef BEHAVIOR_TREES_TURN_H
#define BEHAVIOR_TREES_TURN_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace behavior_trees
{

    class Turn : public BT::ActionNodeBase
    {
        public:
            explicit Turn(const std::string& name);

            void halt();

            BT::NodeStatus tick();

        private:
            ros::NodeHandle nh_;
            ros::Publisher vel_pub_;

            int counter_;
    };

}

#endif // BEHAVIOR_TREES_TURN_H