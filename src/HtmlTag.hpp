#pragma once

#include "Position.hpp"
#include "RenderElement.hpp"
#include "StyleContext.hpp"
#include <string>
namespace HtmlTag {
struct HtmlTag {
protected:
    std::string tagName;
	StyleContext style;
    Position pos;
public:
    virtual std::shared_ptr<RenderElement> renderContent(const std::string& content) = 0;
    virtual void setStyle(const StyleContext& ctx) { this->style = ctx; }
    virtual StyleContext getStyle() { return this->style; }
    virtual bool isClosingTag(const std::string& tagName) const {
        return tagName.compare("/" + this->tagName) == 0;
    }
    virtual std::string getTagName() const { return this->tagName; }
    virtual void setPosition(Position pos) { this->pos = pos; }
    virtual Position computeNextPosition() { return this->pos; }
};
class DocType : public HtmlTag {
public:
    std::shared_ptr<RenderElement> renderContent(const std::string& content);
};
class Html : public HtmlTag {
public:
    std::shared_ptr<RenderElement> renderContent(const std::string& content);
};
class Title : public HtmlTag {
public:
    std::shared_ptr<RenderElement> renderContent(const std::string& content);
};
class Body : public HtmlTag {
public:
    std::shared_ptr<RenderElement> renderContent(const std::string& content);
    void setStyle(const StyleContext& ctx);
    StyleContext getStyle();
};
class H1 : public HtmlTag {
public:
    std::shared_ptr<RenderElement> renderContent(const std::string& content);
    void setStyle(const StyleContext& ctx);
    StyleContext getStyle();
};
class H2 : public HtmlTag {
public:
    std::shared_ptr<RenderElement> renderContent(const std::string& content);
    void setStyle(const StyleContext& ctx);
    StyleContext getStyle();
};
class P : public HtmlTag {
public:
    std::shared_ptr<RenderElement> renderContent(const std::string& content);
    void setStyle(const StyleContext& ctx);
    StyleContext getStyle();
};
}
