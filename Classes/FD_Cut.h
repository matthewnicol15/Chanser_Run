//////////////////////////////////////////////////////////////
///
///Class:
///Description:
///     my own derived particle cut

#pragma once

#include "BaseCut.h"

namespace matthewn{


  class FD_Cut : public chanser::BaseCut{

  public:
    FD_Cut()=default; // must have default constructor


    Bool_t ParticleCut(const chanser::BaseParticle* part) const noexcept override{
      auto c12p = static_cast<const chanser::CLAS12Particle*>(part);
      auto c12=c12p->CLAS12(); //if you require other DST data
      if(c12->getRegion()==clas12::FD) return true;
      return false;
    }



    void Print(Option_t* option = "")const final{
      std::cout<<"\t\t"<<ClassName()<<" particles on FD "<<std::endl;
    }

  private:
    Float_t _cutDetector=chanser::THIS_FLT_MAX;

    ClassDefOverride(matthewn::FD_Cut,1);

  };//class FD_Cut

}
