// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphwidget.h"
#include "graphmodel.h"
#include "graphpropertywidget.h"
#include "graphwidgettoolbar.h"
#include "jobmanager.h"
#include <QBoxLayout>
#include <QDebug>
#include <mvvm/model/modelutils.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

GraphWidget::GraphWidget(GraphModel* model, QWidget* parent)
    : QWidget(parent), toolbar(new GraphWidgetToolBar), m_graphCanvas(new GraphCanvas),
      m_propertyWidget(new GraphPropertyWidget), m_model(nullptr)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    auto centralLayout = new QHBoxLayout;

    centralLayout->addWidget(m_graphCanvas, 3);
    centralLayout->addWidget(m_propertyWidget, 1);

    mainLayout->addWidget(toolbar);
    mainLayout->addLayout(centralLayout);

    setLayout(mainLayout);
    setModel(model);

    init_connections();
}

GraphWidget::~GraphWidget() = default;

void GraphWidget::setModel(GraphModel* model)
{
    if (!model)
        return;

    m_model = model;

    job_manager = std::make_unique<JobManager>();

    m_propertyWidget->setModel(model);

    m_graphCanvas->setItem(Utils::TopItem<GraphViewportItem>(model));
}

//! Takes ready simulation results from JobManager and write into the model.

void GraphWidget::onSimulationCompleted()
{
    auto data = job_manager->simulationResult();
    if (!data.empty())
        m_model->set_data(data);
}

void GraphWidget::init_connections()
{
    // change in amplitude is propagated from toolbar to JobManager
    connect(toolbar, &GraphWidgetToolBar::valueChanged, job_manager.get(),
            &JobManager::requestSimulation);

    // Simulation progress is propagated from JobManager to toolbar.
    // Connection is made queued since JobManager::progressChanged is emitted from non-GUI thread.
    connect(job_manager.get(), &JobManager::progressChanged, toolbar,
            &GraphWidgetToolBar::onProgressChanged, Qt::QueuedConnection);

    // Notification about completed simulation from jobManager to GraphWidget.
    // Connection is made queued since JobManager::simulationCompleted is emitted from non-GUI
    // thread.
    connect(job_manager.get(), &JobManager::simulationCompleted, this,
            &GraphWidget::onSimulationCompleted, Qt::QueuedConnection);

    // simulation delay factor is propagated from toolbar to JobManager
    connect(toolbar, &GraphWidgetToolBar::delayChanged, job_manager.get(), &JobManager::setDelay);

    // cancel click is propagated from toolbar to JobManager
    connect(toolbar, &GraphWidgetToolBar::cancelPressed, job_manager.get(),
            &JobManager::onInterruptRequest);
}
