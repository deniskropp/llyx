#pragma once

#include "BaseView.hpp"


namespace llyx {


struct ImageStyle : public BaseStyle
{
	std::string source;

	ImageStyle() {}
};


class ImageView : public BaseView
{
public:
	ImageView(const ImageStyle& style);
};


}