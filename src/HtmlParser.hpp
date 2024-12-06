#pragma once

#include "HtmlTag.hpp"
#include "Position.hpp"
#include "RenderElement.hpp"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>


class HtmlParser{
private:
	std::unordered_map<std::string, std::function<std::shared_ptr<HtmlTag::HtmlTag>()>> nameToTag = {
		std::make_pair("!DOCTYPE", [](){ return std::make_shared<HtmlTag::DocType>();}),
		std::make_pair("html", [](){ return std::make_shared<HtmlTag::Html>();}),
		std::make_pair("title", [](){ return std::make_shared<HtmlTag::Title>();}),
		std::make_pair("body", [](){ return std::make_shared<HtmlTag::Body>();}),
		std::make_pair("h1", [](){ return std::make_shared<HtmlTag::H1>();}),
		std::make_pair("h2", [](){ return std::make_shared<HtmlTag::H2>();}),
		std::make_pair("p", [](){ return std::make_shared<HtmlTag::P>();}),
	};

public:
	HtmlParser();
	std::vector<std::shared_ptr<RenderElement>> parse(Position basePos, const std::string &input);
};
