#pragma once

namespace Graphical {
	class Engine {
		class EngineInternals * _internals;
	public:
		void render();
		void setup();
		bool exitRequested();
		void closeup();
		~Engine();
		void * manager();
	};
};