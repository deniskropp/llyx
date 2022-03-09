#include <llyx/FPSView.hpp>

#include <llyx/Elements.hpp>


namespace llyx {


FPSView::FPSView(const FPSStyle& style)
	:
	style(style)
{
	auto fps = std::make_shared<FPSElement>(style.text_color, style.text_height);

	AddElement(fps);
}


}
