#include <SFML/Graphics.hpp>

int main(int argc, char * argv[]) {

	sf::RenderWindow window;
	window.create(sf::VideoMode(1920, 1080, 32), "wlibMonitor", (sf::Style::Titlebar | sf::Style::Default));
	window.setVerticalSyncEnabled(false);
	
	sf::RenderTexture screen_buffer;
	screen_buffer.create(1920, 1080);  //�o�b�t�@�����
	screen_buffer.setSmooth(true);  //�X���[�X�ݒ�ON
	sf::Sprite sprite(screen_buffer.getTexture());  //�o�b�t�@��ʗp�̃X�v���C�g�����

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F4 && event.key.alt) window.close();
			}
		}

		screen_buffer.clear();

		

		screen_buffer.display();
		window.clear();
		window.draw(sprite);
		window.display();
	}

}