#include <llyx/TextView.hpp>

#include <llyx/Elements.hpp>


namespace llyx {


TextView::TextView(const TextStyle& style)
	:
	BaseView(style),
	style(style)
{
	text_element = std::make_shared<TextElement>(style.text, style.text_color, style.text_height);

	AddElement(text_element);

	SetSize(text_element->GetSize());
}

void TextView::SetText(std::string text)
{
	text_element->SetText(text);

	SetSize(text_element->GetSize());

	DoRepaint();
}


}
