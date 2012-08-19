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
#ifndef BIO_TRD_CompositeElectrode_HXX
#define BIO_TRD_CompositeElectrode_HXX
#include "../../biosensor.hxx"
#include "../slv/ISolver.hxx"
#include "../slv/ITransducer.hxx"
#include "../cfg/BoundAnalyzer.hxx"
#include "../dm/IDataModel.hxx"
#include "../dm/IGrid2D.hxx"
#include "../dm/ICursor2D.hxx"
#include "../dm/IComposite2D.hxx"
#include "../dm/ISegmentSplit.hxx"
#include "IntegralOverArea.hxx"
#include <biosensor-xml.hxx>
#include <string>
#include <vector>
BIO_TRD_NS_BEGIN


/**
 *  Transducer: InjectedElectrode.
 */
class CompositeElectrode : public BIO_SLV_NS::ITransducer
{
private:
    std::vector<BIO_SLV_NS::ITransducer *> transducers;
    std::vector<BIO_SLV_NS::ITransducer *> transducersToDelete;

public:
    CompositeElectrode();

    virtual ~CompositeElectrode();

    void addTransducer(BIO_SLV_NS::ITransducer* transducer, bool deleteOnDestruction);

    /**
     *  Returns current density, generated by the biosensor.
     */
    virtual double getOutput();

};



BIO_TRD_NS_END
#endif
