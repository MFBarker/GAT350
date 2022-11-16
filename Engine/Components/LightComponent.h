#pragma once
#include "Framework/Component.h"

namespace neu
{
	class Program;

	class LightComponent : public Component
	{
	public:
		enum Type
		{
			Point,       //0
			Directional, //1
			Spot         //2
		};

	public:
		CLASS_DECLARATION(LightComponent)

		void Update() override;

		void SetProgram(std::shared_ptr<Program> program , int index);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::vec3 color{ 0 };

		Type type = Type::Point;
		float cutoff = 45.0f;
		float exponent = 50.0f;
	};
}