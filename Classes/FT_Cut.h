//////////////////////////////////////////////////////////////
///
///Class:
///Description:
///     my own derived particle cut

#pragma once

#include "BaseCut.h"

namespace matthewn{


  class FT_Cut : public chanser::BaseCut{

  public:
    FT_Cut()=default; // must have default constructor


    Bool_t ParticleCut(const chanser::BaseParticle* part) const noexcept override{
      auto c12p = static_cast<const chanser::CLAS12Particle*>(part);
      auto c12=c12p->CLAS12(); //if you require other DST data
      if(c12->getRegion()==clas12::FT) return true;
      return false;
    }



    void Print(Option_t* option = "")const final{
      std::cout<<"\t\t"<<ClassName()<<" with electron on FT "<<std::endl;
    }

  private:
    Float_t _cutDetector=chanser::THIS_FLT_MAX;

    ClassDefOverride(matthewn::FT_Cut,1);

  };//class FT_Cut

}
