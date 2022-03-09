#include <llyx/BaseView.hpp>

#include <SFML/Graphics.hpp>


namespace llyx {


BaseView::BaseView(const BaseStyle& style)
	:
	style(style)
{
	if (style.background_image != "") {
		background_element = std::make_shared<BackgroundElement>(style.background_image);

		AddElement(background_element);

		SetSize(background_element->GetSize());
	}
	else if (style.background_color) {
		background_element = std::make_shared<BackgroundElement>(style.background_color);

		AddElement(background_element);
	}

	if (style.border) {
		border_element = std::make_shared<BorderElement>(style.border_color, (float)style.border);

		AddElement(border_element);
	}
}


}
