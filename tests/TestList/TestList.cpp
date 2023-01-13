/*

TestList - llyx test

*/

#include <array>
#include <iostream>
#include <list>
#include <memory>
#include <queue>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <llyx/BaseView.hpp>
#include <llyx/ButtonView.hpp>
#include <llyx/Elements.hpp>
#include <llyx/FPSView.hpp>
#include <llyx/ListView.hpp>
#include <llyx/RootView.hpp>


class TestView : public llyx::RootView
{
public:
	TestView(sf::RenderWindow& window)
		:
		RootView(window, llyx::RootStyle())
	{
		llyx::ListStyle list_style;

		list_style.text_height = 20;
		list_style.grid_width = 2;

		auto list = std::make_shared<llyx::ListView>(list_style);

		list->SetPosition(100, 100);

		AddSubView(list);

		llyx::ListItemStyle item_style;

		item_style.background = llyx::Color(1.0f, 1.0f, 1.0f);
		item_style.strings = { "This is a list item" };
		item_style.colors = { llyx::Color(0.0f, 0.0f, 0.0f) };

		list->AddRow(item_style);



		auto fps = std::make_shared<llyx::FPSView>(llyx::FPSStyle());

		fps->SetPosition(900, 30);

		AddSubView(fps);



		llyx::TextButtonStyle tbs;

		tbs.border_width = 3;
		tbs.border_color = llyx::Color(0.7f, 0.9f, 0.9f);
		tbs.color = llyx::Color(0.1f, 0.5f, 0.5f);
		tbs.text = "Press me!";

		auto button1 = std::make_shared<llyx::TextButtonView>(tbs);

		button1->SetBounds(llyx::Bounds(400, 200, 200, 100));

		button1->ClickEvent.Attach(this, [&window](int x, int y) { window.close(); });

		AddSubView(button1);
	}


};



int main()
{
//	parallel_f::system::instance().setDebugLevel("FrameQueue", 1);
//	parallel_f::system::instance().setAutoFlush(parallel_f::system::AutoFlush::EndOfLine);

//	lli::EventManager::Instance().Enable();

	sf::RenderWindow window(sf::VideoMode({1200, 800}), "TestList");

	std::shared_ptr<TestView> testview = std::make_shared<TestView>(window);


	sf::Clock clock;

	while (window.isOpen()) {
//		lli::EventManager::Instance().Flush();

		if (testview->NeedsRepaint() || clock.getElapsedTime().asSeconds() > 3.7f) {
			clock.restart();

			window.clear();

			window.draw(*testview);

			window.display();
		}
		else
			sf::sleep(sf::milliseconds(20));


		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			default:
				testview->ProcessEvent(event);
				break;
			}
		}
	}

	return 0;
}
