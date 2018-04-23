#include "DataList.hpp"

mtr::DataList::DataList(const std::size_t & max_length, const double max_data_value, const double min_data_value, const std::string & label, const sf::Color & color)
	: max_length_(max_length), color_(color), max_data_value_(max_data_value), min_data_value_(min_data_value), rate_bias_((max_data_value / min_data_value) / 1000.0f)
{}

void mtr::DataList::add(const double data) {
	this->data_.push_back(data);
	while (this->data_.size() > max_length_) this->data_.pop_front();
}

sf::VertexArray mtr::DataList::draw(const ViewType type) const{
	sf::VertexArray vtx(sf::LinesStrip);

	const float width = this->max_length_ / 1800.0f;
	switch (type) {
	case kSolid:
	{
		float x = 0;
		for (auto p = this->data_.begin(); p != this->data_.end(); ++p, ++x) {
			vtx.append(sf::Vertex(sf::Vector2f(width * x, static_cast<float>(this->rate_bias_ * *p + 40.0f)), this->color_));
			vtx.append(sf::Vertex(sf::Vector2f(width * x, 40.0f), this->color_));
		}
	}
		break;

	case kLine:
	{
		float x = 0;
		for (auto p = this->data_.begin(); p != this->data_.end(); ++p, ++x) {
			vtx.append(sf::Vertex(sf::Vector2f(width * x, static_cast<float>(this->rate_bias_ * *p + 40.0f)), this->color_));
		}
	}
		break;

	default:
		break;
	}

	return vtx;
}
