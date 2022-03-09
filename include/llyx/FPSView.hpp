#pragma once

#include "View.hpp"


namespace llyx {


struct FPSStyle
{
	Color text_color;
	int text_height;

	FPSStyle(Color text_color = Color(1.0f, 1.0f, 1.0f), int text_height = 48)
		:
		text_color(text_color),
		text_height(text_height)
	{
	}
};

class FPSView : public View
{
private:
	FPSStyle style;

public:
	FPSView(const FPSStyle& style);
};


}
