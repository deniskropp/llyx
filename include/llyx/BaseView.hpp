#pragma once

#include <SFML/Graphics.hpp>

#include "Elements.hpp"
#include "Types.hpp"
#include "View.hpp"


namespace llyx {


struct BaseStyle
{
	Color background_color;
	std::string background_image;

	unsigned int border;
	Color border_color;

	BaseStyle(Color background_color = Color(),
				std::string background_image = "",
				unsigned int border = 0,
				Color border_color = Color())
		:
		background_color(background_color),
		background_image(background_image),
		border(border),
		border_color(border_color)
	{
	}
};


class BaseView : public View
{
private:
	BaseStyle style;

protected:
	std::shared_ptr<BackgroundElement> background_element;
	std::shared_ptr<BorderElement> border_element;

public:
	BaseView(const BaseStyle& style);
};


}
