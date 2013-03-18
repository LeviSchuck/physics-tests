#pragma once
#include "enums.hpp"
#include "pentity.hpp"
#include "gentity.hpp"
#include "world.hpp"

namespace World {
	class Object {
		Entity_Types _type;
		Graphical::Entity * _g;
		Physical::Entity * _p;
	public:
		Object(const Entity_Types type, const Vec3 & data, const MassProperties & mass, World::Earth *);
		Object(const Entity_Types type, const char * mesh, const MassProperties & mass, World::Earth *);
		virtual ~Object();
		
		const Vec3 getPosition() const;
		const Vec4 getQuatOrientation() const;
		const Vec3 getEulerOrientation() const;
		void setPosition(const Vec3 & vec);
		void setOrientation(const Vec4 & vec);
		void setOrientation(const Vec3 & vec);

		void hideGraphics();
		void showGraphics();
		void hidePhysics();
		void showPhysics();

		void color(const Vec4 & color);

		const Mesh & getMesh() const;

		inline const Entity_Types type() const {return _type;}

	};
}