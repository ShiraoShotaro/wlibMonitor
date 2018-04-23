#pragma once
#ifndef MTR_DATA_HPP
#define MTR_DATA_HPP

#include <string>
#include <list>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace mtr {

class DataList {
public:
	enum ViewType {
		kLine,
		kSolid
	};

	DataList(const std::size_t & max_length, const double max_data_value, const double min_data_value, const std::string & label, const sf::Color & color);

	void add(const double data);

	sf::VertexArray draw(const ViewType type) const;

	const std::size_t max_length_;
	const sf::Color color_;
	const double max_data_value_, min_data_value_;

private:
	std::list<double> data_;
	const double rate_bias_;
};

}

#endif