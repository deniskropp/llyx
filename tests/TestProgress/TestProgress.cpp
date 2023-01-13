/*

TestProgress - llyx test

*/

#include <SFML/Graphics.hpp>

#include <llyx/BaseView.hpp>
#include <llyx/ButtonView.hpp>
#include <llyx/FPSView.hpp>
#include <llyx/ProgressView.hpp>
#include <llyx/RootView.hpp>
#include <llyx/TextView.hpp>


class TestView : public llyx::RootView
{
private:
	lli::Event<> timer;

public:
	TestView(sf::RenderWindow& window)
		:
		RootView(window, llyx::RootStyle())
	{
		llyx::TextStyle text1_style;

		text1_style.text_color = llyx::Color(0.0f, 0.26f, 0.29f);
		text1_style.text_height = 64;
		text1_style.text = "Progress Bar Test";

		auto text1 = std::make_shared<llyx::TextView>(text1_style);

		text1->SetPosition(300, 70);

		AddSubView(text1);


		auto fps = std::make_shared<llyx::FPSView>(llyx::FPSStyle());

		fps->SetPosition(900, 30);

		AddSubView(fps);


		llyx::TextButtonStyle tbs;

		tbs.border_width = 3;
		tbs.border_color = llyx::Color(0.7f, 0.9f, 0.9f);
		tbs.color = llyx::Color(0.1f, 0.5f, 0.5f);
		tbs.text = "Press me!";

		auto button1 = std::make_shared<llyx::TextButtonView>(tbs);

		button1->SetPosition(400, 200);

		button1->ClickEvent.Attach(this, [&window](int x, int y) { window.close(); });

		AddSubView(button1);


		for (int i = 0; i < 4; i++) {
			llyx::ProgressStyle ps;

			ps.border = i+1;
			ps.border_color = llyx::Color(0.8f, 0.8f, 0.8f);
			ps.color = llyx::Color(0.0f, 0.0f, 0.8f);

			auto progress = std::make_shared<llyx::ProgressView>(ps);
			auto p = std::make_shared<float>(0.4f + i * 0.2f);

			progress->SetProgress(*p);
			progress->SetBounds(200, 400 + i * 80, 400, 30);

			AddSubView(progress);


			timer.Attach(this, [progress,p,i]() {
				*p += (i + 1) * 0.01f;

				if (*p > 1.0f)
					*p = 0.0f;

				progress->SetProgress(*p);
				});
		}

//		timer.Attach([this]() { timer.Dispatch(); });

		timer.Dispatch();
	}


};



int main()
{
	//	parallel_f::system::instance().setDebugLevel("FrameQueue", 1);
//	parallel_f::system::instance().setAutoFlush(parallel_f::system::AutoFlush::EndOfLine);

//	lli::EventManager::Instance().Enable();

	sf::RenderWindow window(sf::VideoMode({1200, 800}), "TestProgress");

	std::shared_ptr<TestView> testview = std::make_shared<TestView>(window);


	sf::Clock clock;

	while (window.isOpen()) {
//		lli::EventManager::Instance().Flush();

		if (testview->NeedsRepaint() || clock.getElapsedTime().asSeconds() > 1.0f) {
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
