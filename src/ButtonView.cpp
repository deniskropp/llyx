#include <llyx/ButtonView.hpp>

#include <llyx/Elements.hpp>


namespace llyx {


ButtonView::ButtonView(const ButtonStyle& style)
	:
	style(style),
	state(State::NONE)
{
	auto background = std::make_shared<BackgroundElement>(style.color);

	AddElement(background);

	if (style.border_width > 0.0f) {
		auto border = std::make_shared<BorderElement>(style.border_color, style.border_width);

		AddElement(border);
	}
}

void ButtonView::OnEnter(int x, int y)
{
	state = State::HIGHLIGHT;

	elements[0]->As<BackgroundElement>().SetColor(style.color.lighter());

	DoRepaint();
}

void ButtonView::OnLeave(int x, int y)
{
	state = State::NONE;

	elements[0]->As<BackgroundElement>().SetColor(style.color);

	DoRepaint();
}

void ButtonView::OnButtonDown(int x, int y)
{
	state = State::PRESSED;

	elements[0]->As<BackgroundElement>().SetColor(style.color.darker());

	DoRepaint();
}

void ButtonView::OnButtonUp(int x, int y)
{
	state = State::HIGHLIGHT;

	elements[0]->As<BackgroundElement>().SetColor(style.color.lighter());

	ClickEvent.Dispatch(x, y);

	DoRepaint();
}


ImageButtonView::ImageButtonView(const ImageButtonStyle& style)
	:
	ButtonView(style)
{
	auto image = std::make_shared<ImageElement>(style.filename);

	// TODO: add auto-center of image

	AddElement(image);


	SetSize(image->GetSize());
}


TextButtonView::TextButtonView(const TextButtonStyle& style)
	:
	ButtonView(style)
{
	auto text = std::make_shared<TextElement>(style.text, style.text_color, style.text_height);

	// TODO: add auto-center of text

	AddElement(text);


	SetSize(text->GetSize());
}


}
