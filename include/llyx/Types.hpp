#pragma once

#include <SFML/Graphics.hpp>


namespace llyx {


struct Bounds
{
	int x;
	int y;
	int w;
	int h;

	Bounds()
		:
		x(0),
		y(0),
		w(0),
		h(0)
	{
	}

	Bounds(int x, int y, int w, int h)
		:
		x(x),
		y(y),
		w(w),
		h(h)
	{
	}

	bool contains(int X, int Y)
	{
		if (X < x)
			return false;

		if (Y < y)
			return false;

		if (X >= x + w)
			return false;

		if (Y >= y + h)
			return false;

		return true;
	}

	Bounds operator +(const sf::Vector2u& v)
	{
		return Bounds(x + v.x, y + v.y, w, h);
	}
};


class Color
{
private:
	float r;
	float g;
	float b;
	float a;

public:
	Color()
		:
		r(0.0f),
		g(0.0f),
		b(0.0f),
		a(0.0f)
	{
	}

	Color(float r, float g, float b, float a = 1.0f)
		:
		r(r),
		g(g),
		b(b),
		a(a)
	{
	}

	Color darker() const
	{
		return Color(r * 0.7f, g * 0.7f, b * 0.7f, a);
	}

	Color lighter() const
	{
		return Color(r * 1.33f, g * 1.33f, b * 1.33f, a);
	}

	operator sf::Color() const
	{
		float scale = 1.0f;

		if (r > scale)
			scale = r;

		if (g > scale)
			scale = g;

		if (b > scale)
			scale = b;

		return sf::Color((int)(r / scale * 255.0f), (int)(g / scale * 255.0f), (int)(b / scale * 255.0f), (int)(a * 255.0f));
	}

	operator bool() const
	{
		return a > 0.0f;
	}
};


}
