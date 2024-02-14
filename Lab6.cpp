#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int main() {
	string background = "images1/backgrounds/winter.png";
	string foreground = "images1/characters/yoda.png";
	Texture backgroundTex;
	if (!backgroundTex.loadFromFile(background)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}
	Texture foregroundTex;
	if (!foregroundTex.loadFromFile(foreground)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}
	Image backgroundImage;
	backgroundImage = backgroundTex.copyToImage();
	Image foregroundImage;
	foregroundImage = foregroundTex.copyToImage();
	Vector2u sz = backgroundImage.getSize();

	//Gets the corner pixel and sets that as the green color to be removed
	Color green = foregroundImage.getPixel(0, 0);

	//Sets the tolorance for the green pixel removal
	int colorDiff = 65;

	for (int y = 0; y < sz.y; y++) {
		for (int x = 0; x < sz.x; x++) {

			//Gets the current and foreground and background pixel and sets that to a variable
			Color curFore = foregroundImage.getPixel(x, y);
			Color curBack = backgroundImage.getPixel(x, y);

			if (
				//checks the diffrence in color for each rbg value between the forground and green pixel 
				//and checks if they are within the colorDiff tolorance
				abs((curFore.r - green.r)) < colorDiff &&
				abs((curFore.g - green.g)) < colorDiff &&
				abs((curFore.b - green.b)) < colorDiff
				) {

				//sets the forground pixel to the background image 
				foregroundImage.setPixel(x, y, curBack);
			}
		}
	}
	// By default, just show the foreground image
	RenderWindow window(VideoMode(1024, 768), "Here's the output");
	Sprite sprite1;
	Texture tex1;
	tex1.loadFromImage(foregroundImage);
	sprite1.setTexture(tex1);
	window.clear();
	window.draw(sprite1);
	window.display();
	while (true);
}