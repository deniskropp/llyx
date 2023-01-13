#pragma once

#include <memory>
#include <set>
#include <vector>

#include <SFML/Graphics.hpp>

#include <llyx/Event.hxx>

#include "Types.hpp"


/*

IDEAS
- Move data from Style to Content/Data (DataSource)
- 

*/


namespace llyx {


class View;


class Frame : public sf::RenderTexture
{
private:
	sf::Time time;

public:
	Frame(unsigned int width, unsigned int height, sf::Time time) : time(time)
	{
		if (!create({width, height}))
			throw std::runtime_error("could not create frame texture");
	}

	sf::Time GetTime() const { return time; }

	static std::shared_ptr<Frame> Create(const View* root, sf::Time time);
};


class View
{
public:
	class Element : public sf::Transform
	{
		friend class View;

	protected:
		View* view;

	protected:
		Element() : view(0) {}

	public:
		virtual sf::Vector2u GetSize() const
		{
			return sf::Vector2u(0, 0);
		}

		virtual void Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const = 0;

		template <typename E>
		E& As()
		{
			return *dynamic_cast<E*>(this);
		}
	};

protected:
	Bounds bounds;
	sf::Transformable transformable;
	std::set<std::shared_ptr<View>> subviews;
	std::vector<std::shared_ptr<Element>> elements;
	std::shared_ptr<View> entered;

public:
	Bounds GetBounds() const;
	void SetBounds(const Bounds& bounds);
	void SetBounds(int x, int y, int w, int h) { SetBounds(Bounds(x, y, w, h)); }

	sf::Vector2u GetPosition() const { return sf::Vector2u(bounds.x, bounds.y); }
	void SetPosition(int x, int y);
	void SetPosition(sf::Vector2u pos) { SetPosition(pos.x, pos.y); }

	void SetSize(int w, int h);
	void SetSize(sf::Vector2u size) { SetSize(size.x, size.y); }

	lli::Event<int,int> Position;
	lli::Event<int,int> Size;

protected:
	bool repaint = false;

	void DoRepaint() { repaint = true; }

public:
	bool NeedsRepaint();

protected:
	View();

	void AddSubView(std::shared_ptr<View> view);
	void AddElement(std::shared_ptr<Element> element);

protected:
	virtual void OnEnter(int x, int y) {}
	virtual void OnLeave(int x, int y) {}
	virtual void OnMotion(int x, int y);
	virtual void OnButtonDown(int x, int y);
	virtual void OnButtonUp(int x, int y);
	virtual void OnScroll(int x, int y, int w);
	virtual void OnKeyDown(sf::Keyboard::Key key);
	virtual void OnKeyUp(sf::Keyboard::Key key);

public:
	void Render(std::shared_ptr<Frame> frame, sf::RenderStates states = sf::RenderStates::Default) const;
};


}
