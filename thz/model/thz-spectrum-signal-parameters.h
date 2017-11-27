/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2017 UBNANO
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Zahed Hossain <zahedhos@buffalo.edu>
 *         Qing Xia <qingxia@buffalo.edu>
 *         Josep Miquel Jornet <jmjornet@buffalo.edu>
 */


#ifndef THZ_SPECTRUM_SIGNAL_PARAMETERS_H
#define THZ_SPECTRUM_SIGNAL_PARAMETERS_H


#include <ns3/simple-ref-count.h>
#include <ns3/ptr.h>
#include <ns3/nstime.h>


namespace ns3 {

class THzPhy;
class SpectrumValue;
class Packet;

/**
 * This struct provides the generic signal representation to be used by
 * all wireless technologies. Any specific wireless technology is
 * allowed to define additional signal parameters by inheriting from this
 * struct and providing additional member variables. This makes sure
 * that a minimum set of parameters (in particular, the ones needed
 * for interference calculation) is
 * common across all wireless technologies, while at the same time
 * allowing each technology to have its own specific signal parameters.
 *
 * Furthermore, since the signal parameters specific of every technology inherit
 * directly from this struct, each PHY can test (by using a dynamic
 * cast) if a signal being received belongs to a given technology or not.
 *
 * \note when inheriting from this class, make sure that the assignment operator and the copy constructor work properly, making deep copies if needed.
 */
struct THzSpectrumSignalParameters : public SimpleRefCount<THzSpectrumSignalParameters>
{
  /**
   * default constructor
   */
  THzSpectrumSignalParameters ();

  /**
   * destructor
   */
  virtual ~THzSpectrumSignalParameters ();

  /**
   * copy constructor
   */
  THzSpectrumSignalParameters (const THzSpectrumSignalParameters& p);

  /**
   * make a "virtual" copy of this class, where "virtual" refers to
   * the fact that if the actual object is a derived class of
   * THzSpectrumSignalParameters, then the copy is also a derived class
   * of the same type.
   * Each class inheriting from
   * THzSpectrumSignalParameters should override this method and use it
   * to call the copy constructor of the derived class.
   *
   * \return a copy of the (possibly derived) class
   */
  virtual Ptr<THzSpectrumSignalParameters> Copy ();

  /**
   * The Power Spectral Density of the
   * waveform, in linear units. The exact unit will depend on the
   * type of transmission medium involved: W for radio communications, Pa for
   * underwater acoustic communications. Other transmission media to
   * be defined.
   *
   * \note when THzSpectrumSignalParameters is copied, only the pointer to the PSD will be copied. This is because SpectrumChannel objects normally overwrite the psd anyway, so there is no point in making a copy.
   */
  Ptr <SpectrumValue> txPsd;

  /**
   * The duration of the packet transmission. It is
   * assumed that the Power Spectral Density remains constant for the
   * whole duration of the transmission. In other words, all waveform
   * have a rect shape with respect to time.
   */
  Time txDuration;

  /**
   * The SpectrumPhy instance that is making the transmission
   */
  Ptr<THzPhy> txPhy;

  /**
   * The data packet being transmitted with this signal
   */
  Ptr<Packet> packet;
  double txPower;
  double numberOfSamples;
  double numberOfSubBands;
  double subBandBandwidth;
  double centerFrequency;
  double totalBandwidth;
};


}




#endif /* THZ_SPECTRUM_SIGNAL_PARAMETERS_H */