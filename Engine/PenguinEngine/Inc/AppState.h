#pragma once

namespace PenguinEngine
{
	class AppState
	{
	public:
		virtual ~AppState() = default;

		virtual void Initialize() {}
		virtual void Terminate() {}

		virtual void Update(float detlaTime) {}
		virtual void Render() {}
		virtual void DebugUI() {}
	};
}