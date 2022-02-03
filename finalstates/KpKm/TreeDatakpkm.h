#pragma once


#include "BaseOutEvent.h"

#pragma link C++ class matthewn::TreeDatakpkm;

namespace matthewn{

  class TreeDatakpkm : public chanser::BaseOutEvent{

  public:
    TreeDatakpkm(){SetName("kpkm");}
    ~TreeDatakpkm() final =default;

    //data member for tree branches below here
    Double_t InvKpKm=0;
    Double_t MissMassAll2=0;
    Double_t MissMassp=0;
    Double_t MissMasskp=0;
    Double_t MissMasskm=0;
    Double_t MissMassRes=0;
    Double_t MomentumExchange=0;
    Double_t proton_theta=0, electron_theta=0, kaonm_theta=0, kaonp_theta=0;
    Double_t proton_momentum=0, electron_momentum=0, kaonm_momentum=0, kaonp_momentum=0;
    Double_t proton_Phi=0, electron_Phi=0, kaonm_Phi=0, kaonp_Phi=0;
    Double_t kaonp_delta_time=0, kaonm_delta_time=0, proton_delta_time=0, electron_delta_time=0;

    //example of e- kinematics
    //you can remove these if not using
    Double_t W=0;
    Double_t Q2=0;
    Double_t Pol=0;
    Double_t Egamma=0;

    Double_t ProdCosThGJ=0;
    Double_t ProdPhiGJ=0;
    Double_t MesonCosThGJ=0;
    Double_t MesonPhiGJ=0;
    Double_t PolPhi=0;
    Double_t CosTh=0;
    Double_t Phi=0;

    ///////////////////////////////////////////////////////////
    //LEAVE THE FOLLOWING FUNCTIONS
    //Function required to set tree branches
    void Branches(TTree* tree) final{
      BaseOutEvent::Branches(tree,Class()->GetListOfDataMembers());
    }
    void Hipo(hipo::ntuple_writer* writer) final{
      BaseOutEvent::Hipo(writer,Class()->GetListOfDataMembers());
    }

    ClassDefOverride(TreeDatakpkm,1);
  };
}
