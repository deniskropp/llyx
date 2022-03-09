#pragma once

#include <SFML/Graphics.hpp>

#include "View.hpp"


namespace llyx {


class BackgroundElement : public View::Element
{
private:
	Color color;

public:
	BackgroundElement(Color color = Color());

	BackgroundElement(std::string image_file);

	void SetColor(const Color& color);

	virtual void Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const;
};


class BorderElement : public View::Element
{
private:
	Color color;
	float width;

public:
	BorderElement(Color color = Color(), float width = 2.0f);

	virtual void Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const;
};


class ImageElement : public View::Element
{
private:
	sf::Texture texture;

public:
	ImageElement(std::string filename);

	ImageElement(sf::Image& image);

	virtual void Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const;

	virtual sf::Vector2u GetSize() const;
};


class TextElement : public View::Element
{
private:
	sf::Font font;
	sf::Text text;

public:
	TextElement(std::string string, const Color& color, int height);

	void SetText(std::string string);

	virtual void Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const;

	virtual sf::Vector2u GetSize() const;
};


class RowElement : public View::Element
{
private:
	sf::Font font;
	std::vector<std::shared_ptr<sf::Text>> texts;
	Color background;
	bool selected;

public:
	RowElement(std::vector<std::string> strings, const std::vector<Color>& colors, int height, Color background);

	void SetSelected(bool selected);

	virtual void Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const;

	virtual sf::Vector2u GetSize() const;
};


class FPSElement : public View::Element
{
private:
	sf::Font font;
	Color text_color;
	int text_height;

public:
	FPSElement(const Color& text_color, int text_height);

	virtual void Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const;

private:
	class FPS
	{
	public:
		static FPS& Instance()
		{
			static FPS instance;

			return instance;
		}

	private:
		sf::Clock clock;
		unsigned int frames;
		float fps;

		FPS() : frames(0), fps(0.0f) {}

	public:
		float Count()
		{
			frames++;

			auto time = clock.getElapsedTime();

			if (time.asSeconds() >= 2.0f) {
				fps = frames / time.asSeconds();

				clock.restart();

				frames = 0;
			}

			return fps;
		}
	};
};


class ProgressElement : public View::Element
{
private:
	Color color;
	float progress;

public:
	ProgressElement(Color color = Color());

	void SetProgress(float progress);

	virtual void Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const;
};


}
