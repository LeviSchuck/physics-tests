#pragma once
#include "enums.hpp"
#include "mesh.hpp"
#include "pentity.hpp"
#include "gentity.hpp"
#include "world.hpp"
#include "graphics.hpp"

namespace World {
	class Object {
		class ObjectContents * _contents;
	public:
		Object(World::Earth *, Graphical::Engine *);
		virtual ~Object();

		void init(const Entity_Types, const char * mesh, const MassProperties mass, const Transform t);
		void init(const Entity_Types, const Vec4 data, const MassProperties mass, const Transform t);
		void init(ShapeList & list, const MassProperties mass, const Transform t);

		const Vec3 getPosition() const;
		const Vec4 getQuatOrientation() const;
		const Vec3 getEulerOrientation() const;
		void setPosition(const Vec3 vec);
		void setOrientation(const Vec4 vec);
		void setOrientation(const Vec3 vec);
		void setStatic(bool);

		void hideGraphics();
		void showGraphics();

		void color(const Vec4 color);

		const Mesh getMesh() const;

		const Entity_Types type() const;

	};
}