#include <map>
#include <queue>

#include <llyx/RootView.hpp>

#include <llyx/Elements.hpp>


namespace llyx {


class FrameManager
{
public:
	static FrameManager& Instance()
	{
		static FrameManager manager;

		return manager;
	}

private:
	class FrameQueue
	{
	private:
		const RootView* view;
		sf::Clock clock;
		std::queue<std::shared_ptr<llyx::Frame>> frames;

	public:
		FrameQueue(const RootView* view)
			:
			view(view)
		{
		}

		std::shared_ptr<llyx::Frame> currentFrame()
		{
			sf::Time currentTime = clock.getElapsedTime();

			if (!frames.empty() && frames.front()->GetTime() < currentTime)
				frames.pop();

			if (frames.empty())
				frames.push(llyx::Frame::Create(view, currentTime));

///			if (frames.back()->GetTime() - currentTime < sf::milliseconds(20))
///				frames.push(llyx::Frame::Create(view, frames.back()->GetTime() + sf::milliseconds(16)));

//			LOG_DEBUG("FrameQueue::currentFrame() --> queue length %zu\n", frames.size());

			return frames.front();
		}
	};

private:
	std::map<const RootView*, std::shared_ptr<FrameQueue>> queues;

public:
	std::shared_ptr<llyx::Frame> GetFrame(const RootView* view)
	{
		std::shared_ptr<FrameQueue> queue = GetQueue(view);

		return queue->currentFrame();
	}

	void Dispose(const RootView* view)
	{
		queues.erase(view);
	}

private:
	std::shared_ptr<FrameQueue> GetQueue(const RootView* view)
	{
		auto it = queues.find(view);

		if (it == queues.end()) {
			auto queue = std::make_shared<FrameQueue>(view);

			queues.insert(std::make_pair(view, queue));

			return queue;
		}

		return (*it).second;
	}
};



RootView::RootView(sf::RenderTarget& target, const RootStyle& style)
	:
	target(target),
	style(style)
{
	SetSize(target.getSize());


	auto background = std::make_shared<BackgroundElement>(style.color);

	AddElement(background);


	Size.Attach(this, [this](int w, int h) { FrameManager::Instance().Dispose(this); });

	DoRepaint();
}

RootView::~RootView()
{
	FrameManager::Instance().Dispose(this);
}

void RootView::ProcessEvent(sf::Event& event)
{
	switch (event.type) {
	case sf::Event::Resized:
		SetSize(event.size.width, event.size.height);
		target.setView(sf::View(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((float)event.size.width, (float)event.size.height))));
		break;
	case sf::Event::MouseMoved:
		OnMotion(event.mouseMove.x, event.mouseMove.y);
		break;
	case sf::Event::MouseButtonPressed:
		OnButtonDown(event.mouseButton.x, event.mouseButton.y);
		break;
	case sf::Event::MouseButtonReleased:
		OnButtonUp(event.mouseButton.x, event.mouseButton.y);
		break;
	case sf::Event::MouseWheelScrolled:
		OnScroll(event.mouseWheelScroll.x, event.mouseWheelScroll.y, event.mouseWheelScroll.delta);
		break;
	case sf::Event::KeyPressed:
		OnKeyDown(event.key.code);
		break;
	case sf::Event::KeyReleased:
		OnKeyUp(event.key.code);
		break;
	default:
		break;
	}
}

void RootView::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	std::shared_ptr<llyx::Frame> frame = FrameManager::Instance().GetFrame(this);


	sf::Sprite sprite;

	sprite.setTexture(frame->getTexture());

	target.draw(sprite, states);
}


}
