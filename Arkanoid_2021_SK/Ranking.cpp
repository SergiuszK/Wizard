#include "Ranking.h"

Ranking::Ranking(float width, float height) {

	font.loadFromFile("Almendra-BoldItalic.otf");
	//print();
	refresh(width, height);
	selectedItemIndex = 0;
	//draw();

}

bool cmp(std::pair<int, std::string>& a,
	std::pair<int, std::string>& b)
{
	return a.first > b.first;
}

void Ranking::refresh(float width, float height) {
	upload();
	std::sort(sorted.begin(), sorted.end(), cmp);
	text.setFont(font);
	text.setFillColor(sf::Color::Red);

	//text.setPosition(sf::Vector2f(width / 2, height / 5 * 1));
	//rankingText.push_back(text);
	int i = 1;
	text.setString("RANKING");
	text.setPosition(sf::Vector2f(width / 2, height / 3 * 0.2 * i++));
	rankingText.push_back(text);
	text.setFillColor(sf::Color::White);
	for (auto it : sorted)
	{

		//std::cout << it.second;
		//std::cout << it.first;

		text.setString(std::to_string(i - 1) + ". " + it.second + "    " + std::to_string(it.first));
		text.setPosition(sf::Vector2f(width / 2, height / 3 * 0.2 * i++));
		rankingText.push_back(text);
		if (i == 12)
			break;

	}
	while (i < 12) {
		text.setString(std::to_string(i - 1) + ". ---- ----");
		text.setPosition(sf::Vector2f(width / 2, height / 3 * 0.2 * i++));
		rankingText.push_back(text);
	}

	text.setString("Wyjdz");
	text.setPosition(sf::Vector2f(width / 2, height / 3 * 0.2 * i++));
	rankingText.push_back(text);
}

void Ranking::upload() {
	std::string text;
	std::fstream file;
	file.open(path, std::ios::in | std::ios::app);


	int temp;
	std::string temp1;
	while (!file.eof()) {
		std::getline(file, text);
		std::regex process("name: (.*) score: (.*)");
		std::smatch sm;

		while (text != "" and std::regex_search(text, sm, process)) {
			//std::cout << sm.prefix();
			temp = stoi(sm[2]);
			//records[std::stoi(temp)] = sm[1];
			temp1 = sm[1];
			std::pair<int, std::string> pair(temp, temp1);
			sorted.push_back(pair);
			text = sm.suffix();
		}


	}
	file.close();

}

void Ranking::print() {
	for (auto it = sorted.cbegin(); it != sorted.cend(); ++it)
	{
		std::cout << it->second << " " << it->first << " " << "\n";
	}
}

void Ranking::MoveUp() {
	if (selectedItemIndex - 1 >= 0) {
		rankingText[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		rankingText[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Ranking::MoveDown() {
	if (selectedItemIndex + 1 < rankingText.size()) {
		rankingText[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		rankingText[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}