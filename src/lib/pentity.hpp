#pragma once
#include "vec.hpp"
#include "enums.hpp"
#include "world.hpp"

namespace Physical {
	class Entity {
		Entity_Types _type;
		size_t _body_index;
		World::Earth * _world;
	public:
		Entity(const Entity_Types type, const Vec3 & data, const MassProperties & mass, World::Earth *);
		Entity(const Entity_Types type, const Mesh & mesh, const MassProperties & mass, World::Earth *);
		const Vec3 getPosition() const;
		void setPosition(const Vec3 & vec);
		void hide();
		void show();
		
		inline const Entity_Types type() const {return _type;}
		virtual ~Entity();
		const Vec4 getQuatOrientation() const;
		const Vec3 getEulerOrientation() const;
		void setOrientation(const Vec4 & vec);
		void setOrientation(const Vec3 & vec);
	};
};