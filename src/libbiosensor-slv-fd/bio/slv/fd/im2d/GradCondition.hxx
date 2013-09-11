/*
 * Copyright 2011-2013 Karolis Petrauskas
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
#ifndef BIO_SLV_FD_IM2D_GradCondition_HXX
#define BIO_SLV_FD_IM2D_GradCondition_HXX
#include "../../../../biosensor-slv-fd.hxx"
#include "IBoundCondition.hxx"
#include "AreaSubSolver.hxx"

BIO_SLV_FD_IM2D_NS_BEGIN


/**
 *  Bound condition "Grad".
 *  The "Wall" condition is a special case (f = 0) of this boundary condition.
 */
class GradCondition : public IBoundCondition
{
private:

    IAreaEdgeData* edge;
    bool atStart;
    double diffusion;
    IAreaEdgeFunction* function;

public:

    /**
     *  Constructor.
     *
     *  \param edge     Reference to the data in the area.
     *  \param atStart  Is this condition at top|left (true) or bottom|right (false)?
     */
    GradCondition(
        IAreaEdgeData* edge,
        bool atStart,
        double diffusion,
        IAreaEdgeFunction* function
    );

    /**
     *
     */
    virtual ~GradCondition();

    /**
     *
     */
    virtual void solveThroughForward();

    /**
     *
     */
    virtual void solveThroughBackward();

    /**
     *
     */
    virtual void solveAlongForward();

    /**
     *
     */
    virtual void solveAlongBackward();

    /**
     *
     */
    virtual void applyInitialValues();

    /**
     *
     */
    virtual double getConcentration(int x);

    /**
     *  Set concentration for the substance at specified point.
     *
     *  \param x    Point index;
     *  \param c    New concentration.
     */
    virtual void setConcentration(int x, double c);

};



BIO_SLV_FD_IM2D_NS_END

#endif
