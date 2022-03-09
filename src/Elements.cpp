#include <sstream>

#include <llyx/Elements.hpp>


namespace llyx {


BackgroundElement::BackgroundElement(Color color)
	:
	color(color)
{
}

BackgroundElement::BackgroundElement(std::string image_file)
{
}

void BackgroundElement::SetColor(const Color& color)
{
	this->color = color;
}

void BackgroundElement::Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const
{
	auto bounds = view->GetBounds();

	sf::VertexArray va(sf::TriangleFan, 4);

	va[0] = sf::Vertex(sf::Vector2f(0.0f, 0.0f), color);
	va[1] = sf::Vertex(sf::Vector2f(0.0f, (float)bounds.h), color);
	va[2] = sf::Vertex(sf::Vector2f((float)bounds.w, (float)bounds.h), color);
	va[3] = sf::Vertex(sf::Vector2f((float)bounds.w, 0.0f), color);

	frame->draw(va, states);
}


BorderElement::BorderElement(Color color, float width)
	:
	color(color),
	width(width)
{
}

void BorderElement::Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const
{
	auto bounds = view->GetBounds();

	sf::VertexArray va(sf::TriangleFan, 4);

	va[0] = sf::Vertex(sf::Vector2f(-width / 2.0f, -width / 2.0f), color);
	va[1] = sf::Vertex(sf::Vector2f(width / 2.0f, width / 2.0f), color);
	va[2] = sf::Vertex(sf::Vector2f(bounds.w - width / 2.0f, width / 2.0f), color);
	va[3] = sf::Vertex(sf::Vector2f(bounds.w + width / 2.0f, -width / 2.0f), color);

	frame->draw(va, states);

	va[0] = sf::Vertex(sf::Vector2f(bounds.w - width / 2.0f, width / 2.0f), color);
	va[1] = sf::Vertex(sf::Vector2f(bounds.w - width / 2.0f, bounds.h - width / 2.0f), color);
	va[2] = sf::Vertex(sf::Vector2f(bounds.w + width / 2.0f, bounds.h + width / 2.0f), color);
	va[3] = sf::Vertex(sf::Vector2f(bounds.w + width / 2.0f, -width / 2.0f), color);

	frame->draw(va, states);

	va[0] = sf::Vertex(sf::Vector2f(width / 2.0f, bounds.h - width / 2.0f), color);
	va[1] = sf::Vertex(sf::Vector2f(-width / 2.0f, bounds.h + width / 2.0f), color);
	va[2] = sf::Vertex(sf::Vector2f(bounds.w + width / 2.0f, bounds.h + width / 2.0f), color);
	va[3] = sf::Vertex(sf::Vector2f(bounds.w - width / 2.0f, bounds.h - width / 2.0f), color);

	frame->draw(va, states);

	va[0] = sf::Vertex(sf::Vector2f(-width / 2.0f, -width / 2.0f), color);
	va[1] = sf::Vertex(sf::Vector2f(-width / 2.0f, bounds.h + width / 2.0f), color);
	va[2] = sf::Vertex(sf::Vector2f(width / 2.0f, bounds.h - width / 2.0f), color);
	va[3] = sf::Vertex(sf::Vector2f(width / 2.0f, width / 2.0f), color);

	frame->draw(va, states);
}


ImageElement::ImageElement(std::string filename)
{
	if (!texture.loadFromFile(filename))
		throw std::runtime_error(filename);
}

ImageElement::ImageElement(sf::Image& image)
{
	if (!texture.loadFromImage(image))
		throw std::runtime_error("load from image failed");
}

void ImageElement::Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const
{
	sf::Sprite sprite;

	sprite.setTexture(texture);

	frame->draw(sprite, states);
}

sf::Vector2u ImageElement::GetSize() const
{
	return texture.getSize();
}


TextElement::TextElement(std::string string, const Color& color, int height)
{
	if (!font.loadFromFile("media/Calibri.ttf"))	// TODO: Make parameter
		throw std::runtime_error("media/Calibri.ttf");

	text.setFont(font);
	text.setFillColor(color);
	text.setString(string);

	text.setCharacterSize(height);
}

void TextElement::SetText(std::string string)
{
	text.setString(string);
}

void TextElement::Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const
{
	states.transform.translate(sf::Vector2f(5.0f, 0.0f));

	frame->draw(text, states);
}

sf::Vector2u TextElement::GetSize() const
{
	return sf::Vector2u((unsigned int)(text.getGlobalBounds().getSize().x * 1.16f),
				        (unsigned int)(text.getCharacterSize() * 1.4f));
}


RowElement::RowElement(std::vector<std::string> strings, const std::vector<Color>& colors, int height, Color background)
	:
	background(background),
	selected(false)
{
	if (!font.loadFromFile("media/Calibri.ttf"))	// TODO: Make parameter
		throw std::runtime_error("media/Calibri.ttf");

	for (size_t i = 0; i < strings.size(); i++) {
		auto text = std::make_shared<sf::Text>();

		text->setFont(font);
		text->setFillColor(colors[i]);
		text->setString(strings[i]);

		text->setCharacterSize(height);

		texts.push_back(text);
	}
}

void RowElement::SetSelected(bool selected)
{
	this->selected = selected;
}

void RowElement::Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const
{
	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f((float)GetSize().x, (float)GetSize().y));
	rect.setFillColor(selected ? background.lighter().lighter() : background);

	frame->draw(rect, states);

	states.transform.translate(sf::Vector2f(3.0f, 2.0f));

	for (auto t : texts) {
		frame->draw(*t, states);

		states.transform.translate(sf::Vector2f(0.0f, t->getGlobalBounds().getSize().y));
	}
}

sf::Vector2u RowElement::GetSize() const
{
	float width = 7.0f;

	for (auto t : texts)
		width += t->getGlobalBounds().getSize().x;

	return sf::Vector2u((unsigned int)width, (unsigned int)(texts[0]->getCharacterSize() * 1.3f + 4.0f));
}


FPSElement::FPSElement(const Color& text_color, int text_height)
	:
	text_color(text_color),
	text_height(text_height)
{
	if (!font.loadFromFile("media/Calibri.ttf"))	// TODO: Make parameter
		throw std::runtime_error("media/Calibri.ttf");
}

void FPSElement::Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const
{
	std::stringstream ss;

	ss << "FPS " << FPS::Instance().Count();


	sf::Text text;

	text.setFont(font);
	text.setCharacterSize(text_height);
	text.setString(ss.str());
	text.setFillColor(text_color);


	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f(text.getGlobalBounds().getSize().x + 2.0f, text.getCharacterSize()*1.5f));
	rect.setFillColor(sf::Color::Black);


	frame->draw(rect, states);
	frame->draw(text, states);
}


ProgressElement::ProgressElement(Color color)
	:
	color(color),
	progress(0.0f)
{
}

void ProgressElement::SetProgress(float progress)
{
	this->progress = progress;
}

void ProgressElement::Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const
{
	auto bounds = view->GetBounds();

	sf::VertexArray va(sf::TriangleFan, 4);

	va[0] = sf::Vertex(sf::Vector2f(1.0f, 1.0f), color);
	va[1] = sf::Vertex(sf::Vector2f(1.0f, (float)(bounds.h - 1)), color);
	va[2] = sf::Vertex(sf::Vector2f(1.0f + (bounds.w - 2) * progress, (float)(bounds.h - 1)), color);
	va[3] = sf::Vertex(sf::Vector2f(1.0f + (bounds.w - 2) * progress, 1.0f), color);

	frame->draw(va, states);
}


}
