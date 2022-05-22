#ifndef TRAPDOOR_VILLAGE_HELPER_H
#define TRAPDOOR_VILLAGE_HELPER_H

#include <MC/Village.hpp>
#include <unordered_set>

#include "CommandHelper.h"

namespace tr {

    class VillageHelper {
       public:
        void TickParticles();
        ActionResult ListTickingVillages();

       private:
        std::unordered_set<Village*> vs_;
        bool show_center_ = false;
        bool show_iron_spawn_ = false;
        bool show_bounds_ = false;
        bool show_poi_query_ = false;
    };

}  // namespace tr

#endif
