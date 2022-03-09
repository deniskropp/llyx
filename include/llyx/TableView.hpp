#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include <llyx/Event.hxx>

#include "View.hpp"
#include "Types.hpp"


namespace llyx {


struct TableStyle
{
	int text_height;
	int grid_width;

	TableStyle(int text_height = 32, int grid_width = 2) : text_height(text_height), grid_width(grid_width) {}
};

struct TableRowStyle
{
	Color background;
	std::vector<std::string> strings;
	std::vector<Color> colors;
};

class RowElement;

class TableView : public View
{
private:
	TableStyle style;
//	std::vector<std::shared_ptr<RowElement> rows;
	int offset;

public:
	TableView(const TableStyle& style);
		
	void AddRow(const TableRowStyle& style);

	void Clear();

protected:
	virtual void OnButtonDown(int x, int y);
	virtual void OnScroll(int x, int y, int w);
	virtual void OnKeyDown(sf::Keyboard::Key key);

private:
	void fillElements();

public:
	lli::Event<int> Selected;
};


}
