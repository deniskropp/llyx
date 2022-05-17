#pragma once

#include <SFML/Graphics.hpp>

#include "Types.hpp"
#include "View.hpp"


namespace llyx {


struct RootStyle
{
	Color color;

	RootStyle(Color color = Color(0.2f, 0.41f, 0.63f)) : color(color) {}
};


class RootView : public View, public sf::Drawable, public lli::EventListener
{
protected:
	sf::RenderTarget& target;
	RootStyle style;

public:
	RootView(sf::RenderTarget& target, const RootStyle& style = RootStyle());
	virtual ~RootView();

	void ProcessEvent(sf::Event& event);

protected:
	virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


}
