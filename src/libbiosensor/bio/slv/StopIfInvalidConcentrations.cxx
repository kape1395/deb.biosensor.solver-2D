/*
 * Copyright 2011 Karolis Petrauskas
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "StopIfInvalidConcentrations.hxx"
#include "../Exception.hxx"
#include <iostream>
#include <cmath>
#include <memory>
#include "../Logging.hxx"
#define LOGGER "libbiosensor::StopIfInvalidConcentrations: "


/* ************************************************************************** */
/* ************************************************************************** */
BIO_SLV_NS::StopIfInvalidConcentrations::StopIfInvalidConcentrations(
    ISolver* solver,
    long checkEveryNumberOfSteps
)
{
    this->iterativeSolver = dynamic_cast<BIO_SLV_NS::IIterativeSolver*>(solver);
    this->dataModel = dynamic_cast<BIO_DM_NS::IComposite2D*>(solver->getData());
    this->checkEveryNumberOfSteps = checkEveryNumberOfSteps;

    if (this->checkEveryNumberOfSteps <= 0)
        this->checkEveryNumberOfSteps = 1;

    if (iterativeSolver == 0)
        throw Exception("StopIfInvalidConcentrations: Solver must implement IIterativeSolver");

    if (dataModel == 0)
        throw Exception("StopIfInvalidConcentrations: Solver dataModel must implement IComposite2D");

    nextStepForCheck = iterativeSolver->getSolvedIterationCount();
}


/* ************************************************************************** */
/* ************************************************************************** */
BIO_SLV_NS::StopIfInvalidConcentrations::~StopIfInvalidConcentrations()
{
    //  Nothing to do here
}


/* ************************************************************************** */
/* ************************************************************************** */
void BIO_SLV_NS::StopIfInvalidConcentrations::solveEventOccured()
{
    if (iterativeSolver->getSolvedIterationCount() < nextStepForCheck)
    {
        return;
    }

    for (int v = 0; v < dataModel->sizeV(); v++)
    {
        for (int h = 0; h < dataModel->sizeH(); h++)
        {
            if (!checkSubArea(dataModel->getArea(h, v), h, v))
            {
                iterativeSolver->stop(false);
                LOG_ERROR(LOGGER << "The solver is stopped because it is in an invalid state.");
            }
        }
    }
    LOG_DEBUG(LOGGER << "Validation successful");

    nextStepForCheck = iterativeSolver->getSolvedIterationCount() + checkEveryNumberOfSteps;
}


/* ************************************************************************** */
/* ************************************************************************** */
void BIO_SLV_NS::StopIfInvalidConcentrations::reset()
{
    nextStepForCheck = iterativeSolver->getSolvedIterationCount();
}


/* ************************************************************************** */
/* ************************************************************************** */
bool BIO_SLV_NS::StopIfInvalidConcentrations::checkSubArea(BIO_DM_NS::IGrid2D* area, int posH, int posV)
{
    std::auto_ptr<BIO_DM_NS::ICursor2D> cursor(area->newGridCursor());

    for (cursor->colStart(); cursor->rowStart(), cursor->isValid(); cursor->down())
    {
        for ( ; cursor->isValid(); cursor->right())
        {
            BIO_DM_NS::IConcentrations* concentrations = cursor->getConcentrations();
            for (int s = 0; s < area->getSubstanceCount(); s++)
            {
                double c = concentrations->getConcentration(s);
                if (area->getSubstanceConf(s) && (std::isnan(c) || c < ZERO_MIN))
                {
                    LOG_WARN(LOGGER
                             << "An invalid concentration value \"" << c
                             << "\" found for the substance \""
                             << area->getSubstanceConf(s)->name()
                             << "\" in the subArea with position:"
                             << " h=" << posH << " v=" << posV
                            );
                    return false;
                }
            }
        }
    }

    return true;
}


/* ************************************************************************** */
/* ************************************************************************** */
