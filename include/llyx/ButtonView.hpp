#pragma once

#include <SFML/Graphics.hpp>

#include <llyx/Event.hxx>

#include "View.hpp"
#include "Types.hpp"


namespace llyx {


struct ButtonStyle
{
	Color color;

	float border_width;
	Color border_color;

	ButtonStyle(Color color = Color(), float border_width = 2.0f, Color border_color = Color(1.0f, 1.0f, 1.0f))
		:
		color(color),
		border_width(border_width),
		border_color(border_color)
	{
	}
};

class ButtonView : public View
{
private:
	enum class State {
		NONE = 0,
		HIGHLIGHT = 1,
		PRESSED = 2
	};

	ButtonStyle style;
	State state;

public:
	ButtonView(const ButtonStyle& style);

protected:
	virtual void OnEnter(int x, int y);
	virtual void OnLeave(int x, int y);
	virtual void OnButtonDown(int x, int y);
	virtual void OnButtonUp(int x, int y);

public:
	lli::Event<int,int> ClickEvent;		// Click: x, y
};


struct ImageButtonStyle : public ButtonStyle
{
	std::string filename;
};

class ImageButtonView : public ButtonView
{
public:
	ImageButtonView(const ImageButtonStyle& style);
};


struct TextButtonStyle : public ButtonStyle
{
	std::string text;
	Color text_color;
	int text_height;

	TextButtonStyle(std::string text = "", Color text_color = Color(1.0f, 1.0f, 1.0f), int text_height = 32)
		:
		text(text),
		text_color(text_color),
		text_height(text_height)
	{
	}
};

class TextButtonView : public ButtonView
{
public:
	TextButtonView(const TextButtonStyle& style);
};


}
