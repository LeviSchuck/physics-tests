#pragma once
#include "vec.hpp"
#include "enums.hpp"

namespace Graphical {
	class Entity {
		Entity_Types _type;
	public:
		Entity(const Entity_Types type, const Vec3 & data);
		Entity(const Entity_Types type, const char * mesh);
		const Vec3 getPosition() const;
		void setPosition(const Vec3 & vec);
		void hide();
		void show();
		void color(const Vec4 & color);
		inline const Entity_Types type() const {return _type;}
		virtual ~Entity();
		const Vec4 getQuatOrientation() const;
		const Vec3 getEulerOrientation() const;
		void setOrientation(const Vec4 & vec);
		void setOrientation(const Vec3 & vec);
		const Mesh & getMesh() const;
	};
};