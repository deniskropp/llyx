#include <llyx/ProgressView.hpp>

#include <llyx/Elements.hpp>


namespace llyx {


ProgressView::ProgressView(const ProgressStyle& style)
	:
	BaseView(style),
	style(style)
{
	progress_element = std::make_shared<ProgressElement>(style.color);

	AddElement(progress_element);
}

void ProgressView::SetProgress(float progress)
{
	progress_element->SetProgress(progress);

	DoRepaint();
}


}
