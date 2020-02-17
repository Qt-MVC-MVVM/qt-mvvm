// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/refviewitem.h>
#include <vector>

using namespace ModelView;

struct RefViewItem::RefViewItemImpl {
    std::vector<std::unique_ptr<RefViewItem>> children;
    int rows{0};
    int columns{0};
    RefViewItemImpl() {}

    void appendRow(std::vector<std::unique_ptr<RefViewItem>> items)
    {
        if (items.empty())
            throw std::runtime_error("Error in RefViewItem: attempt to cappend empty row");

        if (columns > 0 && items.size() != static_cast<size_t>(columns))
            throw std::runtime_error("Error in RefViewItem: wrong number of columns.");

        children.insert(children.end(), std::make_move_iterator(items.begin()),
                        std::make_move_iterator(items.end()));
        columns = static_cast<int>(items.size());
        ++rows;
    }
};

RefViewItem::RefViewItem() : p_impl(std::make_unique<RefViewItemImpl>()) {}

RefViewItem::~RefViewItem() = default;

int RefViewItem::rowCount() const
{
    return p_impl->rows;
}

int RefViewItem::columnCount() const
{
    return p_impl->columns;
}

void RefViewItem::appendRow(std::vector<std::unique_ptr<RefViewItem>> items)
{
    p_impl->appendRow(std::move(items));
}

void RefViewItem::clear()
{
    p_impl->children.clear();
    p_impl->rows = 0;
    p_impl->columns = 0;
}
