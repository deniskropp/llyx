#include <llyx/ImageView.hpp>

#include <llyx/Elements.hpp>


namespace llyx {


ImageView::ImageView(const ImageStyle& style)
	:
	BaseView(style)
{
	sf::Image image;

	if (image.loadFromFile(style.source)) {
		auto element = std::make_shared<ImageElement>(image);

		AddElement(element);

		SetSize(element->GetSize());
	}
}


}