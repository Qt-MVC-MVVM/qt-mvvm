// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODELCONTROLLER_H
#define MVVM_VIEWMODELCONTROLLER_H

#include "mvvm_global.h"
#include <memory>
#include <vector>

class QStandardItem;
#include <QList>

namespace ModelView
{

class AbstractViewModel;
class SessionItem;
class ChildrenStrategyInterface;
class RowConstructorInterface;

/*!
@class ViewModelController
@brief Syncronizes AbstractViewModel and SessionModel.
*/

class CORE_EXPORT ViewModelController
{
public:
    ViewModelController(AbstractViewModel* view_model);
    virtual ~ViewModelController();

    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

    void setRowConstructor(std::unique_ptr<RowConstructorInterface> row_constructor);

    void reset_view_model();

    virtual void iterate(const SessionItem* item, QStandardItem* parent);

private:
    class ViewModelControllerPrivate;
    std::unique_ptr<ViewModelControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODELCONTROLLER_H