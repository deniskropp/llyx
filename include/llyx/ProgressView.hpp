#pragma once

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"
#include "Types.hpp"


namespace llyx {


struct ProgressStyle : public BaseStyle
{
	Color color;

	ProgressStyle(Color color = Color(1.0f, 1.0f, 1.0f))
		:
		color(color)
	{
	}
};

class ProgressView : public BaseView
{
private:
	ProgressStyle style;
	std::shared_ptr<ProgressElement> progress_element;

public:
	ProgressView(const ProgressStyle& style);

	void SetProgress(float progress);
};


}