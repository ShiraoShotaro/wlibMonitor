#include "DataSet.hpp"
#include <iostream>
#include <thread>
#include <sstream>

mtr::DataSet::DataSet(const std::size_t & max_length, const json11::Json & json, bool & result) {
	result = false;
	if (json.is_array()) {
		auto json_array = json.arrayItems();
		for (auto p = json_array.begin(); p != json_array.end(); ++p){
			std::string label = (*p)["label"].asString("Unnamed label");
			int r = (*p)["r"].asInt(255);
			int g = (*p)["g"].asInt(255);
			int b = (*p)["b"].asInt(255);
			double max = (*p)["max"].asDouble(1000);
			double min = (*p)["min"].asDouble(0);
			this->columns_.emplace_back(max_length, max, min, label, sf::Color(r,g,b));
			std::cout << "[Monitor:INFO]Add column - " << label << " RGB(" << r << ", " << g << ", " << b << ")" << std::endl;
			result = true;
		}
	}

	if (result) {
		std::cout << "[Monitor:INFO]max length - " << max_length << std::endl;
		std::cout << "[Monitor:INFO]column amount number - " << this->columns_.size() << std::endl;
	}
	else std::cerr << "[Monitor:ERROR]DATA DEFINITON json is illegal format. Json root must be array." << std::endl;
}

void mtr::DataSet::add(const std::string & line) {
	//lineƒp[ƒX
	std::stringstream sstr{ line };
	std::string buf;
	std::vector<std::string> v;
	while (std::getline(sstr, buf, ',')) {
		v.push_back(buf);
	}

	if (v.size() == this->columns_.size()) {
		std::cout << "[Monitor:WARNING]Given arguments and columns are unequal size." << std::endl;
	}

	{
		std::lock_guard<std::mutex> lock(this->mutex_);
		auto n = this->columns_.begin();
		auto p = v.begin();
		for (; n != this->columns_.end(); ++n) {
			if (p != v.end()) {
				try {
					double val = std::stod(*p);
					n->add(val);
				}
				catch (std::invalid_argument e) {
					n->add(n->min_data_value_);
				}
				++p;
			}
			else n->add(n->min_data_value_);
		}
	}
	
}

void mtr::DataSet::draw(const ViewType type, sf::RenderTexture & screen_buffer) const{
	for (auto p = this->columns_.begin(); p != this->columns_.end(); ++p) {
		screen_buffer.draw(p->draw(type));
	}
}
