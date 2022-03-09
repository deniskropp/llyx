#pragma once

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"
#include "Types.hpp"


namespace llyx {


struct TextStyle : public BaseStyle
{
	std::string text;
	Color text_color;
	int text_height;

	TextStyle(std::string text = "", Color text_color = Color(1.0f, 1.0f, 1.0f), int text_height = 32)
		:
		text(text),
		text_color(text_color),
		text_height(text_height)
	{
	}
};

class TextView : public BaseView
{
private:
	TextStyle style;
	std::shared_ptr<TextElement> text_element;

public:
	TextView(const TextStyle& style);

	void SetText(std::string text);
};


}
