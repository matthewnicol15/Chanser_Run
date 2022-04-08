#pragma once


#include "BaseOutEvent.h"

#pragma link C++ class matthewn::TreeDataScaling_Strangeness;

namespace matthewn{

  class TreeDataScaling_Strangeness : public chanser::BaseOutEvent{

  public:
    TreeDataScaling_Strangeness(){SetName("Scaling_Strangeness");}
    ~TreeDataScaling_Strangeness() final =default;

    //data member for tree branches below here
    Double_t Miss1K=0;
    Double_t Miss2K=0;
    Double_t Miss3K=0;


    //example of e- kinematics
    //you can remove these if not using
    Double_t W=0;
    Double_t Q2=0;
    Double_t Pol=0;
    Double_t Egamma=0;

    // Particle kinematics
    Double_t electron_theta=0, Kaonp_1_theta=0, Kaonp_2_theta=0, Kaonp_3_theta=0;
    Double_t electron_momentum=0, Kaonp_1_momentum=0, Kaonp_2_momentum=0, Kaonp_3_momentum;
    Double_t electron_Phi=0, Kaonp_1_Phi=0, Kaonp_2_Phi=0, Kaonp_3_Phi=0;
    Double_t electron_delta_time=0, Kaonp_1_delta_time=0, Kaonp_2_delta_time=0, Kaonp_3_delta_time=0;

    Int_t Trigger=-10;
    TString Trigger_Binary;

    ///////////////////////////////////////////////////////////
    //LEAVE THE FOLLOWING FUNCTIONS
    //Function required to set tree branches
    void Branches(TTree* tree) final{
      BaseOutEvent::Branches(tree,Class()->GetListOfDataMembers());
    }
    void Hipo(hipo::ntuple_writer* writer) final{
      BaseOutEvent::Hipo(writer,Class()->GetListOfDataMembers());
    }

    ClassDefOverride(TreeDataScaling_Strangeness,1);
  };
}
