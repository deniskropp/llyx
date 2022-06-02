#include <llyx/ListView.hpp>

#include <llyx/Elements.hpp>


namespace llyx {


ListView::ListView(const ListStyle& style)
	:
	style(style),
	offset(0)
{
	Clear();
}

void ListView::AddRow(const ListItemStyle& style)
{
//	auto row = std::make_shared<RowElement>(style.strings, style.colors, this->style.text_height, style.background);



	unsigned int height = 0;

	auto row = std::make_shared<RowElement>(style.strings, style.colors, this->style.text_height, style.background);

	for (auto e : elements) {
		unsigned int h = e->GetSize().y;

		row->translate(sf::Vector2f(0.0f, (float)h));

		height += h;
	}

	height += row->GetSize().y;

	AddElement(row);


	SetSize(std::max(bounds.w, (int)row->GetSize().x), (int)height);

	DoRepaint();
}

void ListView::Clear()
{
	elements.clear();


	auto background = std::make_shared<BackgroundElement>(Color(0.15f, 0.15f, 0.15f));

	AddElement(background);


	auto border = std::make_shared<BorderElement>(Color(0.33f, 0.39f, 0.40f), 7.0f);

	AddElement(border);


	DoRepaint();
}

void ListView::OnButtonDown(int x, int y)
{
	float ty = 0.0f;

	for (size_t i = 2; i < elements.size(); i++) {
		auto row = (RowElement*)(elements[i].get());

		if (y < ty || y >= ty + row->GetSize().y) {
			row->SetSelected(false);
		}
		else {
			row->SetSelected(true);

			Selected.Dispatch((int)i - 2);
		}

		ty += row->GetSize().y;
	}

	DoRepaint();
}

void ListView::OnScroll(int x, int y, int w)
{
	transformable.move(sf::Vector2f(0.0f, (float)w));

	DoRepaint();
}

void ListView::OnKeyDown(sf::Keyboard::Key key)
{
	switch (key) {
	case sf::Keyboard::Key::Down:
		transformable.move(sf::Vector2f(0.0f, 10.0f));
		break;
	default:
		break;
	}

	DoRepaint();
}

void fillElements()
{

}


}
