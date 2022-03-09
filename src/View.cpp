#include <SFML/Graphics.hpp>

#include <llyx/View.hpp>


namespace llyx {


std::shared_ptr<Frame> Frame::Create(const View* root, sf::Time time)
{
	auto bounds = root->GetBounds();
	std::shared_ptr<Frame> frame = std::make_shared<Frame>(bounds.w, bounds.h, time);

	root->Render(frame);

	frame->display();

	return frame;
}


View::View()
{
}

Bounds View::GetBounds() const
{
	return bounds;
}

void View::SetBounds(const Bounds& bounds)
{
	SetPosition(bounds.x, bounds.y);
	SetSize(bounds.w, bounds.h);
}

void View::SetPosition(int x, int y)
{
	if (x != bounds.x || y != bounds.y) {
		bounds.x = x;
		bounds.y = y;

		Position.Dispatch(x, y);
	}
}

void View::SetSize(int w, int h)
{
	if (w != bounds.w || h != bounds.h) {
		bounds.w = w;
		bounds.h = h;

		Size.Dispatch(w, h);
	}
}

void View::AddSubView(std::shared_ptr<View> view)
{
	subviews.insert(view);
}

void View::AddElement(std::shared_ptr<Element> element)
{
	element->view = this;

	elements.push_back(element);
}

bool View::NeedsRepaint()
{
	bool ret = repaint;
	
	repaint = false;
	
	for (auto view : subviews) {
		if (view->NeedsRepaint())
			ret = true;
	}

	return ret;
}

void View::Render(std::shared_ptr<Frame> frame, sf::RenderStates states) const
{
	states.transform.translate(sf::Vector2f((float)bounds.x, (float)bounds.y));

	states.transform *= transformable.getTransform();

	for (auto element : elements) {
		sf::RenderStates es = states;

		es.transform *= *(sf::Transform*)element.get();

		element->Render(frame, es);
	}

	for (auto view : subviews)
		view->Render(frame, states);
}

void View::OnMotion(int x, int y)
{
	for (auto v : subviews) {
		if (v->bounds.contains(x, y)) {
			if (v != entered) {
				if (entered)
					entered->OnLeave(x, y);

				v->OnEnter(x, y);

				entered = v;
			}
			
			v->OnMotion(x - v->bounds.x, y - v->bounds.y);
		}
		else if (v == entered) {
			v->OnLeave(x, y);

			entered = 0;
		}
	}
}

void View::OnButtonDown(int x, int y)
{
	for (auto v : subviews) {
		if (v->bounds.contains(x, y))
			v->OnButtonDown(x - v->bounds.x, y - v->bounds.y);
	}
}

void View::OnButtonUp(int x, int y)
{
	for (auto v : subviews) {
		if (v->bounds.contains(x, y))
			v->OnButtonUp(x - v->bounds.x, y - v->bounds.y);
	}
}

void View::OnScroll(int x, int y, int w)
{
	for (auto v : subviews) {
		if (v->bounds.contains(x, y))
			v->OnScroll(x - v->bounds.x, y - v->bounds.y, w);
	}
}

void View::OnKeyDown(sf::Keyboard::Key key)
{
	if (entered)
		entered->OnKeyDown(key);
}

void View::OnKeyUp(sf::Keyboard::Key key)
{
	if (entered)
		entered->OnKeyUp(key);
}


}
