// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "taginfo.h"
#include <stdexcept>
#include <algorithm>

namespace
{
template <typename A, typename B> bool contains(const A& container, const B& element)
{
    return std::find(container.begin(), container.end(), element) != container.end();
}
}

ModelView::TagInfo::TagInfo() : m_min(0), m_max(-1), m_childCount(0)
{

}

ModelView::TagInfo ModelView::TagInfo::defaultTag(std::string name)
{
    return TagInfo(std::move(name), 0, -1, {});
}

ModelView::TagInfo ModelView::TagInfo::propertyTag(std::string name, std::string property_type)
{
    return TagInfo(std::move(name), 1, 1, {std::move(property_type)});
}

std::string ModelView::TagInfo::name() const
{
    return m_name;
}

int ModelView::TagInfo::min() const
{
    return m_min;
}

int ModelView::TagInfo::max() const
{
    return m_max;
}

int ModelView::TagInfo::childCount() const
{
    return m_childCount;
}

//! Returns true if given tag has already maximum number of assigned items.

bool ModelView::TagInfo::maximumReached() const
{
    return m_max != -1 && m_max == m_childCount;
}

bool ModelView::TagInfo::isValidChild(const std::string& child) const
{
    return m_modelTypes.empty() ? true : contains(m_modelTypes, child);
}

void ModelView::TagInfo::add(const std::string& child)
{
    if (!isValidChild(child))
        throw std::runtime_error("TagInfo::add() -> Invalid child.");

    if (maximumReached())
        throw std::runtime_error("TagInfo::add() -> Maximum reached.");

    m_childCount++;
}

void ModelView::TagInfo::remove()
{
    if (childCount() == m_min)
        throw std::runtime_error("TagInfo::add() -> Minimum reached");

    m_childCount--;
}

bool ModelView::TagInfo::isSingleItemTag() const
{
    return m_min == 1 && m_max == 1 && m_childCount == 1;
}

ModelView::TagInfo::TagInfo(std::string name, int min, int max, std::vector<std::string> modelTypes)
    : m_name(std::move(name)), m_min(min), m_max(max), m_childCount(0),
      m_modelTypes(std::move(modelTypes))
{

}