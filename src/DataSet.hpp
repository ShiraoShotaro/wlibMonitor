#pragma once
#ifndef MTR_DATASET_HPP
#define MTR_DATASET_HPP

#include <vector>
#include <mutex>
#include <SFML/Graphics/RenderTexture.hpp>
#include "json11.hpp"
#include "DataList.hpp"

namespace mtr {

class DataSet {
public:
	typedef DataList::ViewType ViewType;

	DataSet(const std::size_t & max_length, const json11::Json & json, bool & result);

	void add(const std::string & line);

	void draw(const ViewType type, sf::RenderTexture & screen_buffer) const;

private:
	std::vector<DataList> columns_;
	std::mutex mutex_;
};

}

#endif