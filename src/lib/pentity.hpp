#pragma once
#include <vector>
#include "vec.hpp"
#include "enums.hpp"
#include "mesh.hpp"
#include "world.hpp"

namespace Physical {
	class Entity {
	private:
		Entity_Types _type;
		size_t _body_index;
		::std::vector<size_t> _shape_index;
		World::Earth * _world;
		size_t createShape(const Entity_Types type, const Mesh & m);
		size_t createShape(const Entity_Types type, const Vec3 data);
	public:
		Entity(const Entity_Types type, World::Earth *);
		virtual ~Entity();
		void init(const Mesh & m, const MassProperties mass);
		void init(const Vec3 data, const MassProperties mass);
		void init(const ShapeList & list, const MassProperties mass);
		
		const Vec3 getPosition() const;
		const Vec4 getQuatOrientation() const;
		const Vec3 getEulerOrientation() const;
		const Transform getTransform() const;
		void setPosition(const Vec3 vec);
		void setOrientation(const Vec4 vec);
		void setOrientation(const Vec3 vec);
		void setTransform(const Transform t);

		inline const Entity_Types type() const {return _type;}
	};
};