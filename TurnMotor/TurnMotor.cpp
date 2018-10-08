/*======================================================================================================================

    Copyright 2011, 2012, 2013, 2014, 2015 Institut fuer Neuroinformatik, Ruhr-Universitaet Bochum, Germany

    This file is part of cedar.

    cedar is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    cedar is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with cedar. If not, see <http://www.gnu.org/licenses/>.

========================================================================================================================

    Institute:   Ruhr-Universitaet Bochum
                 Institut fuer Neuroinformatik

    File:        EarSubscriber.h

    Maintainer:  Tutorial Writer Person
    Email:       cedar@ini.rub.de
    Date:        2011 12 09

    Description:

    Credits:

======================================================================================================================*/

// CEDAR INCLUDES
#include "TurnMotor.h"
#include <cedar/processing/ExternalData.h> // getInputSlot() returns ExternalData
#include <cedar/auxiliaries/MatData.h> // this is the class MatData, used internally in this step
#include "cedar/auxiliaries/math/functions.h"
#include <cmath>
#include "std_msgs/Float64.h"


// SYSTEM INCLUDES

//----------------------------------------------------------------------------------------------------------------------
// constructors and destructor
//----------------------------------------------------------------------------------------------------------------------
TurnMotor::TurnMotor()
:
cedar::proc::Step(true),
mMotordir(new cedar::aux::UIntParameter(this, "1 left, 2 right", 1, cedar::aux::UIntParameter::LimitType::positive(2))),
mVel(new cedar::aux::DoubleParameter(this,"Motor Pos",25))
{
this->declareInput("motor", true);
//pub = n.advertise<std_msgs::Float64>("MotorCommand", 1000);
velocity = 0;
choice = 1;
this->connect(this->mMotordir.get(), SIGNAL(valueChanged()), this, SLOT(setDirection()));
this->connect(this->mVel.get(), SIGNAL(valueChanged()), this, SLOT(setVelocity()));
}
//----------------------------------------------------------------------------------------------------------------------
// methods
//----------------------------------------------------------------------------------------------------------------------
void TurnMotor::compute(const cedar::proc::Arguments&)
{

  cedar::aux::ConstDataPtr op1 = this->getInputSlot("motor")->getData();
  cv::Mat doublepos = op1->getData<cv::Mat>();
  float t1 = doublepos.at<float>(0);
  activated = static_cast<double> (t1);
  activated = round(activated);
  if(activated == 1)
  {
     std::cout<<"activated\n";
  }
  else
  {
     std::cout<<"NOT activated\n";
  }




}

void TurnMotor::setDirection()
{
  choice = static_cast<int>(this->mMotordir->getValue());
}

void TurnMotor::setVelocity()
{
   velocity = static_cast<double>(this->mVel->getValue());
}

void TurnMotor::reset()
{

	//ros::shutdown();

}
