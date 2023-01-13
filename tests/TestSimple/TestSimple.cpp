/*

TestSimple - llyx test

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
#include <llyx/RootView.hpp>
#include <llyx/TextView.hpp>


class TestView : public llyx::RootView
{
public:
	TestView(sf::RenderWindow& window)
		:
		RootView(window, llyx::RootStyle())
	{
		std::array<llyx::Color,4> colors = {
			llyx::Color(0.0f, 0.44f, 0.55f),
			llyx::Color(0.3f, 0.11f, 0.55f),
			llyx::Color(0.9f, 0.22f, 0.11f),
			llyx::Color(0.3f, 0.23f, 0.23f)
		};

		for (int i = 0; i < 4; i++) {
			llyx::TextStyle text1_style;

			text1_style.background_color = colors[i];
			text1_style.border = 2;
			text1_style.border_color = text1_style.background_color.darker();
			text1_style.text = "Test Text";

			auto text1 = std::make_shared<llyx::TextView>(text1_style);

			text1->SetPosition(100 + i * 200, 700);

			AddSubView(text1);
		}


		auto fps = std::make_shared<llyx::FPSView>(llyx::FPSStyle());

		fps->SetPosition(900, 30);

		AddSubView(fps);


//		auto base1 = std::make_shared<llyx::BaseView>(llyx::BaseStyle(llyx::Color(0.5f, 0.5f, 0.5f), "", 5, llyx::Color(0.7f, 0.7f, 0.7f)));

//		base1->SetBounds(llyx::Bounds(200, 300, 400, 200));

//		AddSubView(base1);


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

	sf::RenderWindow window(sf::VideoMode({1200, 800}), "TestSimple");

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
