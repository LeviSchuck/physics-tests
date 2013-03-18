#include "lib/world.hpp"
namespace Bullet{
	class BulletWorld : public World::Earth {
	public:
		virtual ~BulletWorld() {};
	};
};